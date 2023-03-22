/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/Serialization/EditContext.h>
#include <AzToolsFramework/ToolsComponents/TransformComponent.h>

#include <Source/ArticulationLinkComponent.h>
#include <Source/EditorArticulationLinkComponent.h>
#include <Source/EditorColliderComponent.h>

namespace PhysX
{
    void EditorArticulationLinkComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<EditorArticulationLinkComponent, AzToolsFramework::Components::EditorComponentBase>()
                ->Version(1)
                ->Field("Configuration", &EditorArticulationLinkComponent::m_config)
                ->Field("PhysXSpecificConfiguration", &EditorArticulationLinkComponent::m_physxSpecificConfig)
                ->Field("JointConfig", &EditorArticulationLinkComponent::m_jointConfig)
            ;

            if (auto* editContext = serializeContext->GetEditContext())
            {
                constexpr const char* ToolTip = "Articulated rigid body.";

                editContext
                    ->Class<EditorArticulationLinkComponent>("PhysX Articulation Link", ToolTip)
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "PhysX")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/PhysXRigidBody.svg")
                    ->Attribute(AZ::Edit::Attributes::ViewportIcon, "Icons/Components/Viewport/PhysXRigidBody.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                    ->Attribute(
                        AZ::Edit::Attributes::HelpPageURL, "")

                    ->DataElement(
                        AZ::Edit::UIHandlers::Default,
                        &EditorArticulationLinkComponent::m_config,
                        "Configuration",
                        "Configuration for rigid body physics.")
                    ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                    ->DataElement(
                        AZ::Edit::UIHandlers::Default,
                        &EditorArticulationLinkComponent::m_physxSpecificConfig,
                        "PhysX-Specific Configuration",
                        "Settings which are specific to PhysX, rather than generic.")
                    ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)

                    ->DataElement(
                        AZ::Edit::UIHandlers::Default,
                        &EditorArticulationLinkComponent::m_jointConfig,
                        "Joint Configuration",
                        "Joint configuration for the articulation link.")
                    ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                ;
            }
        }
    }

    void EditorArticulationLinkComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("PhysicsWorldBodyService"));
        provided.push_back(AZ_CRC_CE("PhysicsRigidBodyService"));
    }

    void EditorArticulationLinkComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("PhysicsRigidBodyService"));
    }

    void EditorArticulationLinkComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        required.push_back(AZ_CRC_CE("TransformService"));
    }

    void EditorArticulationLinkComponent::GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        dependent.push_back(AZ_CRC_CE("NonUniformScaleService"));
    }

    bool EditorArticulationLinkComponent::IsRootArticulation() const
    {
        return IsRootArticulationEntity<EditorArticulationLinkComponent>(GetEntity());
    }

    void EditorArticulationLinkComponent::Activate()
    {
        AzToolsFramework::Components::EditorComponentBase::Activate();
    }

    void EditorArticulationLinkComponent::Deactivate()
    {
        AzToolsFramework::Components::EditorComponentBase::Deactivate();
    }

    void EditorArticulationLinkComponent::BuildGameEntity(AZ::Entity* gameEntity)
    {
        gameEntity->CreateComponent<ArticulationLinkComponent>();
    }
} // namespace PhysX
