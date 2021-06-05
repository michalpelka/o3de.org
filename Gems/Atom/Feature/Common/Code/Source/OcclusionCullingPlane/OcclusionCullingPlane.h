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

#include <Atom/Feature/OcclusionCullingPlane/OcclusionCullingPlaneFeatureProcessorInterface.h>
#include <Atom/Feature/Mesh/MeshFeatureProcessorInterface.h>

namespace AZ
{
    namespace Render
    {
        //! This class represents an OcclusionCullingPlane which is used to cull meshes that are inside the view frustum
        class OcclusionCullingPlane final
            : public AZ::Data::AssetBus::MultiHandler
        {
        public:
            OcclusionCullingPlane() = default;
            ~OcclusionCullingPlane();

            void Init(RPI::Scene* scene);

            void SetTransform(const AZ::Transform& transform);
            const AZ::Transform& GetTransform() const { return m_transform; }

            void SetEnabled(bool enabled) { m_enabled = enabled; }
            bool GetEnabled() const { return m_enabled; }

            // enables or disables rendering of the visualization plane
            void ShowVisualization(bool showVisualization);

            // sets the visualization to transparent mode
            void SetTransparentVisualization(bool transparentVisualization);

        private:

            void SetVisualizationMaterial();

            // AZ::Data::AssetBus::Handler overrides...
            void OnAssetReady(Data::Asset<Data::AssetData> asset) override;
            void OnAssetError(Data::Asset<Data::AssetData> asset) override;

            AZ::Transform m_transform;
            bool m_enabled = true;
            bool m_showVisualization = true;
            bool m_transparentVisualization = false;

            // visualization
            AZ::Render::MeshFeatureProcessorInterface* m_meshFeatureProcessor = nullptr;
            Data::Asset<RPI::ModelAsset> m_visualizationModelAsset;
            Data::Asset<RPI::MaterialAsset> m_visualizationMaterialAsset;
            Data::Instance<RPI::Material> m_visualizationMaterial;
            AZ::Render::MeshFeatureProcessorInterface::MeshHandle m_visualizationMeshHandle;
        };
    } // namespace Render
} // namespace AZ
