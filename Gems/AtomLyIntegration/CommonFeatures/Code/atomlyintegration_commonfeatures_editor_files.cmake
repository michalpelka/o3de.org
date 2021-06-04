#
# All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
# its licensors.
#
# For complete copyright and license terms please see the LICENSE at the root of this
# distribution (the "License"). All use of this software is governed by the License,
# or, if provided, by the license below or the license accompanying this file. Do not
# remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#

set(FILES
    Include/AtomLyIntegration/CommonFeatures/Material/EditorMaterialSystemComponentRequestBus.h
    Include/AtomLyIntegration/CommonFeatures/ReflectionProbe/EditorReflectionProbeBus.h
    Include/AtomLyIntegration/CommonFeatures/Thumbnails/ThumbnailFeatureProcessorProviderBus.h
    Source/Module.cpp
    Source/Animation/EditorAttachmentComponent.h
    Source/Animation/EditorAttachmentComponent.cpp
    Source/EditorCommonFeaturesSystemComponent.h
    Source/EditorCommonFeaturesSystemComponent.cpp
    Source/CoreLights/EditorAreaLightComponent.h
    Source/CoreLights/EditorAreaLightComponent.cpp
    Source/CoreLights/EditorDirectionalLightComponent.h
    Source/CoreLights/EditorDirectionalLightComponent.cpp
    Source/Decals/EditorDecalComponent.h
    Source/Decals/EditorDecalComponent.cpp
    Source/DiffuseGlobalIllumination/EditorDiffuseProbeGridComponent.h
    Source/DiffuseGlobalIllumination/EditorDiffuseProbeGridComponent.cpp
    Source/DiffuseGlobalIllumination/EditorDiffuseGlobalIlluminationComponent.h
    Source/DiffuseGlobalIllumination/EditorDiffuseGlobalIlluminationComponent.cpp
    Source/Grid/EditorGridComponent.h
    Source/Grid/EditorGridComponent.cpp
    Source/ImageBasedLights/EditorImageBasedLightComponent.h
    Source/ImageBasedLights/EditorImageBasedLightComponent.cpp
    Source/Material/EditorMaterialComponent.cpp
    Source/Material/EditorMaterialComponent.h
    Source/Material/EditorMaterialComponentUtil.cpp
    Source/Material/EditorMaterialComponentUtil.h
    Source/Material/EditorMaterialComponentSlot.cpp
    Source/Material/EditorMaterialComponentSlot.h
    Source/Material/EditorMaterialComponentExporter.cpp
    Source/Material/EditorMaterialComponentExporter.h
    Source/Material/EditorMaterialComponentInspector.cpp
    Source/Material/EditorMaterialComponentInspector.h
    Source/Material/EditorMaterialModelUvNameMapInspector.cpp
    Source/Material/EditorMaterialModelUvNameMapInspector.h
    Source/Material/EditorMaterialSystemComponent.cpp
    Source/Material/EditorMaterialSystemComponent.h
    Source/Material/MaterialBrowserInteractions.h
    Source/Material/MaterialBrowserInteractions.cpp
    Source/Material/MaterialThumbnail.cpp
    Source/Material/MaterialThumbnail.h
    Source/Mesh/EditorMeshComponent.h
    Source/Mesh/EditorMeshComponent.cpp
    Source/Mesh/EditorMeshSystemComponent.cpp
    Source/Mesh/EditorMeshSystemComponent.h
    Source/Mesh/MeshThumbnail.h
    Source/Mesh/MeshThumbnail.cpp
    Source/PostProcess/EditorPostFxLayerComponent.cpp
    Source/PostProcess/EditorPostFxLayerComponent.h
    Source/PostProcess/Bloom/EditorBloomComponent.cpp
    Source/PostProcess/Bloom/EditorBloomComponent.h
    Source/PostProcess/DepthOfField/EditorDepthOfFieldComponent.cpp
    Source/PostProcess/DepthOfField/EditorDepthOfFieldComponent.h
    Source/PostProcess/DisplayMapper/EditorDisplayMapperComponent.cpp
    Source/PostProcess/DisplayMapper/EditorDisplayMapperComponent.h
    Source/PostProcess/ExposureControl/EditorExposureControlComponent.cpp
    Source/PostProcess/ExposureControl/EditorExposureControlComponent.h
    Source/PostProcess/Ssao/EditorSsaoComponent.cpp
    Source/PostProcess/Ssao/EditorSsaoComponent.h
    Source/PostProcess/LookModification/EditorLookModificationComponent.cpp
    Source/PostProcess/LookModification/EditorLookModificationComponent.h
    Source/PostProcess/RadiusWeightModifier/EditorRadiusWeightModifierComponent.cpp
    Source/PostProcess/RadiusWeightModifier/EditorRadiusWeightModifierComponent.h
    Source/PostProcess/ShapeWeightModifier/EditorShapeWeightModifierComponent.cpp
    Source/PostProcess/GradientWeightModifier/EditorGradientWeightModifierComponent.h
    Source/PostProcess/GradientWeightModifier/EditorGradientWeightModifierComponent.cpp
    Source/PostProcess/ShapeWeightModifier/EditorShapeWeightModifierComponent.h
    Source/PostProcess/EditorPostFxLayerCategoriesAsset.h
    Source/PostProcess/EditorPostFxLayerCategoriesAsset.cpp
    Source/PostProcess/EditorPostFxSystemComponent.h
    Source/PostProcess/EditorPostFxSystemComponent.cpp
    Source/ScreenSpace/EditorDeferredFogComponent.h
    Source/ScreenSpace/EditorDeferredFogComponent.cpp
    Source/ReflectionProbe/EditorReflectionProbeComponent.h
    Source/ReflectionProbe/EditorReflectionProbeComponent.cpp
    Source/SkinnedMesh/SkinnedMeshDebugDisplay.h
    Source/SkinnedMesh/SkinnedMeshDebugDisplay.cpp
    Source/SkyBox/EditorHDRiSkyboxComponent.cpp
    Source/SkyBox/EditorHDRiSkyboxComponent.h
    Source/SkyBox/EditorPhysicalSkyComponent.cpp
    Source/SkyBox/EditorPhysicalSkyComponent.h
    Source/Thumbnails/ThumbnailUtils.h
    Source/Thumbnails/ThumbnailUtils.cpp
    Source/Thumbnails/Preview/CommonPreviewer.cpp
    Source/Thumbnails/Preview/CommonPreviewer.h
    Source/Thumbnails/Preview/CommonPreviewer.ui
    Source/Thumbnails/Preview/CommonPreviewerFactory.cpp
    Source/Thumbnails/Preview/CommonPreviewerFactory.h
    Source/Thumbnails/Rendering/CommonThumbnailRenderer.cpp
    Source/Thumbnails/Rendering/CommonThumbnailRenderer.h
    Source/Thumbnails/Rendering/ThumbnailRendererData.h
    Source/Thumbnails/Rendering/ThumbnailRendererContext.h
    Source/Thumbnails/Rendering/ThumbnailRendererSteps/ThumbnailRendererStep.h
    Source/Thumbnails/Rendering/ThumbnailRendererSteps/InitializeStep.cpp
    Source/Thumbnails/Rendering/ThumbnailRendererSteps/InitializeStep.h
    Source/Thumbnails/Rendering/ThumbnailRendererSteps/FindThumbnailToRenderStep.cpp
    Source/Thumbnails/Rendering/ThumbnailRendererSteps/FindThumbnailToRenderStep.h
    Source/Thumbnails/Rendering/ThumbnailRendererSteps/WaitForAssetsToLoadStep.cpp
    Source/Thumbnails/Rendering/ThumbnailRendererSteps/WaitForAssetsToLoadStep.h
    Source/Thumbnails/Rendering/ThumbnailRendererSteps/CaptureStep.cpp
    Source/Thumbnails/Rendering/ThumbnailRendererSteps/CaptureStep.h
    Source/Thumbnails/Rendering/ThumbnailRendererSteps/ReleaseResourcesStep.cpp
    Source/Thumbnails/Rendering/ThumbnailRendererSteps/ReleaseResourcesStep.h
    Source/Scripting/EditorEntityReferenceComponent.cpp
    Source/Scripting/EditorEntityReferenceComponent.h
    Source/SurfaceData/EditorSurfaceDataMeshComponent.cpp
    Source/SurfaceData/EditorSurfaceDataMeshComponent.h
    Resources/AtomLyIntegrationResources.qrc
)
