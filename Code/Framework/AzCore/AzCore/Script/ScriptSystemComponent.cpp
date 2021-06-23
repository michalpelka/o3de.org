/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#if !defined(AZCORE_EXCLUDE_LUA)

#include <AzCore/Script/ScriptSystemComponent.h>

#include <AzCore/Asset/AssetManagerBus.h>
#include <AzCore/Asset/AssetManager.h>
#include <AzCore/Casting/numeric_cast.h>
#include <AzCore/Component/ComponentApplication.h>
#include <AzCore/Component/Entity.h>
#include <AzCore/Component/TickBus.h>
#include <AzCore/Debug/TraceReflection.h>
#include <AzCore/IO/FileIO.h>
#include <AzCore/Math/MathReflection.h>
#include <AzCore/PlatformId/PlatformId.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/Script/ScriptAsset.h>
#include <AzCore/Script/ScriptContextDebug.h>
#include <AzCore/Script/ScriptDebug.h>

#include <AzCore/std/string/conversions.h>
#include <AzCore/Script/lua/lua.h>

using namespace AZ;

/**
 * Script lifecycle:
 * 1. When a script is requested for load, LoadAssetData() is called by the asset database
 * 2. LoadAssetData will load the script into a buffer.
 * 3. Load will compile the script, execute the function, and return with the resulting table on top of the stack.
 *      This table will also be cached, so subsequent loads of the same script/vm will not recompile.
 * 4. On change, all references to the script will be removed.
 *      If the script has been required, the script will no longer be tracked.
 *      If the script was loaded by a ScriptComponent, Load will be called once reload is complete.
 */

namespace
{
    // Called when a module has already been loaded
    static int LuaRequireLoadedModule(lua_State* l)
    {
        // Push value to top of stack
        lua_pushvalue(l, lua_upvalueindex(1));

        return 1;
    }
}

//=========================================================================
// ScriptSystemComponent
// [5/29/2012]
//=========================================================================
ScriptSystemComponent::ScriptSystemComponent()
{
    m_defaultGarbageCollectorSteps = 2; // this is a default value, users should tweak this number for optimal performance
}

//=========================================================================
// ~ScriptSystemComponent
// [5/29/2012]
//=========================================================================
ScriptSystemComponent::~ScriptSystemComponent()
{
}

//=========================================================================
// Activate
// [5/29/2012]
//=========================================================================
void ScriptSystemComponent::Activate()
{
    // Create default context
    AddContextWithId(ScriptContextIds::DefaultScriptContextId);

    ScriptSystemRequestBus::Handler::BusConnect();

    SystemTickBus::Handler::BusConnect();

    AZ::Data::AssetCatalogRequestBus::Broadcast(&AZ::Data::AssetCatalogRequests::AddExtension, "lua");
    AZ::Data::AssetCatalogRequestBus::Broadcast(&AZ::Data::AssetCatalogRequests::AddExtension, "luac");

    if (Data::AssetManager::Instance().IsReady())
    {
        Data::AssetManager::Instance().RegisterHandler(this, AzTypeInfo<ScriptAsset>::Uuid());
    }

    AZ::AssetTypeInfoBus::Handler::BusConnect(AZ::AzTypeInfo<ScriptAsset>::Uuid());
}

//=========================================================================
// Deactivate
// [5/29/2012]
//=========================================================================
void ScriptSystemComponent::Deactivate()
{
    AZ::AssetTypeInfoBus::Handler::BusDisconnect();
    Data::AssetBus::MultiHandler::BusDisconnect();
    SystemTickBus::Handler::BusDisconnect();
    ScriptSystemRequestBus::Handler::BusDisconnect();

    for (auto& context : m_contexts)
    {
        if (context.m_isOwner)
        {
            // Lock access to the loaded scripts map
            AZStd::lock_guard<AZStd::recursive_mutex> lock(context.m_loadedScriptsMutex);

            // Clear loaded scripts, they need the context to still be around on unload
            context.m_loadedScripts.clear();
            delete context.m_context;
        }
    }

    m_contexts.clear();

    // Need to do this at the end, so that any cached scripts cleared above may be released properly
    if (Data::AssetManager::Instance().IsReady())
    {
        Data::AssetManager::Instance().UnregisterHandler(this);
    }
}

