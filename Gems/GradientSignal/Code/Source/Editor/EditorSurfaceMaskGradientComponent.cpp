/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include "GradientSignal_precompiled.h"
#include "EditorSurfaceMaskGradientComponent.h"

namespace GradientSignal
{
    void EditorSurfaceMaskGradientComponent::Reflect(AZ::ReflectContext* context)
    {
        EditorGradientComponentBase::ReflectSubClass<EditorSurfaceMaskGradientComponent, BaseClassType>(context);
    }
}
