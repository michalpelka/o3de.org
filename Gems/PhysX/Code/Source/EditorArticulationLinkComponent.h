/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzToolsFramework/ToolsComponents/EditorComponentBase.h>
#include <Editor/EditorJointConfiguration.h>
#include <Source/EditorRigidBodyComponent.h>
#include <Source/Articulation/ArticulationLinkConfiguration.h>

namespace PhysX
{
    class EditorArticulationLinkComponent;

    //! Configuration data for EditorRigidBodyComponent.
     struct EditorArticulationLinkConfiguration
         : public ArticulationLinkConfiguration
    {
        AZ_CLASS_ALLOCATOR(EditorArticulationLinkConfiguration, AZ::SystemAllocator);
        AZ_RTTI(
            EditorArticulationLinkConfiguration,
            "{8FFA0EC2-E850-4562-AB3D-08D157E07B81}",
            ArticulationLinkConfiguration);

        const EditorArticulationLinkComponent* m_component = nullptr;
        EditorJointLimitLinearPairConfig m_linearLimits;
        EditorJointLimitPairConfig m_angularLimits;

        static void Reflect(AZ::ReflectContext* context);

        void SetArticulationComponent(const EditorArticulationLinkComponent* component);
        bool IsRootArticulation() const override;
        bool IsNotRootArticulation() const override;
    };

    //! Class for in-editor PhysX Articulation Link Component.
    class EditorArticulationLinkComponent
        : public AzToolsFramework::Components::EditorComponentBase
    {
    public:
        AZ_EDITOR_COMPONENT(
            EditorArticulationLinkComponent, "{7D23169B-3214-4A32-ABFC-FCCE6E31F2CF}", AzToolsFramework::Components::EditorComponentBase);
        static void Reflect(AZ::ReflectContext* context);

        EditorArticulationLinkComponent();
        explicit EditorArticulationLinkComponent(const EditorArticulationLinkConfiguration& configuration);
        ~EditorArticulationLinkComponent() = default;

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // EditorComponentBase overrides ...
        void Activate() override;
        void Deactivate() override;

        void BuildGameEntity(AZ::Entity* gameEntity) override;

        bool IsRootArticulation() const;

    private:
        EditorArticulationLinkConfiguration m_config;
    };
} // namespace PhysX
