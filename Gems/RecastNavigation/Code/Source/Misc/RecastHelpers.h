/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once
#include <DetourAlloc.h>
#include <Recast.h>
#include <AzCore/Math/Aabb.h>
#include <AzCore/Math/Vector3.h>
#include <AzCore/std/smart_ptr/shared_ptr.h>
#include <AzCore/std/function/function_template.h>

namespace RecastNavigation
{
    //! A helper class to manage different coordinate systems between O3DE and Recast Navigation library.
    //! In O3DE, +Z is up. In Recast library, +Y is up.
    class RecastVector3
    {
    public:
        RecastVector3() = default;

        //! A constructor from O3DE coordinate values.
        explicit RecastVector3(const AZ::Vector3& in)
        {
            m_xyz[0] = in.GetX();
            m_xyz[1] = in.GetZ(); // swapping y and z
            m_xyz[2] = in.GetY();
        }

        //! A constructor from Recast coordinate values.
        explicit RecastVector3(const float* data)
        {
            m_xyz[0] = data[0];
            m_xyz[1] = data[1];
            m_xyz[2] = data[2];
        }

        //! @returns raw data without any conversion between coordinate systems. Useful when working with Recast library API.
        float* GetData() { return &m_xyz[0]; }

        //! @returns vector in O3DE coordinate space, with +Z being up. Useful when passing data from Recast to O3DE.
        [[nodiscard]] AZ::Vector3 AsVector3WithZup() const
        {
            return { m_xyz[0], m_xyz[2] , m_xyz[1] };
        }

        float m_xyz[3] = { 0, 0, 0 };
    };

    //! A collection of triangle data within a volume defined by an axis aligned bounding box.
    class TileGeometry
    {
    public:
        AZ::Aabb m_worldBounds = AZ::Aabb::CreateNull();
        AZ::Aabb m_scanBounds = AZ::Aabb::CreateNull(); // includes @m_worldBounds and additional border extents

        int m_tileX = 0; // tile coordinate within the navigation grid along X-axis
        int m_tileY = 0; // tile coordinate within the navigation grid along Y-axis

        //! Indexed vertices.
        AZStd::vector<RecastVector3> m_vertices;
        AZStd::vector<AZ::s32> m_indices;

        //! Callback to the navigation mesh component that should process this tile.
        AZStd::function<void(AZStd::shared_ptr<TileGeometry>)> m_tileCallback;

        //! @returns true if there are no vertices in this tile
        bool IsEmpty() const
        {
            return m_vertices.empty();
        }
    };

    //! Navigation data in binary Recast form
    struct NavigationTileData
    {
        //! @returns true if the Recast data is not empty
        bool IsValid() const
        {
            return m_size > 0 && m_data != nullptr;
        }

        unsigned char* m_data = nullptr;
        int m_size = 0;
    };
} // namespace RecastNavigation