//=========================================================================
// AddContext
// [3/1/2014]
//=========================================================================
ScriptContext*  ScriptSystemComponent::AddContext(ScriptContext* context, int garbageCollectorStep)
{
    AZ_Assert(context == nullptr || context->GetId() != ScriptContextIds::DefaultScriptContextId, "Default script context ID is reserved! Please provide a Unique context ID for you ScriptContext!");
    if (context && GetContext(context->GetId()) == nullptr)
    {
        m_contexts.emplace_back();
        ContextContainer& cc = m_contexts.back();
        cc.m_context = context;
        cc.m_isOwner = false;
        cc.m_garbageCollectorSteps = garbageCollectorStep < 1 ? m_defaultGarbageCollectorSteps : garbageCollectorStep;

        if (context->GetId() != ScriptContextIds::CryScriptContextId)
        {
            BehaviorContext* behaviorContext = nullptr;
            EBUS_EVENT_RESULT(behaviorContext, ComponentApplicationBus, GetBehaviorContext);
            if (behaviorContext)
            {
                context->BindTo(behaviorContext);
            }
        }

        return context;
    }

    return nullptr;
}

//=========================================================================
// AddContextWithId
// [3/1/2014]
//=========================================================================
ScriptContext* ScriptSystemComponent::AddContextWithId(ScriptContextId id)
{
    AZ_Assert(m_contexts.empty() || id != ScriptContextIds::DefaultScriptContextId, "Default script context ID is reserved! Please provide a Unique context ID for you ScriptContext!");
    if (GetContext(id) == nullptr)
    {
        m_contexts.emplace_back();
        ContextContainer& cc = m_contexts.back();
        cc.m_context = aznew ScriptContext(id);
        cc.m_isOwner = true;
        cc.m_garbageCollectorSteps = m_defaultGarbageCollectorSteps;

        cc.m_context->SetRequireHook(AZStd::bind(&ScriptSystemComponent::DefaultRequireHook, this, AZStd::placeholders::_1, AZStd::placeholders::_2, AZStd::placeholders::_3));

        if (id != ScriptContextIds::CryScriptContextId)
        {
            // Reflect script classes
            ComponentApplication* app = nullptr;
            EBUS_EVENT_RESULT(app, ComponentApplicationBus, GetApplication);
            if (app && app->GetDescriptor().m_enableScriptReflection)
            {
                if (app->GetBehaviorContext())
                {
                    cc.m_context->BindTo(app->GetBehaviorContext());
                }
                else
                {
                    AZ_Error("Script", false, "We are asked to enabled scripting, but the Applicaion has no BehaviorContext! Scripting relies on BehaviorContext!");
                }
            }
        }

        return cc.m_context;
    }

    return nullptr;
}

void ScriptSystemComponent::RestoreDefaultRequireHook(ScriptContextId id)
{
    if (auto context = GetContext(id))
    {
        for (auto& inMemoryModule : m_inMemoryModules)
        {
            ClearAssetReferences(inMemoryModule.second->GetId());
        }

        m_inMemoryModules.clear();
        context->SetRequireHook(AZStd::bind(&ScriptSystemComponent::DefaultRequireHook, this, AZStd::placeholders::_1, AZStd::placeholders::_2, AZStd::placeholders::_3));
    }
}

void ScriptSystemComponent::UseInMemoryRequireHook(const InMemoryScriptModules& modules, ScriptContextId id)
{
    if (auto context = GetContext(id))
    {
        m_inMemoryModules = modules;
        context->SetRequireHook(AZStd::bind(&ScriptSystemComponent::InMemoryRequireHook, this, AZStd::placeholders::_1, AZStd::placeholders::_2, AZStd::placeholders::_3));
    }
}

//=========================================================================
// RemoveContext
// [3/1/2014]
//=========================================================================
bool ScriptSystemComponent::RemoveContext(ScriptContext* context)
{
    if (context)
    {
        return RemoveContextWithId(context->GetId());
    }

    return false;
}

//=========================================================================
// RemoveContextWithId
//=========================================================================
bool ScriptSystemComponent::RemoveContextWithId(ScriptContextId id)
{
    AZ_Assert(id != ScriptContextIds::DefaultScriptContextId, "Default script context ID is reserved! The system will remove the context automatically on shutdown!");
    if (id == ScriptContextIds::DefaultScriptContextId)
    {
        return false;
    }

    ContextContainer* container = AZStd::find_if(m_contexts.begin(), m_contexts.end(), [&id](const ContextContainer& ctxContainer) { return ctxContainer.m_context->GetId() == id; });
    if (container != m_contexts.end())
    {
        delete container->m_context;
        m_contexts.erase(container);
        return true;
    }

    return false;
}

//=========================================================================
// GetContext
// [3/1/2014]
//=========================================================================
ScriptContext*  ScriptSystemComponent::GetContext(ScriptContextId id)
{
    ContextContainer* container = GetContextContainer(id);
    if (container)
    {
        return container->m_context;
    }
    return nullptr;
}

