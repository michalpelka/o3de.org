/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzToolsFramework/ViewportUi/ViewportUiRequestBus.h>
#include <Editor/Plugins/Ragdoll/RagdollManipulators.h>
#include <AzCore/Math/Transform.h>

namespace EMotionFX
{
    class Actor;
    class Node;
    class Transform;

    struct RagdollViewportUiClusterData
    {
    };

    class RagdollViewportUiCluster
    {
    public:

        RagdollViewportUiCluster();
        void CreateClusterIfNoneExists(RagdollManipulatorData ragdollManipulatorData);
        void DestroyClusterIfExists();

        enum class SubMode : AZ::u32
        {
            ColliderTranslation,
            NumModes
        };

    private:
        void SetCurrentMode(SubMode mode, const RagdollManipulatorData& ragdollManipulatorData);

        AzToolsFramework::ViewportUi::ClusterId m_clusterId = AzToolsFramework::ViewportUi::InvalidClusterId;
        AZStd::vector<AzToolsFramework::ViewportUi::ButtonId> m_buttonIds;
        AZStd::unordered_map<SubMode, AZStd::unique_ptr<RagdollManipulatorsBase>> m_subModes;
        SubMode m_subMode = SubMode::ColliderTranslation;
        AZ::Event<AzToolsFramework::ViewportUi::ButtonId>::Handler
            m_modeSelectionHandler; //!< Event handler for sub mode changes.
        RagdollManipulatorData m_ragdollManipulatorData;
    };
} // namespace EMotionFX
