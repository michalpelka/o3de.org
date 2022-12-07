/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <Atom/RPI.Reflect/Material/MaterialAsset.h>
#include <Atom/RPI.Reflect/Material/MaterialPropertiesLayout.h>
#include <Atom/RPI.Reflect/Material/MaterialFunctor.h>
#include <Atom/RPI.Reflect/Material/MaterialVersionUpdate.h>
#include <Atom/RPI.Reflect/Asset/AssetHandler.h>
#include <Atom/RPI.Public/Shader/ShaderReloadDebugTracker.h>

#include <AzCore/Asset/AssetSerializer.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/Component/TickBus.h>

namespace AZ
{
    namespace RPI
    {
        const char* MaterialAsset::s_debugTraceName = "MaterialAsset";

        const char* MaterialAsset::DisplayName = "MaterialAsset";
        const char* MaterialAsset::Group = "Material";
        const char* MaterialAsset::Extension = "azmaterial";

        void MaterialAsset::Reflect(ReflectContext* context)
        {
            if (auto* serializeContext = azrtti_cast<SerializeContext*>(context))
            {
                serializeContext->Class<MaterialAsset, AZ::Data::AssetData>()
                    ->Version(14) // added m_rawPropertyValues
                    ->Field("materialTypeAsset", &MaterialAsset::m_materialTypeAsset)
                    ->Field("materialTypeVersion", &MaterialAsset::m_materialTypeVersion)
                    ->Field("propertyValues", &MaterialAsset::m_propertyValues)
                    ->Field("rawPropertyValues", &MaterialAsset::m_rawPropertyValues)
                    ->Field("finalized", &MaterialAsset::m_wasPreFinalized)
                    ;
            }
        }

        MaterialAsset::MaterialAsset()
        {
        }

        MaterialAsset::~MaterialAsset()
        {
            AssetInitBus::Handler::BusDisconnect();
        }

        const Data::Asset<MaterialTypeAsset>& MaterialAsset::GetMaterialTypeAsset() const
        {
            return m_materialTypeAsset;
        }

        const MaterialPipelineShaderCollections& MaterialAsset::GetShaderCollections() const
        {
            return m_materialTypeAsset->GetShaderCollections();
        }

        const ShaderCollection& MaterialAsset::GetShaderCollection(const Name& forPipeline) const
        {
            return m_materialTypeAsset->GetShaderCollection(forPipeline);
        }

        const MaterialFunctorList& MaterialAsset::GetMaterialFunctors() const
        {
            return m_materialTypeAsset->GetMaterialFunctors();
        }

        const RHI::Ptr<RHI::ShaderResourceGroupLayout>& MaterialAsset::GetMaterialSrgLayout(const SupervariantIndex& supervariantIndex) const
        {
            return m_materialTypeAsset->GetMaterialSrgLayout(supervariantIndex);
        }

        const RHI::Ptr<RHI::ShaderResourceGroupLayout>& MaterialAsset::GetMaterialSrgLayout(const AZ::Name& supervariantName) const
        {
            return m_materialTypeAsset->GetMaterialSrgLayout(supervariantName);
        }

        const RHI::Ptr<RHI::ShaderResourceGroupLayout>& MaterialAsset::GetMaterialSrgLayout() const
        {
            return m_materialTypeAsset->GetMaterialSrgLayout();
        }

        const RHI::Ptr<RHI::ShaderResourceGroupLayout>& MaterialAsset::GetObjectSrgLayout(const SupervariantIndex& supervariantIndex) const
        {
            return m_materialTypeAsset->GetObjectSrgLayout(supervariantIndex);
        }

        const RHI::Ptr<RHI::ShaderResourceGroupLayout>& MaterialAsset::GetObjectSrgLayout(const AZ::Name& supervariantName) const
        {
            return m_materialTypeAsset->GetObjectSrgLayout(supervariantName);
        }

        const RHI::Ptr<RHI::ShaderResourceGroupLayout>& MaterialAsset::GetObjectSrgLayout() const
        {
            return m_materialTypeAsset->GetObjectSrgLayout();
        }

        const MaterialPropertiesLayout* MaterialAsset::GetMaterialPropertiesLayout() const
        {
            return m_materialTypeAsset->GetMaterialPropertiesLayout();
        }
        
