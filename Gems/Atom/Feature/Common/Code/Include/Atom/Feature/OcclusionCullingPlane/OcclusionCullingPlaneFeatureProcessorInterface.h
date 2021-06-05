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

#include <AzCore/base.h>
#include <AzCore/Math/Transform.h>
#include <Atom/RPI.Public/FeatureProcessor.h>

namespace AZ
{
    namespace Render
    {
        class OcclusionCullingPlane;

        using OcclusionCullingPlaneHandle = AZStd::shared_ptr<OcclusionCullingPlane>;

        // OcclusionCullingPlaneFeatureProcessorInterface provides an interface to the feature processor for code outside of Atom
        class OcclusionCullingPlaneFeatureProcessorInterface
            : public RPI::FeatureProcessor
        {
        public:
            AZ_RTTI(AZ::Render::OcclusionCullingPlaneFeatureProcessorInterface, "{50F6B45E-A622-44EC-B962-DE25FBD44095}");

            virtual OcclusionCullingPlaneHandle AddOcclusionCullingPlane(const AZ::Transform& transform) = 0;
            virtual void RemoveOcclusionCullingPlane(OcclusionCullingPlaneHandle& handle) = 0;
            virtual bool IsValidOcclusionCullingPlaneHandle(const OcclusionCullingPlaneHandle& occlusionCullingPlane) const = 0;
            virtual void SetTransform(const OcclusionCullingPlaneHandle& occlusionCullingPlane, const AZ::Transform& transform) = 0;
            virtual void SetEnabled(const OcclusionCullingPlaneHandle& occlusionCullingPlane, bool enabled) = 0;
            virtual void ShowVisualization(const OcclusionCullingPlaneHandle& occlusionCullingPlane, bool showVisualization) = 0;
            virtual void SetTransparentVisualization(const OcclusionCullingPlaneHandle& occlusionCullingPlane, bool transparentVisualization) = 0;
        };
    } // namespace Render
} // namespace AZ
