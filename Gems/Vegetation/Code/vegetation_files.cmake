#
# Copyright (c) Contributors to the Open 3D Engine Project
# 
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

set(FILES
    Include/Vegetation/DescriptorListAsset.h
    Include/Vegetation/Descriptor.h
    Include/Vegetation/InstanceData.h
    Include/Vegetation/InstanceSpawner.h
    Include/Vegetation/DynamicSliceInstanceSpawner.h
    Include/Vegetation/EmptyInstanceSpawner.h
    Include/Vegetation/PrefabInstanceSpawner.h
    Include/Vegetation/AreaComponentBase.h
    Include/Vegetation/Ebuses/AreaSystemRequestBus.h
    Include/Vegetation/Ebuses/AreaNotificationBus.h
    Include/Vegetation/Ebuses/AreaConfigRequestBus.h
    Include/Vegetation/Ebuses/AreaDebugBus.h
    Include/Vegetation/Ebuses/AreaInfoBus.h
    Include/Vegetation/Ebuses/AreaRequestBus.h
    Include/Vegetation/Ebuses/DebugNotificationBus.h
    Include/Vegetation/Ebuses/DebugRequestsBus.h
    Include/Vegetation/Ebuses/DebugSystemDataBus.h
    Include/Vegetation/Ebuses/DependencyRequestBus.h
    Include/Vegetation/Ebuses/DescriptorNotificationBus.h
    Include/Vegetation/Ebuses/DescriptorProviderRequestBus.h
    Include/Vegetation/Ebuses/DescriptorSelectorRequestBus.h
    Include/Vegetation/Ebuses/FilterRequestBus.h
    Include/Vegetation/Ebuses/InstanceSystemRequestBus.h
    Include/Vegetation/Ebuses/ModifierRequestBus.h
    Include/Vegetation/Ebuses/SystemConfigurationBus.h
    Include/Vegetation/Ebuses/ScaleModifierRequestBus.h
    Include/Vegetation/Ebuses/SlopeAlignmentModifierRequestBus.h
    Include/Vegetation/Ebuses/RotationModifierRequestBus.h
    Include/Vegetation/Ebuses/PositionModifierRequestBus.h
    Include/Vegetation/Ebuses/SurfaceAltitudeFilterRequestBus.h
    Include/Vegetation/Ebuses/DistanceBetweenFilterRequestBus.h
    Include/Vegetation/Ebuses/DistributionFilterRequestBus.h
    Include/Vegetation/Ebuses/ShapeIntersectionFilterRequestBus.h
    Include/Vegetation/Ebuses/SurfaceSlopeFilterRequestBus.h
    Include/Vegetation/Ebuses/SurfaceMaskDepthFilterRequestBus.h
    Include/Vegetation/Ebuses/SurfaceMaskFilterRequestBus.h
    Include/Vegetation/Ebuses/AreaBlenderRequestBus.h
    Include/Vegetation/Ebuses/BlockerRequestBus.h
    Include/Vegetation/Ebuses/DescriptorListCombinerRequestBus.h
    Include/Vegetation/Ebuses/ReferenceShapeRequestBus.h
    Include/Vegetation/Ebuses/MeshBlockerRequestBus.h
    Include/Vegetation/Ebuses/SpawnerRequestBus.h
    Include/Vegetation/Ebuses/DescriptorListRequestBus.h
    Source/Components/AreaBlenderComponent.cpp
    Source/Components/AreaBlenderComponent.h
    Source/Components/AreaComponentBase.cpp
    Source/Components/BlockerComponent.cpp
    Source/Components/BlockerComponent.h
    Source/Components/DescriptorListCombinerComponent.cpp
    Source/Components/DescriptorListCombinerComponent.h
    Source/Components/DescriptorListComponent.cpp
    Source/Components/DescriptorListComponent.h
    Source/Components/DescriptorWeightSelectorComponent.cpp
    Source/Components/DescriptorWeightSelectorComponent.h
    Source/Components/DistanceBetweenFilterComponent.cpp
    Source/Components/DistanceBetweenFilterComponent.h
    Source/Components/DistributionFilterComponent.cpp
    Source/Components/DistributionFilterComponent.h
    Source/Components/LevelSettingsComponent.cpp
    Source/Components/LevelSettingsComponent.h
    Source/Components/MeshBlockerComponent.cpp
    Source/Components/MeshBlockerComponent.h
    Source/Components/PositionModifierComponent.cpp
    Source/Components/PositionModifierComponent.h
    Source/Components/ReferenceShapeComponent.cpp
    Source/Components/ReferenceShapeComponent.h
    Source/Components/RotationModifierComponent.cpp
    Source/Components/RotationModifierComponent.h
    Source/Components/ScaleModifierComponent.cpp
    Source/Components/ScaleModifierComponent.h
    Source/Components/ShapeIntersectionFilterComponent.cpp
    Source/Components/ShapeIntersectionFilterComponent.h
    Source/Components/SlopeAlignmentModifierComponent.cpp
    Source/Components/SlopeAlignmentModifierComponent.h
    Source/Components/SpawnerComponent.cpp
    Source/Components/SpawnerComponent.h
    Source/Components/SurfaceAltitudeFilterComponent.cpp
    Source/Components/SurfaceAltitudeFilterComponent.h
    Source/Components/SurfaceMaskDepthFilterComponent.cpp
    Source/Components/SurfaceMaskDepthFilterComponent.h
    Source/Components/SurfaceMaskFilterComponent.cpp
    Source/Components/SurfaceMaskFilterComponent.h
    Source/Components/SurfaceSlopeFilterComponent.cpp
    Source/Components/SurfaceSlopeFilterComponent.h
    Source/Util/ConcurrentQueue.h
    Source/Util/ProducerConsumerQueue.h
    Source/Debugger/AreaDebugComponent.cpp
    Source/Debugger/AreaDebugComponent.h
    Source/Debugger/DebugComponent.cpp
    Source/Debugger/DebugComponent.h
    Source/DescriptorListAsset.cpp
    Source/Descriptor.cpp
    Source/DynamicSliceInstanceSpawner.cpp
    Source/EmptyInstanceSpawner.cpp
    Source/PrefabInstanceSpawner.cpp
    Source/VegetationSystemComponent.cpp
    Source/VegetationSystemComponent.h
    Source/InstanceData.cpp
    Source/InstanceSystemComponent.cpp
    Source/InstanceSystemComponent.h
    Source/DebugSystemComponent.cpp
    Source/DebugSystemComponent.h
)
