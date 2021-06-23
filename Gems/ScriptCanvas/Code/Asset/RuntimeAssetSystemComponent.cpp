/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/Asset/AssetManager.h>
#include <AzCore/Serialization/SerializeContext.h>

#include <ScriptCanvas/Asset/RuntimeAsset.h>
#include <ScriptCanvas/Asset/RuntimeAssetHandler.h>
#include <Asset/RuntimeAssetSystemComponent.h>
#include <Asset/Functions/RuntimeFunctionAssetHandler.h>

namespace ScriptCanvas
{
    RuntimeAssetSystemComponent::~RuntimeAssetSystemComponent()
    {
    }

    void RuntimeAssetSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        ScriptCanvas::RuntimeData::Reflect(context);
        ScriptCanvas::SubgraphInterfaceData::Reflect(context);
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<RuntimeAssetSystemComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void RuntimeAssetSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("ScriptCanvasRuntimeAssetService", 0x1a85bf2b));
    }

    void RuntimeAssetSystemComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        required.push_back(AZ_CRC("AssetDatabaseService", 0x3abf5601));
        required.push_back(AZ_CRC("ScriptCanvasService", 0x41fd58f3));
    }

    void RuntimeAssetSystemComponent::GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        dependent.push_back(AZ_CRC("AssetCatalogService", 0xc68ffc57));
    }

    void RuntimeAssetSystemComponent::Init()
    {
    }

    void RuntimeAssetSystemComponent::Activate()
    {
        m_runtimeAssetRegistry.Register<ScriptCanvas::RuntimeAsset, ScriptCanvas::RuntimeAssetHandler, ScriptCanvas::RuntimeAssetDescription>();
        m_runtimeAssetRegistry.Register<ScriptCanvas::SubgraphInterfaceAsset, ScriptCanvas::SubgraphInterfaceAssetHandler, ScriptCanvas::SubgraphInterfaceAssetDescription>();
    }

    void RuntimeAssetSystemComponent::Deactivate()
    {
        m_runtimeAssetRegistry.Unregister();
    }

    AssetRegistry& RuntimeAssetSystemComponent::GetAssetRegistry()
    {
        return m_runtimeAssetRegistry;
    }

}
