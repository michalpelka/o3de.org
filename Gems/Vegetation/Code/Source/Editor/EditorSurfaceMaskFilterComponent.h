/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <Components/SurfaceMaskFilterComponent.h>
#include <Vegetation/Editor/EditorVegetationComponentBase.h>

namespace Vegetation
{
    class EditorSurfaceMaskFilterComponent
        : public EditorVegetationComponentBase<SurfaceMaskFilterComponent, SurfaceMaskFilterConfig>
    {
    public:
        using BaseClassType = EditorVegetationComponentBase<SurfaceMaskFilterComponent, SurfaceMaskFilterConfig>;
        AZ_EDITOR_COMPONENT(EditorSurfaceMaskFilterComponent, EditorSurfaceMaskFilterComponentTypeId, BaseClassType);
        static void Reflect(AZ::ReflectContext* context);

        static constexpr const char* const s_categoryName = "Vegetation Filters";
        static constexpr const char* const s_componentName = "Vegetation Surface Mask Filter";
        static constexpr const char* const s_componentDescription = "Filters out vegetation based on surface mask-to-tag mappings";
        static constexpr const char* const s_icon = "Editor/Icons/Components/VegetationFilter.svg";
        static constexpr const char* const s_viewportIcon = "Editor/Icons/Components/Viewport/VegetationFilter.png";
        static constexpr const char* const s_helpUrl = "https://docs.aws.amazon.com/console/lumberyard/vegetationfilters/vegetation-surface-mask-filter";
    };
}
