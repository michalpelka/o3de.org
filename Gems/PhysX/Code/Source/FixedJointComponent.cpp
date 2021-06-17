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
#include <PhysX_precompiled.h>

#include <Source/FixedJointComponent.h>
#include <PhysX/MathConversion.h>
#include <PhysX/PhysXLocks.h>
#include <AzCore/Component/TransformBus.h>
#include <AzFramework/Physics/SimulatedBodies/RigidBody.h>
#include <AzFramework/Physics/RigidBodyBus.h>
#include <PhysX/Joint/Configuration/PhysXJointConfiguration.h>
#include <AzFramework/Physics/PhysicsScene.h>
#include <AzCore/Interface/Interface.h>

#include <PxPhysicsAPI.h>

namespace PhysX
{
    void FixedJointComponent::Reflect(AZ::ReflectContext* context)
    {
        AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context);
        if (serializeContext)
        {
            serializeContext->Class<FixedJointComponent, JointComponent>()
                ->Version(2)
                ;
        }
    }

    FixedJointComponent::FixedJointComponent(
        const JointComponentConfiguration& configuration, 
        const JointGenericProperties& genericProperties)
        : JointComponent(configuration, genericProperties)
    {
    }

    FixedJointComponent::FixedJointComponent(
        const JointComponentConfiguration& configuration, 
        const JointGenericProperties& genericProperties,
        const JointLimitProperties& limitProperties)
        : JointComponent(configuration, genericProperties, limitProperties)
    {
    }

    void FixedJointComponent::InitNativeJoint()
    {
        if (m_jointHandle != AzPhysics::InvalidJointHandle)
        {
            return;
        }

        JointComponent::LeadFollowerInfo leadFollowerInfo;
        ObtainLeadFollowerInfo(leadFollowerInfo);
        if (!leadFollowerInfo.m_followerActor)
        {
            return;
        }

        FixedJointConfiguration configuration;
        configuration.m_parentLocalPosition = leadFollowerInfo.m_leadLocal.GetTranslation();
        configuration.m_parentLocalRotation = leadFollowerInfo.m_leadLocal.GetRotation();
        configuration.m_childLocalPosition = leadFollowerInfo.m_followerLocal.GetTranslation();
        configuration.m_childLocalRotation = leadFollowerInfo.m_followerLocal.GetRotation();

        configuration.m_genericProperties = m_genericProperties;

        if (auto* sceneInterface = AZ::Interface<AzPhysics::SceneInterface>::Get())
        {
            m_jointHandle = sceneInterface->AddJoint(
                leadFollowerInfo.m_followerBody->m_sceneOwner,
                &configuration,  
                leadFollowerInfo.m_leadBody->m_bodyHandle, 
                leadFollowerInfo.m_followerBody->m_bodyHandle);
            m_jointSceneOwner = leadFollowerInfo.m_followerBody->m_sceneOwner;
        }
    }
} // namespace PhysX