//=========================================================================
// OnSystemTick
//=========================================================================
void    ScriptSystemComponent::OnSystemTick()
{
    for (size_t i = 0; i < m_contexts.size(); ++i)
    {
        ContextContainer& contextContainer = m_contexts[i];
        if (contextContainer.m_context->GetDebugContext())
        {
            contextContainer.m_context->GetDebugContext()->ProcessDebugCommands();
        }

#ifdef AZ_PROFILE_TELEMETRY
        if (contextContainer.m_context->GetId() == ScriptContextIds::DefaultScriptContextId)
        {
            size_t memoryUsageBytes = contextContainer.m_context->GetMemoryUsage();
            AZ_PROFILE_DATAPOINT(AZ::Debug::ProfileCategory::Script, memoryUsageBytes / 1024.0, "Script Memory (KB)");
        }
#endif // AZ_PROFILE_TELEMETRY

        contextContainer.m_context->GarbageCollectStep(contextContainer.m_garbageCollectorSteps);
    }
}

//=========================================================================
// GarbageCollect
//=========================================================================
void ScriptSystemComponent::GarbageCollect()
{
    for (size_t i = 0; i < m_contexts.size(); ++i)
    {
        ScriptContext* vm = m_contexts[i].m_context;
        if (vm)
        {
            vm->GarbageCollect();
        }
    }
}

//=========================================================================
// GarbageCollectStep
//=========================================================================
void ScriptSystemComponent::GarbageCollectStep(int numberOfSteps)
{
    for (size_t i = 0; i < m_contexts.size(); ++i)
    {
        ScriptContext* vm = m_contexts[i].m_context;
        if (vm)
        {
            vm->GarbageCollectStep(numberOfSteps);
        }
    }
}

bool ScriptSystemComponent::Load(const Data::Asset<ScriptAsset>& asset, const char* mode, ScriptContextId id)
{
    return LoadAndGetNativeContext(asset, mode, id).status != ScriptLoadResult::Status::Failed;
}

ScriptLoadResult ScriptSystemComponent::LoadAndGetNativeContext(const Data::Asset<ScriptAsset>& asset, const char* mode, ScriptContextId id)
{
    ContextContainer* container = GetContextContainer(id);
    ScriptContext* context = container->m_context;
    lua_State* lua = context->NativeContext();

    {
        // Lock access to the loaded scripts map
        AZStd::lock_guard<AZStd::recursive_mutex> lock(container->m_loadedScriptsMutex);

        // Check if already loaded
        auto scriptIt = container->m_loadedScripts.find(asset.GetId().m_guid);
        if (scriptIt != container->m_loadedScripts.end())
        {
            lua_rawgeti(lua, LUA_REGISTRYINDEX, scriptIt->second.m_tableReference);

            // If not table, pop and return false
            if (!lua_istable(lua, -1))
            {
                lua_pop(lua, 1);
                return { ScriptLoadResult::Status::Failed, lua };
            }
            else
            {
                return { ScriptLoadResult::Status::OnStack, lua };
            }
        }
    }

    // Load lua script into the VM
    IO::MemoryStream stream = asset.Get()->CreateMemoryStream();
    if (!context->LoadFromStream(&stream, asset.Get()->GetDebugName(), mode, lua))
    {
        context->Error(ScriptContext::ErrorType::Error, "%s", lua_tostring(lua, -1));
        lua_pop(lua, 1);
        return { ScriptLoadResult::Status::Failed, lua };
    }

    // Execute the script
    if (!Internal::LuaSafeCall(lua, 0, 1))
    {
        return { ScriptLoadResult::Status::Failed, lua };
    }

    // Dupe the table (so we can ref AND return it)
    lua_pushvalue(lua, -1);
    int ref = luaL_ref(lua, LUA_REGISTRYINDEX);

    // No need to keep the script asset around, the owner will keep a reference to it (or this, if it's require()'d)
    LoadedScriptInfo info;
    const char* debugName = asset.Get()->GetDebugName();
    if (debugName)
    {
        info.m_scriptNames.emplace(debugName);
    }
    info.m_tableReference = ref;

    {
        // Lock access to the loaded scripts map
        AZStd::lock_guard<AZStd::recursive_mutex> lock(container->m_loadedScriptsMutex);
        container->m_loadedScripts.emplace(asset.GetId().m_guid, AZStd::move(info));
    }

    return { ScriptLoadResult::Status::Initial, lua };
}

