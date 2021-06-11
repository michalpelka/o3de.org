/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include <AzCore/Component/Entity.h>
#include <AzCore/Math/Sfmt.h>
#include <AzCore/StringFunc/StringFunc.h>
#include <AzCore/Utils/TypeHash.h>

#include <AzToolsFramework/Prefab/Instance/Instance.h>
#include <AzToolsFramework/Prefab/Instance/InstanceEntityIdMapper.h>
#include <AzToolsFramework/Prefab/Instance/InstanceEntityMapper.h>

namespace AzToolsFramework
{
    namespace Prefab
    {
        AZ::JsonSerializationResult::Result InstanceEntityIdMapper::MapJsonToId(AZ::EntityId& outputValue,
            const rapidjson::Value& inputValue, AZ::JsonDeserializerContext& context)
        {
            namespace JSR = AZ::JsonSerializationResult;

            if (!m_loadingInstance)
            {
                AZ_Assert(false,
                    "Attempted to map an EntityId in Prefab Instance without setting the Loading Prefab Instance");

                return context.Report(JSR::Tasks::WriteValue, JSR::Outcomes::DefaultsUsed,
                    "Attempted to map an EntityId in Prefab Instance without setting the Loading Prefab Instance");
            }

            AZ::EntityId mappedValue(AZ::EntityId::InvalidEntityId);
            EntityAlias inputAlias;

            if (inputValue.IsString())
            {
                inputAlias = EntityAlias(inputValue.GetString(), inputValue.GetStringLength());
            }

            if (!inputAlias.empty())
            {
                AliasPath absoluteEntityPath = m_loadingInstance->GetAbsoluteInstanceAliasPath();
                absoluteEntityPath.Append(inputAlias);
                absoluteEntityPath = absoluteEntityPath.LexicallyNormal();

                mappedValue = GenerateEntityIdForAliasPath(absoluteEntityPath, m_randomSeed);

                if (!m_isEntityReference)
                {
                    if (!m_loadingInstance->RegisterEntity(mappedValue, inputAlias))
                    {
                        mappedValue = AZ::EntityId(AZ::EntityId::InvalidEntityId);
                        context.Report(JSR::Tasks::ReadField, JSR::Outcomes::DefaultsUsed,
                            "Unable to register entity Id with prefab instance during load. Using default invalid id");
                    }
                }
            }

            outputValue = mappedValue;

            return context.Report(JSR::Tasks::ReadField, JSR::Outcomes::Success, "Successfully mapped Entity Id For Prefab Instance load");
        }

        AZ::JsonSerializationResult::Result InstanceEntityIdMapper::MapIdToJson(rapidjson::Value& outputValue,
            const AZ::EntityId& inputValue, AZ::JsonSerializerContext& context)
        {
            namespace JSR = AZ::JsonSerializationResult;

            if (!m_storingInstance)
            {
                return context.Report(JSR::Tasks::WriteValue, JSR::Outcomes::DefaultsUsed,
                    "Attempted to map an EntityId in Prefab Instance without setting the Storing Prefab Instance");
            }

            EntityAlias mappedValue;
            if (inputValue.IsValid())
            {
                if (m_isEntityReference)
                {
                    mappedValue = ResolveReferenceId(inputValue);
                }
                else
                {
                    auto idMapIter = m_storingInstance->m_instanceToTemplateEntityIdMap.find(inputValue);

                    if (idMapIter != m_storingInstance->m_instanceToTemplateEntityIdMap.end())
                    {
                        mappedValue = idMapIter->second;
                    }
                    else
                    {
                        AZStd::string defaultErrorMessage =
                            "Entity with Id " + inputValue.ToString() +
                            " could not be found within its owning instance. Defaulting to invalid Id for Store.";
                        context.Report(JSR::Tasks::WriteValue, JSR::Outcomes::DefaultsUsed, defaultErrorMessage);
                    }
                }
            }

            outputValue.SetString(rapidjson::StringRef(mappedValue.c_str(), mappedValue.length()), context.GetJsonAllocator());

            return context.Report(JSR::Tasks::WriteValue, JSR::Outcomes::Success, "Successfully mapped Entity Id For Prefab Instance store");
        }

        void InstanceEntityIdMapper::SetEntityIdGenerationApproach(EntityIdGenerationApproach approach)
        {
            m_entityIdGenerationApproach = approach;

            if (m_entityIdGenerationApproach == EntityIdGenerationApproach::Hashed)
            {
                m_randomSeed = SeedKey;
            }
            else if (m_entityIdGenerationApproach == EntityIdGenerationApproach::Random)
            {
                m_randomSeed = AZ::Sfmt::GetInstance().Rand64();

                // Sanity check to avoid collision with hashed mode
                if (m_randomSeed == SeedKey)
                {
                    m_randomSeed++;
                }
            }
            else
            {
                AZ_Assert(false, "Unsupported option in EntityIdGenerationApproach encountered."
                    " Defaulting to Hashed");

                m_randomSeed = SeedKey;
            }
        }

        void InstanceEntityIdMapper::SetStoringInstance(const Instance& storingInstance)
        {
            m_storingInstance = &storingInstance;
            m_instanceAbsolutePath = m_storingInstance->GetAbsoluteInstanceAliasPath();
        }

        void InstanceEntityIdMapper::SetLoadingInstance(Instance& loadingInstance)
        {
            m_loadingInstance = &loadingInstance;
        }

        EntityAlias InstanceEntityIdMapper::ResolveReferenceId(const AZ::EntityId& entityId)
        {
            // Acquire the owning instance of our entity
            InstanceOptionalReference owningInstanceReference = m_storingInstance->m_instanceEntityMapper->FindOwningInstance(entityId);

            // Start with an empty alias to build out our reference path
            // If we can't resolve this id we'll return a new alias based on the entity ID instead of a reference path
            AliasPath relativeEntityAliasPath;
            if (!owningInstanceReference)
            {
                AZ_Warning("Prefabs", false,
                    "Prefab - EntityIdMapper: Entity with Id %s has no registered owning instance",
                    entityId.ToString().c_str());

                return AZStd::string::format("Entity_%s", entityId.ToString().c_str());
            }

            Instance* owningInstance = &(owningInstanceReference->get());

            // Build out the absolute path of this alias
            // so we can compare it to the absolute path of our currently scoped instance
            relativeEntityAliasPath = owningInstance->GetAbsoluteInstanceAliasPath();
            relativeEntityAliasPath.Append(owningInstance->GetEntityAlias(entityId)->get());

            return relativeEntityAliasPath.LexicallyRelative(m_instanceAbsolutePath).String();
        }

        AZ::EntityId InstanceEntityIdMapper::GenerateEntityIdForAliasPath(const AliasPathView& aliasPath, uint64_t seedKey)
        {
            const AZ::HashValue64 seed = aznumeric_cast<AZ::HashValue64>(seedKey);
            return AZ::EntityId(aznumeric_cast<AZ::u64>((AZ::TypeHash64(aliasPath.Native().data(), seed))));
        }
    }
}