        bool MaterialAsset::WasPreFinalized() const
        {
            return m_wasPreFinalized;
        }

        void MaterialAsset::Finalize(AZStd::function<void(const char*)> reportWarning, AZStd::function<void(const char*)> reportError)
        {
            if (m_wasPreFinalized)
            {
                m_isFinalized = true;
            }

            if (m_isFinalized)
            {
                return;
            }

            if (!reportWarning)
            {
                reportWarning = []([[maybe_unused]] const char* message)
                {
                    AZ_Warning(s_debugTraceName, false, "%s", message);
                };
            }
            
            if (!reportError)
            {
                reportError = []([[maybe_unused]] const char* message)
                {
                    AZ_Error(s_debugTraceName, false, "%s", message);
                };
            }

            // It is possible that the material type has had some properties renamed or otherwise updated. If that's the case,
            // and this material is still referencing the old property layout, we need to apply any auto updates to rename those
            // properties before using them to realign the property values.
            ApplyVersionUpdates(reportError);

            const MaterialPropertiesLayout* propertyLayout = GetMaterialPropertiesLayout();

            AZStd::vector<MaterialPropertyValue> finalizedPropertyValues(m_materialTypeAsset->GetDefaultPropertyValues().begin(), m_materialTypeAsset->GetDefaultPropertyValues().end());

            for (const auto& [name, value] : m_rawPropertyValues)
            {
                const MaterialPropertyIndex propertyIndex = propertyLayout->FindPropertyIndex(name);
                if (propertyIndex.IsValid())
                {
                    const MaterialPropertyDescriptor* propertyDescriptor = propertyLayout->GetPropertyDescriptor(propertyIndex);

                    if (value.Is<AZStd::string>() && propertyDescriptor->GetDataType() == MaterialPropertyDataType::Enum)
                    {
                        AZ::Name enumName = AZ::Name(value.GetValue<AZStd::string>());
                        uint32_t enumValue = propertyDescriptor->GetEnumValue(enumName);
                        if (enumValue == MaterialPropertyDescriptor::InvalidEnumValue)
                        {
                            reportWarning(AZStd::string::format("Material property name \"%s\" has invalid enum value \"%s\".", name.GetCStr(), enumName.GetCStr()).c_str());
                        }
                        else
                        {
                            finalizedPropertyValues[propertyIndex.GetIndex()] = enumValue;
                        }
                    }
                    else if (value.Is<AZStd::string>() && propertyDescriptor->GetDataType() == MaterialPropertyDataType::Image)
                    {
                        // Here we assume that the material asset builder resolved any image source file paths to an ImageAsset reference.
                        // So the only way a string could be present is if it's an empty image path reference, meaning no image should be bound.
                        AZ_Assert(value.GetValue<AZStd::string>().empty(), "Material property '%s' references in image '%s'. Image file paths must be resolved by the material asset builder.");

                        finalizedPropertyValues[propertyIndex.GetIndex()] = Data::Asset<ImageAsset>{};
                    }
                    else
                    {
                        // The material asset could be finalized sometime after the original JSON is loaded, and the material type might not have been available
                        // at that time, so the data type would not be known for each property. So each raw property's type was based on what appeared in the JSON
                        // and here we have the first opportunity to resolve that value with the actual type. For example, a float property could have been specified in
                        // the JSON as 7 instead of 7.0, which is valid. Similarly, a Color and a Vector3 can both be specified as "[0.0,0.0,0.0]" in the JSON file.

                        MaterialPropertyValue finalValue = value.CastToType(propertyDescriptor->GetStorageDataTypeId());

                        if (ValidateMaterialPropertyDataType(finalValue.GetTypeId(), name, propertyDescriptor, reportError))
                        {
                            finalizedPropertyValues[propertyIndex.GetIndex()] = finalValue;
                        }
                    }
                }
                else
                {
                    reportWarning(AZStd::string::format("Material property name \"%s\" is not found in the material properties layout and will not be used.", name.GetCStr()).c_str());
                }
            }

            m_propertyValues.swap(finalizedPropertyValues);

            m_isFinalized = true;
        }

