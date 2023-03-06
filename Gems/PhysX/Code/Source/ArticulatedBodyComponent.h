/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/EntityBus.h>
#include <AzCore/Component/TransformBus.h>
#include <AzFramework/Physics/Components/SimulatedBodyComponentBus.h>
#include <AzFramework/Physics/RigidBodyBus.h>
#include <PhysX/ComponentTypeIds.h>
#include "AzFramework/Physics/Common/PhysicsEvents.h"
#include "AzFramework/Physics/Shape.h"
#include "RigidBody.h"
#include "PhysX/Joint/Configuration/PhysXJointConfiguration.h"

namespace physx
{
    class PxArticulationReducedCoordinate;
    class PxArticulationJointReducedCoordinate;
}


namespace AzPhysics
{
    struct SimulatedBody;
}

namespace PhysX
{
    class StaticRigidBody;

    struct ArticulationLinkData
    {
        AZ_CLASS_ALLOCATOR(ArticulationLinkData, AZ::SystemAllocator, 0);
        AZ_RTTI(ArticulationLinkData, "{C9862FF7-FFAC-4A49-A51D-A555C4303F74}");
        virtual ~ArticulationLinkData();
        static void Reflect(AZ::ReflectContext* context);
        void Reset();
        AZStd::shared_ptr<Physics::ShapeConfiguration> m_shapeConfiguration;
        Physics::ColliderConfiguration m_colliderConfiguration;
        AZ::EntityId m_entityId;

        AzPhysics::RigidBodyConfiguration m_config; //!< Generic properties from AzPhysics.
        RigidBodyConfiguration
            m_physxSpecificConfig; //!< Properties specific to PhysX which might not have exact equivalents in other physics engines.
        JointGenericProperties m_genericProperties;
        JointLimitProperties m_limits;
        JointMotorProperties m_motor;

        AZStd::vector<AZStd::shared_ptr<ArticulationLinkData>> m_childLinks;
    };

    class ArticulatedBodyComponent final
        : public AZ::Component
        , private AZ::TransformNotificationBus::Handler
    {
    public:
        AZ_COMPONENT(ArticulatedBodyComponent, ArticulatedBodyComponentTypeId);

        ArticulatedBodyComponent();
        explicit ArticulatedBodyComponent(AzPhysics::SceneHandle sceneHandle);
        ~ArticulatedBodyComponent();

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);
        ArticulationLinkData m_articulationLinkData;

    private:
        void CreateRigidBody();
        void DestroyRigidBody();

        bool IsRootArticulation() const;
        void UpdateArticulationHierarchy();

        // AZ::Component
        void Activate() override;

        void CreateArticulation();

        void Deactivate() override;

        // AZ::TransformNotificationsBus
        void OnTransformChanged(const AZ::Transform& local, const AZ::Transform& world) override;
        void SetupSample();
        physx::PxArticulationReducedCoordinate* m_articulation = nullptr;
        physx::PxArticulationJointReducedCoordinate* m_driveJoint = nullptr;
        bool m_tempClosing = true;

        AzPhysics::SimulatedBodyHandle m_staticRigidBodyHandle = AzPhysics::InvalidSimulatedBodyHandle;
        AzPhysics::SceneHandle m_attachedSceneHandle = AzPhysics::InvalidSceneHandle;
        AzPhysics::SceneEvents::OnSceneSimulationFinishHandler m_sceneFinishSimHandler;

    };
} // namespace PhysX
