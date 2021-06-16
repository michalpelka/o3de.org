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
#pragma once

#include <Atom/RPI.Reflect/AssetCreator.h>
#include <Atom/RPI.Reflect/Shader/ShaderAsset.h>

#include <AzCore/std/containers/map.h>

namespace AZ
{
    namespace RPI
    {
        class ShaderAssetCreator
            : public AssetCreator<ShaderAsset>
        {
        public:
            //! Begins creation of a shader asset.
            void Begin(const Data::AssetId& assetId);

            //! [Optional] Set the timestamp for when the ShaderAsset build process began.
            //! This is needed to synchronize between the ShaderAsset and ShaderVariantTreeAsset when hot-reloading shaders.
            void SetShaderAssetBuildTimestamp(AZStd::sys_time_t shaderAssetBuildTimestamp);

            //! [Optional] Sets the name of the shader asset from content.
            void SetName(const Name& name);
            
            //! [Optional] Sets the DrawListTag name associated with this shader.
            void SetDrawListName(const Name& name);

            //! [Required] Assigns the layout used to construct and parse shader options packed into shader variant keys.
            //! Requires that the keys assigned to shader variants were constructed using the same layout.
            void SetShaderOptionGroupLayout(const Ptr<ShaderOptionGroupLayout>& shaderOptionGroupLayout);

            //! Begins the shader creation for a specific RHI API.
            //! Begin must be called before the BeginAPI function is called.
            //! @param type The target RHI API type.
            void BeginAPI(RHI::APIType type);

            //! Begins the creation of a Supervariant for the current RHI::APIType.
            //! If this is the first supervariant its name must be empty. The first
            //! supervariant is always the default, nameless, supervariant.
            void BeginSupervariant(const Name& name);

            void SetSrgLayoutList(const ShaderResourceGroupLayoutList& srgLayoutList);

            //! [Required] Assigns the pipeline layout descriptor shared by all variants in the shader. Shader variants
            //! embedded in a single shader asset are required to use the same pipeline layout. It is not necessary to call
            //! Finalize() on the pipeline layout prior to assignment, but still permitted.
            void SetPipelineLayout(RHI::Ptr<RHI::PipelineLayoutDescriptor> m_pipelineLayoutDescriptor);

            //! Assigns the contract for inputs required by the shader.
            void SetInputContract(const ShaderInputContract& contract);

            //! Assigns the contract for outputs required by the shader.
            void SetOutputContract(const ShaderOutputContract& contract);

            //! Assigns the render states for the draw pipeline. Ignored for non-draw pipelines.
            void SetRenderStates(const RHI::RenderStates& renderStates);

            //! [Optional] Not all shaders have attributes before functions. Some attributes do not exist for all RHI::APIType either.
            void SetShaderStageAttributeMapList(const RHI::ShaderStageAttributeMapList& shaderStageAttributeMapList);

            //! [Required] There's always a root variant for each supervariant.
            void SetRootShaderVariantAsset(Data::Asset<ShaderVariantAsset> shaderVariantAsset);

            bool EndSupervariant();

            bool EndAPI();

            bool End(Data::Asset<ShaderAsset>& shaderAsset);

            //! Clones an existing ShaderAsset nd replaces the referenced Srg and Variant assets
            using ShaderRootVariantAssets = AZStd::vector<AZStd::pair<AZ::Crc32, Data::Asset<RPI::ShaderVariantAsset>>>;
            void Clone(const Data::AssetId& assetId,
                       const ShaderAsset& sourceShaderAsset,
                       const ShaderRootVariantAssets& rootVariantAssets);

        private:

            // Shader variants will use this draw list when they don't specify one.
            Name m_defaultDrawList;

            // The current supervariant is cached here to facilitate asset
            // construction. Additionally, prevents BeginSupervariant to be called more than once before calling EndSupervariant.
            ShaderAsset::Supervariant* m_currentSupervariant = nullptr;

        };
    } // namespace RPI
} // namespace AZ