//=========================================================================
// GetContextContainer
// [3/20/2014]
//=========================================================================
ScriptSystemComponent::ContextContainer* ScriptSystemComponent::GetContextContainer(ScriptContextId id)
{
    for (size_t i = 0; i < m_contexts.size(); ++i)
    {
        if (m_contexts[i].m_context->GetId() == id)
        {
            return &m_contexts[i];
        }
    }

    return nullptr;
}

/**
 * Hook called when requiring a script
 *
 * Step 1: Build file path from module name requested
 * Step 2: Lookup file path in asset database
 * If already loaded:
 *  Step 3: Push cached result of asset to top of stack
 *  Step 4: Push function (above) that simply returns that value (require() expects either a function (success) or string (error message) pushed to the stack)
 * Else:
 *  Step 3: Request load of asset
 *  Step 4: Short circuit asset loading, and load asset blocking (require waits for no man)
 * Step 5: Register the script with the script system component, so that on asset unload, we may cache it (see TrackRequiredScript for more details)
 */
int ScriptSystemComponent::DefaultRequireHook(lua_State* lua, ScriptContext* context, const char* module)
{
    // File extension for lua files
    static const char* s_luaExtension = ".luac";
    ContextContainer* container = GetContextContainer(context->GetId());

    // Replace '.' in module name with '/'
    AZStd::string filePath = module;
    for (auto pos = filePath.find('.'); pos != AZStd::string::npos; pos = filePath.find('.'))
    {
        filePath.replace(pos, 1, "/", 1);
    }

    // Add file extension to path
    if (!filePath.ends_with(s_luaExtension))
    {
        filePath += s_luaExtension;
    }

    Data::AssetId scriptId;
    EBUS_EVENT_RESULT(scriptId, Data::AssetCatalogRequestBus, GetAssetIdByPath, filePath.c_str(), azrtti_typeid<ScriptAsset>(), false);
    if (!scriptId.IsValid())
    {
        lua_pushfstring(lua, "Module \"%s\" has not been registered with the Asset Database.", filePath.c_str());
        return 1;
    }

    // Lock access to the loaded scripts map
    AZStd::lock_guard<AZStd::recursive_mutex> lock(container->m_loadedScriptsMutex);

    // If script already loaded in this context, just use its resulting table
    auto scriptIt = container->m_loadedScripts.find(scriptId.m_guid);
    if (scriptIt != container->m_loadedScripts.end())
    {
        // Add the name used for require as an alias
        scriptIt->second.m_scriptNames.emplace(module);
        // Push the value to a closure that will just return it
        lua_rawgeti(lua, LUA_REGISTRYINDEX, scriptIt->second.m_tableReference);
        lua_pushcclosure(lua, LuaRequireLoadedModule, 1);

        // If asset reference already populated, just return now. Otherwise, capture reference
        if (scriptIt->second.m_scriptAsset.GetId().IsValid())
        {
            return 1;
        }
    }

    // Grab a reference to the script asset being loaded
    Data::Asset<ScriptAsset> script = Data::AssetManager::Instance().FindAsset<ScriptAsset>(scriptId, AZ::Data::AssetLoadBehavior::Default);

    // If it's not loaded, load it in a blocking manner
    if (!script.IsReady())
    {
        script = Data::AssetManager::Instance().GetAsset<ScriptAsset>(scriptId, AZ::Data::AssetLoadBehavior::Default);
        script.BlockUntilLoadComplete();

        if (!script.IsReady())
        {
            lua_pushfstring(lua, "Module \"%s\" failed to load.", filePath.c_str());
            return 1;
        }
    }

    // Now that we have a valid asset reference, stash it and return if the script already loaded and tracked
    if (scriptIt != container->m_loadedScripts.end())
    {
        scriptIt->second.m_scriptAsset = script;
        return 1;
    }

    // If not, load the script, getting the resulting table
    if (!Load(script, AZ::k_scriptLoadBinary, context->GetId()))
    {
        // If the load fails, return the error string load pushed onto the stack
        return 1;
    }

    // Push function returning the result
    lua_pushcclosure(lua, LuaRequireLoadedModule, 1);

    // Set asset reference on the loaded script
    scriptIt = container->m_loadedScripts.find(scriptId.m_guid);
    scriptIt->second.m_scriptNames.emplace(module);
    scriptIt->second.m_scriptAsset = script;

    // Connect to the asset bus so that we may know when this script reloads.
    Data::AssetBus::MultiHandler::BusConnect(script.GetId());

    return 1;
}

