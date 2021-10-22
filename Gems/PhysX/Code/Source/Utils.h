/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <PhysX/ForceRegionComponentBus.h>

#include <AzCore/Math/Quaternion.h>
#include <AzCore/Math/Transform.h>
#include <AzCore/Math/Vector3.h>
#include <AzFramework/Physics/Material.h>
#include <AzFramework/Physics/Shape.h>
#include <AzFramework/Physics/ShapeConfiguration.h>
#include <AzCore/std/optional.h>

#include <PxPhysicsAPI.h>

namespace AzPhysics
{
    class CollisionGroup;
    struct RigidBodyConfiguration;
    struct StaticRigidBodyConfiguration;
    struct StaticRigidBody;
    class Scene;
}

namespace Physics
{
    class RigidBodyConfiguration;
    class ColliderConfiguration;
    class ShapeConfiguration;
}

namespace PhysX
{
    class Shape;
    class ActorData;
    class Material;
    struct TerrainConfiguration;

    namespace Pipeline
    {
        class MeshAssetData;
    } // namespace Pipeline

    namespace Utils
    {
        bool CreatePxGeometryFromConfig(const Physics::ShapeConfiguration& shapeConfiguration, physx::PxGeometryHolder& pxGeometry);

        physx::PxShape* CreatePxShapeFromConfig(
            const Physics::ColliderConfiguration& colliderConfiguration, 
            const Physics::ShapeConfiguration& shapeConfiguration, 
            AzPhysics::CollisionGroup& assignedCollisionGroup
        );

        AzPhysics::Scene* GetDefaultScene();

        //! Creates a PhysX cooked mesh config from the given points.
        //! 
        //! @param pointList Vector of points to build the mesh from.
        //! @param scale Scale to be assigned to the cooked mesh.
        //! @return Either a valid cooked mesh or none if the cooking failed.
        //! 
        AZStd::optional<Physics::CookedMeshShapeConfiguration> CreatePxCookedMeshConfiguration(const AZStd::vector<AZ::Vector3>& pointList, const AZ::Vector3& scale);

        //! Returns whether a shape configuration describes a primitive shape such as a box or sphere, as opposed to mesh geometry.
        bool IsPrimitiveShape(const Physics::ShapeConfiguration& shapeConfig);

        //! Minimum and maximum values for the level of subdivision used when approximating capsules and spheres with convex meshes.
        //! The maximum value is chosen so that the number of faces and vertices generated by CreateConvexFromPrimitive will be within
        //! the limit imposed by PhysX (255).
        //! @{
        constexpr AZ::u8 MinCapsuleSubdivisionLevel = 1;
        constexpr AZ::u8 MaxCapsuleSubdivisionLevel = 5;
        //! @}

        AZStd::optional<Physics::CookedMeshShapeConfiguration> CreateConvexFromPrimitive(
            const Physics::ColliderConfiguration& colliderConfig,
            const Physics::ShapeConfiguration& primitiveShapeConfig, AZ::u8 subdivisionLevel, const AZ::Vector3& scale);

        // 255 is the hard limit for PhysX number of vertices/faces. Upper bound is set to something sensible and less than this hard limit.
        constexpr AZ::u8 MinFrustumSubdivisions = 3;
        constexpr AZ::u8 MaxFrustumSubdivisions = 125; 

        //! Creates the points for a given frustum along the z axis as specified by the supplied arguements.
        //!
        //! @param height Height of the frustum. Must be greater than 0.
        //! @param bottomRadius Radius of bottom cace of frustum. Must be greater than 0 if topRadius is 0, otherwise can be 0.
        //! @param topRadius Radius of top face of frustum. Must be greater than 0 if bottompRadius is 0, otherwise can be 0.
        //! @param subdivisionsNumber of angular subdivisions. Must be between 3 and 125 inclusive.
        //! @return Either a valid point list or none if any of the arguements are invalid.
        //!
        AZStd::optional<AZStd::vector<AZ::Vector3>> CreatePointsAtFrustumExtents(float height, float bottomRadius, float topRadius, AZ::u8 subdivisions);
    
        AZStd::string ConvexCookingResultToString(physx::PxConvexMeshCookingResult::Enum convexCookingResultCode);
        AZStd::string TriMeshCookingResultToString(physx::PxTriangleMeshCookingResult::Enum triangleCookingResultCode);

        bool WriteCookedMeshToFile(const AZStd::string& filePath, const Pipeline::MeshAssetData& assetData);
        bool WriteCookedMeshToFile(const AZStd::string& filePath, const AZStd::vector<AZ::u8>& physxData, 
            Physics::CookedMeshShapeConfiguration::MeshType meshType);

