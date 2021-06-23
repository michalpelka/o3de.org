/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include <qpixmap.h>

#include <GraphCanvas/Widgets/NodePalette/TreeItems/DraggableNodePaletteTreeItem.h>

namespace GraphCanvas
{
    /////////////////////////////////
    // DraggableNodePaletteTreeItem
    /////////////////////////////////
    DraggableNodePaletteTreeItem::DraggableNodePaletteTreeItem(AZStd::string_view name, EditorId editorId)
        : IconDecoratedNodePaletteTreeItem(name, editorId)
    {
    }

    Qt::ItemFlags DraggableNodePaletteTreeItem::OnFlags() const
    {
        if (IsEnabled() && !HasError())
        {
            return Qt::ItemIsDragEnabled;
        }

        return Qt::ItemFlags();
    }
}
