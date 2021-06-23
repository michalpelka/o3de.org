/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include "UiCanvasEditor_precompiled.h"

#include "ViewportDragInteraction.h"

ViewportDragInteraction::ViewportDragInteraction(const AZ::Vector2& startMousePos)
    : m_startMousePos(startMousePos)
{
}

ViewportDragInteraction::~ViewportDragInteraction()
{
}

void ViewportDragInteraction::Render([[maybe_unused]] Draw2dHelper& draw2d)
{
}

void ViewportDragInteraction::EndInteraction(EndState /*endState*/)
{
}