int ScriptSystemComponent::InMemoryRequireHook(lua_State* lua, ScriptContext* context, const char* module)
{
    ContextContainer* container = GetContextContainer(context->GetId());

    // Replace '.' in module name with '/'
    AZStd::string filePath = module;
    for (auto pos = filePath.find('.'); pos != AZStd::string::npos; pos = filePath.find('.'))
    {
        filePath.replace(pos, 1, "/", 1);
    }

    auto inMemoryIter = AZStd::find_if(m_inMemoryModules.begin(), m_inMemoryModules.end(),
        [&](auto candidate) { return candidate.first == filePath; });

    if (inMemoryIter == m_inMemoryModules.end())
    {
        lua_pushfstring(lua, "Module \"%s\" failed to load form in memory assets.", filePath.c_str());
        return 1;
    }

    auto scriptId = inMemoryIter->second.GetId();

    // Lock access to the loaded scripts map
    AZStd::lock_guard<AZStd::recursive_mutex> lock(container->m_loadedScriptsMutex);

    // If script already loaded in this context, just use its resulting table
    auto scriptIt = container->m_loadedScripts.find(scriptId.m_guid);
    if (scriptIt != container->m_loadedScripts.end())
    {
        // Add the name used for require as an alias
        scriptIt->second.m_scriptNames.emplace(module);
        // Push the value to a closure that will just return it
        lua_rawgeti(lua, LUA_REGISTRYINDEX, scriptIt->second.m_tableReference);
        lua_pushcclosure(lua, LuaRequireLoadedModule, 1);

        // If asset reference already populated, just return now. Otherwise, capture reference
        if (scriptIt->second.m_scriptAsset.GetId().IsValid())
        {
            return 1;
        }
    }

    Data::Asset<ScriptAsset> script = inMemoryIter->second;

    // Now that we have a valid asset reference, stash it and return if the script already loaded and tracked
    if (scriptIt != container->m_loadedScripts.end())
    {
        scriptIt->second.m_scriptAsset = script;
        return 1;
    }

    // If not, load the script, getting the resulting table
    if (!Load(script, AZ::k_scriptLoadBinary, context->GetId()))
    {
        // If the load fails, return the error string load pushed onto the stack
        return 1;
    }

    // Push function returning the result
    lua_pushcclosure(lua, LuaRequireLoadedModule, 1);

    // Set asset reference on the loaded script
    scriptIt = container->m_loadedScripts.find(scriptId.m_guid);
    scriptIt->second.m_scriptNames.emplace(module);
    scriptIt->second.m_scriptAsset = script;

    // Connect to the asset bus so that we may know when this script reloads.
    Data::AssetBus::MultiHandler::BusConnect(script.GetId());

    return 1;
}

void ScriptSystemComponent::ClearAssetReferences(Data::AssetId assetBaseId)
{
    for (auto& container : m_contexts)
    {
        AZStd::lock_guard<AZStd::recursive_mutex> lock(container.m_loadedScriptsMutex);

        auto scriptIt = container.m_loadedScripts.find(assetBaseId.m_guid);
        if (scriptIt != container.m_loadedScripts.end())
        {
            lua_State* l = container.m_context->NativeContext();

            // Spin off thread for clearing the loaded table
            LuaNativeThread thread(l);

            lua_getfield(thread, LUA_REGISTRYINDEX, "_LOADED");
            for (const auto& modName : scriptIt->second.m_scriptNames)
            {
                lua_pushnil(thread);
                lua_setfield(thread, -2, modName.c_str());
            }

            // Unref the script table so it may be collected
            luaL_unref(thread, LUA_REGISTRYINDEX, scriptIt->second.m_tableReference);

            // Now that it has been removed, don't track it until it's required again (replacing it in this list).
            container.m_loadedScripts.erase(scriptIt);
        }
    }
}

//=========================================================================
// CreateAsset
// [3/6/2014]
//=========================================================================
Data::AssetPtr ScriptSystemComponent::CreateAsset(const Data::AssetId& id, const Data::AssetType&)
{
    return aznew ScriptAsset(id);
}