        bool CookConvexToPxOutputStream(const AZ::Vector3* vertices, AZ::u32 vertexCount, physx::PxOutputStream& stream);

        bool CookTriangleMeshToToPxOutputStream(const AZ::Vector3* vertices, AZ::u32 vertexCount,
            const AZ::u32* indices, AZ::u32 indexCount, physx::PxOutputStream& stream);

        bool MeshDataToPxGeometry(physx::PxBase* meshData, physx::PxGeometryHolder &pxGeometry, const AZ::Vector3& scale);

        //! Returns all connected busIds of the specified type.
        template<typename BusT>
        AZStd::vector<typename BusT::BusIdType> FindConnectedBusIds()
        {
            AZStd::vector<typename BusT::BusIdType> busIds;
            BusT::EnumerateHandlers([&busIds](typename BusT::Events* /*handler*/)
            {
                busIds.emplace_back(*BusT::GetCurrentBusId());
                return true;
            });
            return busIds;
        }

        //! Logs a warning message using the names of the entities provided.
        void WarnEntityNames(const AZStd::vector<AZ::EntityId>& entityIds, const char* category, const char* message);

        //! Logs a warning if there is more than one connected bus of the particular type.
        template<typename BusT>
        void LogWarningIfMultipleComponents(const char* messageCategroy, const char* messageFormat)
        {
            const auto entityIds = FindConnectedBusIds<BusT>();
            if (entityIds.size() > 1)
            {
                WarnEntityNames(entityIds, messageCategroy, messageFormat);
            }
        }

        //! Converts collider position and orientation offsets to a transform.
        AZ::Transform GetColliderLocalTransform(const AZ::Vector3& colliderRelativePosition
            , const AZ::Quaternion& colliderRelativeRotation);

        //! Combines collider position and orientation offsets and world transform to a transform.
        AZ::Transform GetColliderWorldTransform(const AZ::Transform& worldTransform
            , const AZ::Vector3& colliderRelativePosition
            , const AZ::Quaternion& colliderRelativeRotation);

        //! Converts points in a collider's local space to world space positions 
        //! accounting for collider position and orientation offsets.
        void ColliderPointsLocalToWorld(AZStd::vector<AZ::Vector3>& pointsInOut
            , const AZ::Transform& worldTransform
            , const AZ::Vector3& colliderRelativePosition
            , const AZ::Quaternion& colliderRelativeRotation
            , const AZ::Vector3& nonUniformScale);

        //! Returns AABB of collider by constructing PxGeometry from collider and shape configuration,
        //! and invoking physx::PxGeometryQuery::getWorldBounds.
        //! This function is used only by editor components.
        AZ::Aabb GetColliderAabb(const AZ::Transform& worldTransform
            , bool hasNonUniformScale
            , AZ::u8 subdivisionLevel
            , const ::Physics::ShapeConfiguration& shapeConfiguration
            , const ::Physics::ColliderConfiguration& colliderConfiguration);

        bool TriggerColliderExists(AZ::EntityId entityId);

        void GetShapesFromAsset(const Physics::PhysicsAssetShapeConfiguration& assetConfiguration,
            const Physics::ColliderConfiguration& originalColliderConfiguration, bool hasNonUniformScale,
            AZ::u8 subdivisionLevel, AZStd::vector<AZStd::shared_ptr<Physics::Shape>>& resultingShapes);

        void GetColliderShapeConfigsFromAsset(const Physics::PhysicsAssetShapeConfiguration& assetConfiguration,
            const Physics::ColliderConfiguration& originalColliderConfiguration,
            bool hasNonUniformScale, AZ::u8 subdivisionLevel, AzPhysics::ShapeColliderPairList& resultingColliderShapes);

        //! Gets the scale from the entity's Transform component.
        AZ::Vector3 GetTransformScale(AZ::EntityId entityId);
        //! Returns a vector scale with each element equal to the max element from the entity's Transform component.
        AZ::Vector3 GetUniformScale(AZ::EntityId entityId);
        //! Gets the scale from the entity's Non-Uniform Scale component, if it is present.
        //! Otherwise (1, 1, 1) is returned.
        AZ::Vector3 GetNonUniformScale(AZ::EntityId entityId);
        //! Gets the overall scale, taking into account the scale from both the entity's Transform component and the
        //! Non-Uniform Scale component, if it is present.
        AZ::Vector3 GetOverallScale(AZ::EntityId entityId);

