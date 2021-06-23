/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

// Landscape Canvas
#include <Editor/Nodes/Shapes/BaseShapeNode.h>

namespace LandscapeCanvas
{
    class DiskShapeNode : public BaseShapeNode
    {
    public:
        AZ_CLASS_ALLOCATOR(DiskShapeNode, AZ::SystemAllocator, 0);
        AZ_RTTI(DiskShapeNode, "{DF616307-1D8D-47E6-B012-3BCDEDF1CD97}", BaseShapeNode);

        static void Reflect(AZ::ReflectContext* context);

        DiskShapeNode() = default;
        explicit DiskShapeNode(GraphModel::GraphPtr graph);

        static const QString TITLE;
        const char* GetTitle() const override { return TITLE.toUtf8().constData(); }
    };
}