//=========================================================================
// LoadAssetData
//
// Loads the script data from disk into SciptAsset memory. This does NOT load the asset into any lua_State.
//=========================================================================
Data::AssetHandler::LoadResult ScriptSystemComponent::LoadAssetData(
    const Data::Asset<Data::AssetData>& asset,
    AZStd::shared_ptr<Data::AssetDataStream> stream,
    [[maybe_unused]] const Data::AssetFilterCB& assetLoadFilterCB)
{
    if (stream)
    {
        ScriptAsset* script = asset.GetAs<ScriptAsset>();

        // If it's a compiled asset, pull data from header
        if (asset.GetId().m_subId == ScriptAsset::CompiledAssetSubId)
        {
            // Read asset version
            ScriptAsset::LuaScriptInfo assetVersion = ScriptAsset::Invalid;
            stream->Read(sizeof(assetVersion), &assetVersion);
            if (assetVersion != ScriptAsset::AssetVersion)
            {
                AZ_Error("Script", false, "Script is binary version %u, expected %u.", assetVersion, ScriptAsset::AssetVersion);
                return Data::AssetHandler::LoadResult::Error;
            }

            // Read asset type
            ScriptAsset::LuaScriptInfo assetType = ScriptAsset::Invalid;
            stream->Read(sizeof(assetType), &assetType);

            if (assetType == ScriptAsset::AssetTypeCompiled || assetType == ScriptAsset::AssetTypeText)
            {
                // Read length of debug name
                u32 debugNameLength = 0;
                stream->Read(sizeof(debugNameLength), &debugNameLength);

                // Make string the length of the name + 1 (name in script doesn't include \0)
                script->m_debugName.resize(debugNameLength + 1);
                // Read debug name
                stream->Read(debugNameLength, script->m_debugName.data());
            }
            else
            {
                AZ_Error("Script", false, "Unsupported asset type %u!", assetType);
                return Data::AssetHandler::LoadResult::Error;
            }
        }
        // Otherwise, use defaults
        else
        {
            Data::AssetInfo scriptInfo;
            AZ::Data::AssetCatalogRequestBus::BroadcastResult(scriptInfo, &AZ::Data::AssetCatalogRequestBus::Events::GetAssetInfoById, asset.GetId());
            script->m_debugName = "@" + scriptInfo.m_relativePath;
            AZStd::to_lower(script->m_debugName.begin(), script->m_debugName.end());
        }

        // Read contents into buffer
        size_t scriptDataLength = stream->GetLength() - stream->GetCurPos(); // Remove already read characters from length

        AZ_Error("Script", scriptDataLength > 0, "Script contents are empty! Please check AssetProcessor output.");

        script->m_scriptBuffer.resize(scriptDataLength);
        stream->Read(scriptDataLength, script->m_scriptBuffer.data());

        // Clear cached references in the event of a successful load. This function has to be queued on
        // AssetBus where NotifyAssetReloaded is also queued, to ensure its execution before NotifyAssetReloaded
        Data::AssetBus::QueueFunction(&ScriptSystemComponent::ClearAssetReferences, this, asset.GetId());

        return Data::AssetHandler::LoadResult::LoadComplete;
    }

    return Data::AssetHandler::LoadResult::Error;
}

//=========================================================================
// DestroyAsset
//
// Unref the table returned by the script, so that:
//  * It may be garbage collected
//  * This asset isn't used again in the future
//=========================================================================
void ScriptSystemComponent::DestroyAsset(Data::AssetPtr ptr)
{
    delete ptr;
}

//=========================================================================
// GetHandledAssetTypes
//=========================================================================
void ScriptSystemComponent::GetHandledAssetTypes(AZStd::vector<Data::AssetType>& assetTypes)
{
    assetTypes.push_back(azrtti_typeid<ScriptAsset>());
}

//=========================================================================
// GetProvidedServices
//=========================================================================
void ScriptSystemComponent::GetProvidedServices(ComponentDescriptor::DependencyArrayType& provided)
{
    provided.push_back(AZ_CRC("ScriptService", 0x787235ab));
}

//=========================================================================
// GetIncompatibleServices
//=========================================================================
void ScriptSystemComponent::GetIncompatibleServices(ComponentDescriptor::DependencyArrayType& incompatible)
{
    incompatible.push_back(AZ_CRC("ScriptService", 0x787235ab));
}

//=========================================================================
// GetDependentServices
//=========================================================================
void ScriptSystemComponent::GetDependentServices(ComponentDescriptor::DependencyArrayType& dependent)
{
    dependent.push_back(AZ_CRC("AssetDatabaseService", 0x3abf5601));
}

//=========================================================================
// GetAssetTypeExtensions
//=========================================================================
void ScriptSystemComponent::GetAssetTypeExtensions(AZStd::vector<AZStd::string>& extensions)
{
    extensions.push_back("luac");
}

//=========================================================================
// OnAssetPreReload
// #TEMP: Remove when asset dependencies are in place
// Before an asset is reloaded, this event is called to remove the previously cached version.
// This removes all aliases from the _LOADED table. This will prevent require() calls from surfacing antiquated data.
//=========================================================================
void ScriptSystemComponent::OnAssetPreReload(Data::Asset<Data::AssetData> asset)
{
    ClearAssetReferences(asset.GetId());
}