        //! Returns defaultValue if the input is infinite or NaN, otherwise returns the input unchanged.
        const AZ::Vector3& Sanitize(const AZ::Vector3& input, const AZ::Vector3& defaultValue = AZ::Vector3::CreateZero());

        void InitHeightfieldShapeConfiguration(AZ::EntityId entityId, Physics::HeightfieldShapeConfiguration& configuration);

        namespace Geometry
        {
            using PointList = AZStd::vector<AZ::Vector3>;

            //! Generates a list of points on a box.
            PointList GenerateBoxPoints(const AZ::Vector3& min, const AZ::Vector3& max);

            //! Generates a list of points on the surface of a sphere.
            PointList GenerateSpherePoints(float radius);

            //! Generates a list of points on the surface of a cylinder.
            PointList GenerateCylinderPoints(float height, float radius);

            //! Generates vertices and indices representing the provided box geometry 
            void GetBoxGeometry(const physx::PxBoxGeometry& geometry, AZStd::vector<AZ::Vector3>& vertices, AZStd::vector<AZ::u32>& indices);

            //! Generates vertices and indices representing the provided capsule geometry 
            void GetCapsuleGeometry(const physx::PxCapsuleGeometry& geometry, AZStd::vector<AZ::Vector3>& vertices, AZStd::vector<AZ::u32>& indices, const AZ::u32 stacks, const AZ::u32 slices);

            //! Generates vertices and indices representing the provided convex mesh geometry 
            void GetConvexMeshGeometry(const physx::PxConvexMeshGeometry& geometry, AZStd::vector<AZ::Vector3>& vertices, AZStd::vector<AZ::u32>& indices);

            //! Generates vertices and indices representing the provided heightfield geometry, optionally limited to a bounding box
            void GetHeightFieldGeometry(const physx::PxHeightFieldGeometry& geometry, AZStd::vector<AZ::Vector3>& vertices, AZStd::vector<AZ::u32>& indices, AZ::Aabb* optionalBounds);

            //! Generates vertices and indices representing the provided sphere geometry and optional stacks and slices
            void GetSphereGeometry(const physx::PxSphereGeometry& geometry, AZStd::vector<AZ::Vector3>& vertices, AZStd::vector<AZ::u32>& indices, const AZ::u32 stacks, const AZ::u32 slices);

            //! Generates vertices and indices representing the provided triangle mesh geometry 
            void GetTriangleMeshGeometry(const physx::PxTriangleMeshGeometry& geometry, AZStd::vector<AZ::Vector3>& vertices, AZStd::vector<AZ::u32>& indices);
        } // namespace Geometry

        //! Returns the World transform of an entity with scale. 
        //! This can be used if ComputeJointLocalTransform will be invoked with the result as an argument since ComputeJointLocalTransform  will remove scale.
        AZ::Transform GetEntityWorldTransformWithScale(AZ::EntityId entityId);

        //! Returns the World transform of an entity without scale.
        AZ::Transform GetEntityWorldTransformWithoutScale(AZ::EntityId entityId);

        //! Computes the local transform of joint from an entity given the joint's world transform and the entity's world transform.
        AZ::Transform ComputeJointLocalTransform(const AZ::Transform& jointWorldTransform,
            const AZ::Transform& entityWorldTransform);

        //! Computes the world transform of joint given the joint's local transform from an entity and the entity's world transform.
        AZ::Transform ComputeJointWorldTransform(const AZ::Transform& jointLocalTransform,
            const AZ::Transform& entityWorldTransform);
    } // namespace Utils

    namespace ReflectionUtils
    {
        //! Reflect API specific to PhysX physics. Generic physics API should be reflected in Physics::ReflectionUtils::ReflectPhysicsApi.
        void ReflectPhysXOnlyApi(AZ::ReflectContext* context);
    } // namespace ReflectionUtils

    namespace PxActorFactories
    {
        AZStd::shared_ptr<physx::PxRigidDynamic> CreatePxRigidBody(const AzPhysics::RigidBodyConfiguration& configuration);
        AZStd::shared_ptr<physx::PxRigidStatic> CreatePxStaticRigidBody(const AzPhysics::StaticRigidBodyConfiguration& configuration);
    } // namespace PxActorFactories

    namespace StaticRigidBodyUtils
    {
        bool CanCreateRuntimeComponent(const AZ::Entity& editorEntity);
        bool TryCreateRuntimeComponent(const AZ::Entity& editorEntity, AZ::Entity& gameEntity);
    } // namespace StaticRigidBodyComponent
} // namespace PhysX