        const AZStd::vector<MaterialPropertyValue>& MaterialAsset::GetPropertyValues()
        {
            // This can't be done in MaterialAssetHandler::LoadAssetData because the MaterialTypeAsset isn't necessarily loaded at that point.
            // And it can't be done in PostLoadInit() because that happens on the next frame which might be too late.
            // And overriding AssetHandler::InitAsset in MaterialAssetHandler didn't work, because there seems to be non-determinism on the order
            // of InitAsset calls when a ModelAsset references a MaterialAsset, the model gets initialized first and then fails to use the material.
            // So we finalize just-in-time when properties are accessed.
            // If we could solve the problem with InitAsset, that would be the ideal place to call Finalize() and we could make GetPropertyValues() const again.
            Finalize();

            AZ_Assert(GetMaterialPropertiesLayout() && m_propertyValues.size() == GetMaterialPropertiesLayout()->GetPropertyCount(), "MaterialAsset should be finalized but does not have the right number of property values.");
        
            return m_propertyValues;
        }
        
        const AZStd::vector<AZStd::pair<Name, MaterialPropertyValue>>& MaterialAsset::GetRawPropertyValues() const
        {
            return m_rawPropertyValues;
        }

        void MaterialAsset::SetReady()
        {
            m_status = AssetStatus::Ready;

            // If this was created dynamically using MaterialAssetCreator (which is what calls SetReady()),
            // we need to connect to the AssetBus for reloads.
            PostLoadInit();
        }

        bool MaterialAsset::PostLoadInit()
        {
            if (!m_materialTypeAsset.Get())
            {
                AssetInitBus::Handler::BusDisconnect();

                // Any MaterialAsset with invalid MaterialTypeAsset is not a successfully-loaded asset.
                return false;
            }
            else
            {
                AssetInitBus::Handler::BusDisconnect();

                return true;
            }
        }

        void MaterialAsset::ApplyVersionUpdates(AZStd::function<void(const char*)> reportError)
        {
            if (m_materialTypeVersion == m_materialTypeAsset->GetVersion())
            {
                return;
            }
            [[maybe_unused]] const uint32_t originalVersion = m_materialTypeVersion;

            [[maybe_unused]] bool changesWereApplied =
                m_materialTypeAsset->GetMaterialVersionUpdates().ApplyVersionUpdates(*this, reportError);

#if AZ_ENABLE_TRACING
            if (changesWereApplied)
            {
                const AZStd::string versionString = (originalVersion == UnspecifiedMaterialTypeVersion) ?
                    "<Unspecified>" : AZStd::string::format("'%u'", originalVersion);

                AZStd::string assetString = GetId().ToString<AZStd::string>().c_str();

                AZ::Data::AssetInfo assetInfo;
                AZ::Data::AssetCatalogRequestBus::BroadcastResult(assetInfo,
                    &AZ::Data::AssetCatalogRequestBus::Events::GetAssetInfoById, GetId());
                if (assetInfo.m_assetId.IsValid())
                {
                    assetString += " (" + assetInfo.m_relativePath + ")";
                }

                AZ_Warning(
                    "MaterialAsset", false,
                    "This material is based on version %s of %s, and the material type is now at version '%u'. "
                    "Automatic updates have been applied. Consider updating the .material source file for %s.",
                    versionString.c_str(), m_materialTypeAsset.ToString<AZStd::string>().c_str(),
                    m_materialTypeAsset->GetVersion(), assetString.c_str());
            }
#endif

            m_materialTypeVersion = m_materialTypeAsset->GetVersion();
        }

        Data::AssetHandler::LoadResult MaterialAssetHandler::LoadAssetData(
            const AZ::Data::Asset<AZ::Data::AssetData>& asset,
            AZStd::shared_ptr<AZ::Data::AssetDataStream> stream,
            const AZ::Data::AssetFilterCB& assetLoadFilterCB)
        {
            if (Base::LoadAssetData(asset, stream, assetLoadFilterCB) == Data::AssetHandler::LoadResult::LoadComplete)
            {
                asset.GetAs<MaterialAsset>()->AssetInitBus::Handler::BusConnect();
                return Data::AssetHandler::LoadResult::LoadComplete;
            }

            return Data::AssetHandler::LoadResult::Error;
        }

    } // namespace RPI
} // namespace AZ