//=========================================================================
// OnAssetReloaded
// #TEMP: Remove when asset dependencies are in place
// This function will only be called for the asset that triggered the reload.
//
// Track all reload requests and remove them from the map one by one as they are handled. 
// Once all queued reloads are handled, another full reload can be triggered.
//=========================================================================
void ScriptSystemComponent::OnAssetReloaded(Data::Asset<Data::AssetData> asset)
{
    Data::AssetBus::MultiHandler::BusDisconnect(asset.GetId());

    auto it = m_queuedReloads.find(asset.GetId());
    if (it == m_queuedReloads.end())
    {
        // This is not a reload queued by us as a "dependency" reload, probably an external change.
        if (!m_isReloadQueued)
        {
            // There is no reload-all queued, schedule one.
            m_isReloadQueued = true;
            auto triggeredByAssetId = asset.GetId();
            AZStd::function<void()> reloadFn = [this, triggeredByAssetId]() ///< Capture just reloaded asset ID so that it can be excluded from reloading
            {
                // Collects all script assets for reloading
                Data::AssetCatalogRequests::AssetEnumerationCB collectAssetsCb = [this, triggeredByAssetId](const Data::AssetId id, const Data::AssetInfo& info)
                {
                    // Check asset type
                    if (info.m_assetType == azrtti_typeid<ScriptAsset>())
                    {
                        // Ensure that the asset isn't scheduled for a reload already
                        if (id != triggeredByAssetId && m_queuedReloads.find(id) == m_queuedReloads.end()) ///< Don't reload just reloaded asset or assets already queued for reload
                        {
                            auto otherAsset = Data::AssetManager::Instance().FindAsset<ScriptAsset>(id, AZ::Data::AssetLoadBehavior::Default);
                            if (otherAsset && otherAsset.IsReady())
                            {
                                // Reload the asset from it's current data
                                otherAsset.Reload();

                                // Store the ID of the asset that we started reloading. We will use it to detect the moment 
                                // when all current reload requests are handled, and reloadFn can be called again.
                                m_queuedReloads.insert(id);
                                // the 'this->' in the following line is intentional.
                                // the C++ standard requires the use of this-> on baseclass calls that are templated classes
                                // most of the time you can get away with it, but in some cases MSVC will not correctly adjust the offset of this
                                // during the call
                                this->Data::AssetBus::MultiHandler::BusConnect(id); 
                            }
                        }
                    }
                };
                Data::AssetCatalogRequestBus::Broadcast(&Data::AssetCatalogRequestBus::Events::EnumerateAssets, nullptr, collectAssetsCb, nullptr);

                m_isReloadQueued = false;
            };
            TickBus::QueueFunction(reloadFn);
        }
    }
    else
    {
        // This is one of the reloads triggered by us via reloadFn, no need to trigger another reload-all call.
        // Remove it from the queue, so that reloadFn can be triggered again once all dependencies finished reloading.
        m_queuedReloads.erase(it);
    }
}

//=========================================================================
// GetDependentServices
//=========================================================================
AZ::Data::AssetType ScriptSystemComponent::GetAssetType() const
{
    return AZ::AzTypeInfo<ScriptAsset>::Uuid();
}

const char* ScriptSystemComponent::GetAssetTypeDisplayName() const
{
    return "Lua Script";
}

const char* ScriptSystemComponent::GetGroup() const
{
    return "Script";
}

const char* AZ::ScriptSystemComponent::GetBrowserIcon() const
{
    return "Icons/Components/LuaScript.svg";
}

AZ::Uuid AZ::ScriptSystemComponent::GetComponentTypeId() const
{
    return AZ::Uuid("{b5fc8679-fa2a-4c7c-ac42-dcc279ea613a}");
}

bool AZ::ScriptSystemComponent::CanCreateComponent(const AZ::Data::AssetId& assetId) const
{
    //LUA source files output a compiled as well as an uncompiled asset, both with the same typeID.  We only want to create components with the compiled asset
    return assetId.m_subId == ScriptAsset::CompiledAssetSubId;
}

/**
 * Behavior Context forwarder
 */
class TickBusBehaviorHandler : public TickBus::Handler, public AZ::BehaviorEBusHandler
{
public:
    AZ_EBUS_BEHAVIOR_BINDER(TickBusBehaviorHandler, "{EE90D2DA-9339-4CE6-AF98-AF81E00E2AB3}", AZ::SystemAllocator, OnTick, GetTickOrder);

    void OnTick(float deltaTime, ScriptTimePoint time) override
    {
        Call(FN_OnTick,deltaTime,time);
    }

    int GetTickOrder() override
    {
        int order = ComponentTickBus::TICK_DEFAULT;
        CallResult(order, FN_GetTickOrder);
        return order;
    }
};

// Dummy class to host ComponentTickBus enums
struct DummyTickOrder
{
    AZ_TYPE_INFO(DummyTickOrder, "{8F725746-A4BC-4DF7-A249-02931973C864}");
};

//=========================================================================
// Reflect
//=========================================================================
void ScriptSystemComponent::Reflect(ReflectContext* reflection)
{
    ScriptTimePoint::Reflect(reflection);

    if (SerializeContext* serializeContext = azrtti_cast<SerializeContext*>(reflection))
    {
        
        serializeContext->Class<ScriptSystemComponent, AZ::Component>()
            ->Version(1)
            // ->Attribute(AZ::Edit::Attributes::SystemComponentTags, AZStd::vector<AZ::Crc32>({ AZ_CRC("AssetBuilder", 0xc739c7d7) }))
            ->Field("garbageCollectorSteps", &ScriptSystemComponent::m_defaultGarbageCollectorSteps)
            ;

        if (EditContext* editContext = serializeContext->GetEditContext())
        {
            editContext->Class<ScriptSystemComponent>(
                "Script System", "Initializes and maintains script contexts")
                ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "Engine")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC("System", 0xc94d118b))
                ;
        }
    }

    if (BehaviorContext* behaviorContext = azrtti_cast<BehaviorContext*>(reflection))
    {
        // reflect default entity
        MathReflect(behaviorContext);
        ScriptDebug::Reflect(behaviorContext);
        Debug::TraceReflect(behaviorContext);

        behaviorContext->Class<PlatformID>("Platform")
            ->Enum<static_cast<int>(PlatformID::PLATFORM_WINDOWS_64)>("Windows64")
            ->Enum<static_cast<int>(PlatformID::PLATFORM_LINUX_64)>("Linux")
            ->Enum<static_cast<int>(PlatformID::PLATFORM_ANDROID_64)>("Android64")
            ->Enum<static_cast<int>(PlatformID::PLATFORM_APPLE_IOS)>("iOS")
            ->Enum<static_cast<int>(PlatformID::PLATFORM_APPLE_MAC)>("Mac")
#if defined(AZ_EXPAND_FOR_RESTRICTED_PLATFORM) || defined(AZ_TOOLS_EXPAND_FOR_RESTRICTED_PLATFORMS)
#define AZ_RESTRICTED_PLATFORM_EXPANSION(CodeName, CODENAME, codename, PrivateName, PRIVATENAME, privatename, PublicName, PUBLICNAME, publicname, PublicAuxName1, PublicAuxName2, PublicAuxName3)\
            ->Enum<static_cast<int>(PlatformID::PLATFORM_##PUBLICNAME)>(#CodeName)
#if defined(AZ_EXPAND_FOR_RESTRICTED_PLATFORM)
            AZ_EXPAND_FOR_RESTRICTED_PLATFORM
#else
            AZ_TOOLS_EXPAND_FOR_RESTRICTED_PLATFORMS
#endif
#undef AZ_RESTRICTED_PLATFORM_EXPANSION
#endif
            ->Property("Current", BehaviorConstant(AZ::g_currentPlatform), nullptr)
            ->Method("GetName", &AZ::GetPlatformName)
            ;

        behaviorContext->EBus<TickBus>("TickBus")
            ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
            ->Attribute(AZ::Script::Attributes::Module, "components")
            ->Handler<TickBusBehaviorHandler>()
            ;

        behaviorContext->EBus<TickRequestBus>("TickRequestBus")
            ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
            ->Attribute(AZ::Script::Attributes::Module, "components")
            ->Event("GetTickDeltaTime", &TickRequestBus::Events::GetTickDeltaTime)
            ->Event("GetTimeAtCurrentTick", &TickRequestBus::Events::GetTimeAtCurrentTick)
            ;

        behaviorContext->Class<DummyTickOrder>("TickOrder")
            ->Enum<TICK_FIRST>("First")
            ->Enum<TICK_PLACEMENT>("Placement")
            ->Enum<TICK_INPUT>("Input")
            ->Enum<TICK_GAME>("Game")
            ->Enum<TICK_ANIMATION>("Animation")
            ->Enum<TICK_PHYSICS>("Physics")
            ->Enum<TICK_ATTACHMENT>("Attachment")
            ->Enum<TICK_PRE_RENDER>("PreRender")
            ->Enum<TICK_DEFAULT>("Default")
            ->Enum<TICK_UI>("UI")
            ->Enum<TICK_LAST>("Last")
            ;
    }
}

#endif // #if !defined(AZCORE_EXCLUDE_LUA)
