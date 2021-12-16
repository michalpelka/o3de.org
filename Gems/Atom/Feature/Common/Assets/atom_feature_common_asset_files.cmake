# 
# Copyright (c) Contributors to the Open 3D Engine Project. 
# For complete copyright and license terms please see the LICENSE at the root of this distribution. 
# 
# SPDX-License-Identifier: Apache-2.0 OR MIT 
# 

set(FILES
    Materials/ReflectionProbe/ReflectionProbeVisualization.materialtype
    Materials/Special/ShadowCatcher.azsl
    Materials/Special/ShadowCatcher.materialtype
    Materials/Special/ShadowCatcher.shader
    Materials/Types/EnhancedPBR.materialtype
    Materials/Types/EnhancedPBR_Common.azsli
    Materials/Types/EnhancedPBR_DepthPass_WithPS.azsl
    Materials/Types/EnhancedPBR_DepthPass_WithPS.shader
    Materials/Types/EnhancedPBR_ForwardPass.azsl
    Materials/Types/EnhancedPBR_ForwardPass.shader
    Materials/Types/EnhancedPBR_ForwardPass_EDS.shader
    Materials/Types/EnhancedPBR_Shadowmap_WithPS.azsl
    Materials/Types/EnhancedPBR_Shadowmap_WithPS.shader
    Materials/Types/EnhancedPBR_SubsurfaceState.lua
    Materials/Types/Skin.azsl
    Materials/Types/Skin.materialtype
    Materials/Types/Skin.shader
    Materials/Types/Skin_Common.azsli
    Materials/Types/Skin_WrinkleMaps.lua
    Materials/Types/StandardMultilayerPBR.materialtype
    Materials/Types/StandardMultilayerPBR_ClearCoatEnableFeature.lua
    Materials/Types/StandardMultilayerPBR_Common.azsli
    Materials/Types/StandardMultilayerPBR_DepthPass_WithPS.azsl
    Materials/Types/StandardMultilayerPBR_DepthPass_WithPS.shader
    Materials/Types/StandardMultilayerPBR_Displacement.lua
    Materials/Types/StandardMultilayerPBR_ForwardPass.azsl
    Materials/Types/StandardMultilayerPBR_ForwardPass.shader
    Materials/Types/StandardMultilayerPBR_ForwardPass_EDS.shader
    Materials/Types/StandardMultilayerPBR_LayerEnable.lua
    Materials/Types/StandardMultilayerPBR_ShaderEnable.lua
    Materials/Types/StandardMultilayerPBR_Shadowmap_WithPS.azsl
    Materials/Types/StandardMultilayerPBR_Shadowmap_WithPS.shader
    Materials/Types/StandardPBR.materialtype
    Materials/Types/StandardPBR_ClearCoatEnableFeature.lua
    Materials/Types/StandardPBR_ClearCoatState.lua
    Materials/Types/StandardPBR_Common.azsli
    Materials/Types/StandardPBR_DepthPass_WithPS.azsl
    Materials/Types/StandardPBR_DepthPass_WithPS.shader
    Materials/Types/StandardPBR_EmissiveState.lua
    Materials/Types/StandardPBR_ForwardPass.azsl
    Materials/Types/StandardPBR_ForwardPass.shader
    Materials/Types/StandardPBR_ForwardPass_EDS.shader
    Materials/Types/StandardPBR_HandleOpacityDoubleSided.lua
    Materials/Types/StandardPBR_HandleOpacityMode.lua
    Materials/Types/StandardPBR_LowEndForward.azsl
    Materials/Types/StandardPBR_LowEndForward.shader
    Materials/Types/StandardPBR_LowEndForward_EDS.shader
    Materials/Types/StandardPBR_Metallic.lua
    Materials/Types/StandardPBR_ParallaxState.lua
    Materials/Types/StandardPBR_Roughness.lua
    Materials/Types/StandardPBR_ShaderEnable.lua
    Materials/Types/StandardPBR_Shadowmap_WithPS.azsl
    Materials/Types/StandardPBR_Shadowmap_WithPS.shader
    Materials/Types/MaterialInputs/AlphaInput.azsli
    Materials/Types/MaterialInputs/BaseColorInput.azsli
    Materials/Types/MaterialInputs/ClearCoatInput.azsli
    Materials/Types/MaterialInputs/DetailMapsCommonFunctor.lua
    Materials/Types/MaterialInputs/DetailMapsInput.azsli
    Materials/Types/MaterialInputs/EmissiveInput.azsli
    Materials/Types/MaterialInputs/MetallicInput.azsli
    Materials/Types/MaterialInputs/NormalInput.azsli
    Materials/Types/MaterialInputs/OcclusionInput.azsli
    Materials/Types/MaterialInputs/ParallaxInput.azsli
    Materials/Types/MaterialInputs/RoughnessInput.azsli
    Materials/Types/MaterialInputs/SpecularInput.azsli
    Materials/Types/MaterialInputs/SubsurfaceInput.azsli
    Materials/Types/MaterialInputs/TransmissionInput.azsli
    Materials/Types/MaterialInputs/UvSetCount.azsli
    Passes/AuxGeom.pass
    Passes/BlendColorGradingLuts.pass
    Passes/Bloom.pass
    Passes/BloomBlur.pass
    Passes/BloomComposite.pass
    Passes/BloomDownsample.pass
    Passes/BRDFTexture.pass
    Passes/BRDFTexturePipeline.pass
    Passes/CameraMotionVector.pass
    Passes/CascadedShadowmaps.pass
    Passes/CheckerboardResolveColor.pass
    Passes/CheckerboardResolveDepth.pass
    Passes/Clear.pass
    Passes/ContrastAdaptiveSharpening.pass
    Passes/ConvertToAcescg.pass
    Passes/DebugOverlayParent.pass
    Passes/DeferredFog.pass
    Passes/Depth.pass
    Passes/DepthCheckerboard.pass
    Passes/DepthDownsample.pass
    Passes/DepthExponentiation.pass
    Passes/DepthMax.pass
    Passes/DepthMSAA.pass
    Passes/DepthMSAA2x.pass
    Passes/DepthMSAA4x.pass
    Passes/DepthMSAA8x.pass
    Passes/DepthMSAAParent.pass
    Passes/DepthOfField.pass
    Passes/DepthOfFieldBlurBokeh.pass
    Passes/DepthOfFieldComposite.pass
    Passes/DepthOfFieldDownSample.pass
    Passes/DepthOfFieldMask.pass
    Passes/DepthOfFieldOnBokeh.pass
    Passes/DepthOfFieldPrepare.pass
    Passes/DepthOfFieldReadBackFocusDepth.pass
    Passes/DepthOfFieldWriteFocusDepthFromGpu.pass
    Passes/DepthToLinearDepth.pass
    Passes/DepthUpsample.pass
    Passes/DiffuseComposite.pass
    Passes/DiffuseGlobalFullscreen.pass
    Passes/DiffuseGlobalIllumination.pass
    Passes/DiffuseProbeGridBlendDistance.pass
    Passes/DiffuseProbeGridBlendIrradiance.pass
    Passes/DiffuseProbeGridBorderUpdate.pass
    Passes/DiffuseProbeGridClassification.pass
    Passes/DiffuseProbeGridDownsample.pass
    Passes/DiffuseProbeGridRayTracing.pass
    Passes/DiffuseProbeGridRelocation.pass
    Passes/DiffuseProbeGridRender.pass
    Passes/DiffuseProbeGridUpdate.pass
    Passes/DiffuseSpecularMerge.pass
    Passes/DisplayMapper.pass
    Passes/DownsampleLuminanceMinAvgMaxCS.pass
    Passes/DownsampleMinAvgMaxCS.pass
    Passes/DownsampleMipChain.pass
    Passes/EnvironmentCubeMapDepthMSAA.pass
    Passes/EnvironmentCubeMapForwardMSAA.pass
    Passes/EnvironmentCubeMapForwardSubsurfaceMSAA.pass
    Passes/EnvironmentCubeMapPipeline.pass
    Passes/EnvironmentCubeMapSkyBox.pass
    Passes/EsmShadowmaps.pass
    Passes/EyeAdaptation.pass
    Passes/FastDepthAwareBlur.pass
    Passes/FastDepthAwareBlurHor.pass
    Passes/FastDepthAwareBlurVer.pass
    Passes/Forward.pass
    Passes/ForwardCheckerboard.pass
    Passes/ForwardMSAA.pass
    Passes/ForwardSubsurfaceMSAA.pass
    Passes/FullscreenCopy.pass
    Passes/FullscreenOutputOnly.pass
    Passes/HDRColorGrading.pass
    Passes/ImGui.pass
    Passes/KawaseShadowBlur.pass
    Passes/LightAdaptationParent.pass
    Passes/LightCulling.pass
    Passes/LightCullingHeatmap.pass
    Passes/LightCullingParent.pass
    Passes/LightCullingRemap.pass
    Passes/LightCullingTilePrepareMSAA.pass
    Passes/LookModificationComposite.pass
    Passes/LookModificationTransform.pass
    Passes/LowEndForward.pass
    Passes/LowEndPipeline.pass
    Passes/LuminanceHeatmap.pass
    Passes/LuminanceHistogramGenerator.pass
    Passes/LutGeneration.pass
    Passes/MainPipeline.pass
    Passes/MainPipelineRenderToTexture.pass
    Passes/MeshMotionVector.pass
    Passes/ModulateTexture.pass
    Passes/MorphTarget.pass
    Passes/MotionVectorParent.pass
    Passes/MSAAResolveColor.pass
    Passes/MSAAResolveCustom.pass
    Passes/MSAAResolveDepth.pass
    Passes/NewDepthOfField.pass
    Passes/NewDepthOfFieldComposite.pass
    Passes/NewDepthOfFieldDownsample.pass
    Passes/NewDepthOfFieldFilterLarge.pass
    Passes/NewDepthOfFieldFilterSmall.pass
    Passes/NewDepthOfFieldTile3x3.pass
    Passes/NewDepthOfFieldTileReduce.pass
    Passes/OpaqueParent.pass
    Passes/PostProcessParent.pass
    Passes/ProjectedShadowmaps.pass
    Passes/RayTracingAccelerationStructure.pass
    Passes/ReflectionComposite.pass
    Passes/ReflectionCopyFrameBuffer.pass
    Passes/ReflectionGlobalFullscreen.pass
    Passes/ReflectionProbeBlendWeight.pass
    Passes/ReflectionProbeRenderInner.pass
    Passes/ReflectionProbeRenderOuter.pass
    Passes/ReflectionProbeStencil.pass
    Passes/Reflections.pass
    Passes/ReflectionScreenSpace.pass
    Passes/ReflectionScreenSpaceBlur.pass
    Passes/ReflectionScreenSpaceBlurHorizontal.pass
    Passes/ReflectionScreenSpaceBlurMobile.pass
    Passes/ReflectionScreenSpaceBlurVertical.pass
    Passes/ReflectionScreenSpaceComposite.pass
    Passes/ReflectionScreenSpaceMobile.pass
    Passes/ReflectionScreenSpaceTrace.pass
    Passes/ShadowParent.pass
    Passes/Skinning.pass
    Passes/SkyBox.pass
    Passes/SkyBox_TwoOutputs.pass
    Passes/SMAA1xApplyLinearHDRColor.pass
    Passes/SMAA1xApplyPerceptualColor.pass
    Passes/SMAABlendingWeightCalculation.pass
    Passes/SMAAConvertToPerceptualColor.pass
    Passes/SMAAEdgeDetection.pass
    Passes/SMAANeighborhoodBlending.pass
    Passes/SsaoCompute.pass
    Passes/SsaoParent.pass
    Passes/SubsurfaceScattering.pass
    Passes/Taa.pass
    Passes/ToolsPipeline.pass
    Passes/ToolsPipelineRenderToTexture.pass
    Passes/Transparent.pass
    Passes/TransparentParent.pass
    Passes/UI.pass
    Passes/UIParent.pass
    Scripts/material_find_overrides_demo.lua
    Scripts/material_property_overrides_demo.lua
    ShaderLib/3rdParty/Features/PostProcessing/KelvinToRgb.azsli
    ShaderLib/3rdParty/Features/PostProcessing/PSstyleColorBlends_NonSeparable.azsli
    ShaderLib/3rdParty/Features/PostProcessing/PSstyleColorBlends_Separable.azsli
    ShaderLib/Atom/Features/BlendUtility.azsli
    ShaderLib/Atom/Features/IndirectRendering.azsli
    ShaderLib/Atom/Features/MatrixUtility.azsli
    ShaderLib/Atom/Features/ParallaxMapping.azsli
    ShaderLib/Atom/Features/ShaderQualityOptions.azsli
    ShaderLib/Atom/Features/SphericalHarmonicsUtility.azsli
    ShaderLib/Atom/Features/SrgSemantics.azsli
    ShaderLib/Atom/Features/ColorManagement/TransformColor.azsli
    ShaderLib/Atom/Features/ColorManagement/GeneratedTransforms/AcesCcToAcesCg.azsli
    ShaderLib/Atom/Features/ColorManagement/GeneratedTransforms/AcesCgToAcesCc.azsli
    ShaderLib/Atom/Features/ColorManagement/GeneratedTransforms/AcesCg_To_LinearSrgb.azsli
    ShaderLib/Atom/Features/ColorManagement/GeneratedTransforms/Aces_To_AcesCg.azsli
    ShaderLib/Atom/Features/ColorManagement/GeneratedTransforms/CalculateLuminance_AcesCg.azsli
    ShaderLib/Atom/Features/ColorManagement/GeneratedTransforms/CalculateLuminance_LinearSrgb.azsli
    ShaderLib/Atom/Features/ColorManagement/GeneratedTransforms/LinearSrgb_To_AcesCg.azsli
    ShaderLib/Atom/Features/ColorManagement/GeneratedTransforms/LinearSrgb_To_Srgb.azsli
    ShaderLib/Atom/Features/ColorManagement/GeneratedTransforms/Srgb_To_LinearSrgb.azsli
    ShaderLib/Atom/Features/CoreLights/PhotometricValue.azsli
    ShaderLib/Atom/Features/Decals/DecalTextureUtil.azsli
    ShaderLib/Atom/Features/LightCulling/LightCullingShared.azsli
    ShaderLib/Atom/Features/LightCulling/LightCullingTileIterator.azsli
    ShaderLib/Atom/Features/LightCulling/NVLC.azsli
    ShaderLib/Atom/Features/Math/Filter.azsli
    ShaderLib/Atom/Features/Math/FilterPassSrg.azsli
    ShaderLib/Atom/Features/Math/IntersectionTests.azsli
    ShaderLib/Atom/Features/MorphTargets/MorphTargetCompression.azsli
    ShaderLib/Atom/Features/PBR/AlphaUtils.azsli
    ShaderLib/Atom/Features/PBR/BackLighting.azsli
    ShaderLib/Atom/Features/PBR/Decals.azsli
    ShaderLib/Atom/Features/PBR/DefaultObjectSrg.azsli
    ShaderLib/Atom/Features/PBR/ForwardPassOutput.azsli
    ShaderLib/Atom/Features/PBR/ForwardPassSrg.azsli
    ShaderLib/Atom/Features/PBR/ForwardSubsurfacePassOutput.azsli
    ShaderLib/Atom/Features/PBR/Hammersley.azsli
    ShaderLib/Atom/Features/PBR/LightingOptions.azsli
    ShaderLib/Atom/Features/PBR/LightingUtils.azsli
    ShaderLib/Atom/Features/PBR/Lighting/DualSpecularLighting.azsli
    ShaderLib/Atom/Features/PBR/Lighting/EnhancedLighting.azsli
    ShaderLib/Atom/Features/PBR/Lighting/LightingData.azsli
    ShaderLib/Atom/Features/PBR/Lighting/SkinLighting.azsli
    ShaderLib/Atom/Features/PBR/Lighting/StandardLighting.azsli
    ShaderLib/Atom/Features/PBR/Lights/CapsuleLight.azsli
    ShaderLib/Atom/Features/PBR/Lights/DirectionalLight.azsli
    ShaderLib/Atom/Features/PBR/Lights/DiskLight.azsli
    ShaderLib/Atom/Features/PBR/Lights/Ibl.azsli
    ShaderLib/Atom/Features/PBR/Lights/Lights.azsli
    ShaderLib/Atom/Features/PBR/Lights/LightTypesCommon.azsli
    ShaderLib/Atom/Features/PBR/Lights/Ltc.azsli
    ShaderLib/Atom/Features/PBR/Lights/PointLight.azsli
    ShaderLib/Atom/Features/PBR/Lights/PolygonLight.azsli
    ShaderLib/Atom/Features/PBR/Lights/QuadLight.azsli
    ShaderLib/Atom/Features/PBR/Lights/SimplePointLight.azsli
    ShaderLib/Atom/Features/PBR/Lights/SimpleSpotLight.azsli
    ShaderLib/Atom/Features/PBR/Microfacet/Brdf.azsli
    ShaderLib/Atom/Features/PBR/Microfacet/Fresnel.azsli
    ShaderLib/Atom/Features/PBR/Microfacet/Ggx.azsli
    ShaderLib/Atom/Features/PBR/Surfaces/AnisotropicSurfaceData.azsli
    ShaderLib/Atom/Features/PBR/Surfaces/BasePbrSurfaceData.azsli
    ShaderLib/Atom/Features/PBR/Surfaces/ClearCoatSurfaceData.azsli
    ShaderLib/Atom/Features/PBR/Surfaces/DualSpecularSurface.azsli
    ShaderLib/Atom/Features/PBR/Surfaces/EnhancedSurface.azsli
    ShaderLib/Atom/Features/PBR/Surfaces/SkinSurface.azsli
    ShaderLib/Atom/Features/PBR/Surfaces/StandardSurface.azsli
    ShaderLib/Atom/Features/PBR/Surfaces/TransmissionSurfaceData.azsli
    ShaderLib/Atom/Features/PostProcessing/Aces.azsli
    ShaderLib/Atom/Features/PostProcessing/AcesColorSpaceConversion.azsli
    ShaderLib/Atom/Features/PostProcessing/FullscreenPixelInfo.azsli
    ShaderLib/Atom/Features/PostProcessing/FullscreenVertex.azsli
    ShaderLib/Atom/Features/PostProcessing/FullscreenVertexInfo.azsli
    ShaderLib/Atom/Features/PostProcessing/FullscreenVertexUtil.azsli
    ShaderLib/Atom/Features/PostProcessing/GlyphData.azsli
    ShaderLib/Atom/Features/PostProcessing/GlyphRender.azsli
    ShaderLib/Atom/Features/PostProcessing/HDRColorGradingCommon.azsl
    ShaderLib/Atom/Features/PostProcessing/PostProcessUtil.azsli
    ShaderLib/Atom/Features/PostProcessing/Shapers.azsli
    ShaderLib/Atom/Features/RayTracing/RayTracingMaterialSrg.azsli
    ShaderLib/Atom/Features/RayTracing/RayTracingMaterialUtils.azsli
    ShaderLib/Atom/Features/RayTracing/RayTracingSceneSrg.azsli
    ShaderLib/Atom/Features/RayTracing/RayTracingSceneUtils.azsli
    ShaderLib/Atom/Features/RayTracing/RayTracingSrgs.azsl
    ShaderLib/Atom/Features/RayTracing/RayTracingSrgs.shader
    ShaderLib/Atom/Features/ScreenSpace/ScreenSpaceUtil.azsli
    ShaderLib/Atom/Features/Shadow/BicubicPcfFilters.azsli
    ShaderLib/Atom/Features/Shadow/DirectionalLightShadow.azsli
    ShaderLib/Atom/Features/Shadow/ESM.azsli
    ShaderLib/Atom/Features/Shadow/NormalOffsetShadows.azsli
    ShaderLib/Atom/Features/Shadow/ProjectedShadow.azsli
    ShaderLib/Atom/Features/Shadow/ReceiverPlaneDepthBias.azsli
    ShaderLib/Atom/Features/Shadow/Shadow.azsli
    ShaderLib/Atom/Features/Shadow/ShadowmapAtlasLib.azsli
    ShaderLib/Atom/Features/Skin/SkinObjectSrg.azsli
    ShaderLib/Atom/Features/Vertex/VertexHelper.azsli
    ShaderResourceGroups/SceneSrg.azsli
    ShaderResourceGroups/SceneSrgAll.azsli
    ShaderResourceGroups/ViewSrg.azsli
    ShaderResourceGroups/ViewSrgAll.azsli
    ShaderResourceGroups/CoreLights/SceneSrg.azsli
    ShaderResourceGroups/CoreLights/ViewSrg.azsli
    ShaderResourceGroups/Decals/ViewSrg.azsli
    ShaderResourceGroups/PostProcessing/SceneSrg.azsli
    ShaderResourceGroups/PostProcessing/ViewSrg.azsli
    ShaderResourceGroups/SkyBox/SceneSrg.azsli
    Shaders/ForwardPassSrg.azsl
    Shaders/ForwardPassSrg.shader
    Shaders/AuxGeom/AuxGeomObject.azsl
    Shaders/AuxGeom/AuxGeomObject.shader
    Shaders/AuxGeom/AuxGeomObjectLit.azsl
    Shaders/AuxGeom/AuxGeomObjectLit.shader
    Shaders/AuxGeom/AuxGeomWorld.azsl
    Shaders/AuxGeom/AuxGeomWorld.shader
    Shaders/AuxGeom/ObjectSrg.azsli
    Shaders/AuxGeom/ObjectSrgLit.azsli
    Shaders/BRDFTexture/BRDFTextureCS.azsl
    Shaders/BRDFTexture/BRDFTextureCS.shader
    Shaders/Checkerboard/CheckerboardColorResolveCS.azsl
    Shaders/Checkerboard/CheckerboardColorResolveCS.shader
    Shaders/ColorGrading/LutGeneration.azsl
    Shaders/ColorGrading/LutGeneration.shader
    Shaders/Depth/DepthPass.azsl
    Shaders/Depth/DepthPass.shader
    Shaders/Depth/DepthPassCommon.azsli
    Shaders/Depth/DepthPassSkin.azsl
    Shaders/Depth/DepthPassSkin.shader
    Shaders/Depth/DepthPassTransparentMax.shader
    Shaders/Depth/DepthPassTransparentMin.shader
    Shaders/DiffuseGlobalIllumination/DiffuseComposite.azsl
    Shaders/DiffuseGlobalIllumination/DiffuseComposite.shader
    Shaders/DiffuseGlobalIllumination/DiffuseComposite_nomsaa.azsl
    Shaders/DiffuseGlobalIllumination/DiffuseGlobalFullscreen.azsl
    Shaders/DiffuseGlobalIllumination/DiffuseGlobalFullscreen.shader
    Shaders/DiffuseGlobalIllumination/DiffuseGlobalFullscreen_nomsaa.azsl
    Shaders/DiffuseGlobalIllumination/DiffuseProbeGridDownsample.azsl
    Shaders/DiffuseGlobalIllumination/DiffuseProbeGridDownsample.shader
    Shaders/DiffuseGlobalIllumination/DiffuseProbeGridDownsample_nomsaa.azsl
    Shaders/ImGui/ImGui.azsl
    Shaders/ImGui/ImGui.shader
    Shaders/LightCulling/LightCulling.azsl
    Shaders/LightCulling/LightCulling.shader
    Shaders/LightCulling/LightCullingHeatmap.azsl
    Shaders/LightCulling/LightCullingHeatmap.shader
    Shaders/LightCulling/LightCullingRemap.azsl
    Shaders/LightCulling/LightCullingRemap.shader
    Shaders/LightCulling/LightCullingTilePrepare.azsl
    Shaders/LightCulling/LightCullingTilePrepare.shader
    Shaders/LuxCore/RenderTexture.azsl
    Shaders/LuxCore/RenderTexture.shader
    Shaders/MorphTargets/MorphTargetCS.azsl
    Shaders/MorphTargets/MorphTargetCS.shader
    Shaders/MorphTargets/MorphTargetSRG.azsli
    Shaders/MotionVector/CameraMotionVector.azsl
    Shaders/MotionVector/CameraMotionVector.shader
    Shaders/MotionVector/MeshMotionVector.azsl
    Shaders/MotionVector/MeshMotionVector.shader
    Shaders/MotionVector/MeshMotionVectorCommon.azsli
    Shaders/MotionVector/MeshMotionVectorSkin.azsl
    Shaders/MotionVector/MeshMotionVectorSkin.shader
    Shaders/PostProcessing/AcesOutputTransformLut.azsl
    Shaders/PostProcessing/AcesOutputTransformLut.shader
    Shaders/PostProcessing/ApplyShaperLookupTable.azsl
    Shaders/PostProcessing/ApplyShaperLookupTable.shader
    Shaders/PostProcessing/BakeAcesOutputTransformLutCS.azsl
    Shaders/PostProcessing/BakeAcesOutputTransformLutCS.shader
    Shaders/PostProcessing/BlendColorGradingLuts.azsl
    Shaders/PostProcessing/BlendColorGradingLuts.shader
    Shaders/PostProcessing/BloomBlurCS.azsl
    Shaders/PostProcessing/BloomBlurCS.shader
    Shaders/PostProcessing/BloomCompositeCS.azsl
    Shaders/PostProcessing/BloomCompositeCS.shader
    Shaders/PostProcessing/BloomDownsampleCS.azsl
    Shaders/PostProcessing/BloomDownsampleCS.shader
    Shaders/PostProcessing/ContrastAdaptiveSharpening.azsl
    Shaders/PostProcessing/ContrastAdaptiveSharpening.shader
    Shaders/PostProcessing/ConvertToAcescg.azsl
    Shaders/PostProcessing/ConvertToAcescg.shader
    Shaders/PostProcessing/DepthDownsample.azsl
    Shaders/PostProcessing/DepthDownsample.shader
    Shaders/PostProcessing/DepthOfField.azsli
    Shaders/PostProcessing/DepthOfFieldBlurBokeh.azsl
    Shaders/PostProcessing/DepthOfFieldBlurBokeh.shader
    Shaders/PostProcessing/DepthOfFieldComposite.azsl
    Shaders/PostProcessing/DepthOfFieldComposite.shader
    Shaders/PostProcessing/DepthOfFieldDownSample.azsl
    Shaders/PostProcessing/DepthOfFieldDownSample.shader
    Shaders/PostProcessing/DepthOfFieldMask.azsl
    Shaders/PostProcessing/DepthOfFieldMask.shader
    Shaders/PostProcessing/DepthOfFieldPrepare.azsl
    Shaders/PostProcessing/DepthOfFieldPrepare.shader
    Shaders/PostProcessing/DepthOfFieldWriteFocusDepthFromGpu.azsl
    Shaders/PostProcessing/DepthOfFieldWriteFocusDepthFromGpu.shader
    Shaders/PostProcessing/DepthToLinearDepth.azsl
    Shaders/PostProcessing/DepthToLinearDepth.shader
    Shaders/PostProcessing/DepthUpsample.azsl
    Shaders/PostProcessing/DepthUpsample.shader
    Shaders/PostProcessing/DiffuseSpecularMerge.azsl
    Shaders/PostProcessing/DiffuseSpecularMerge.shader
    Shaders/PostProcessing/DisplayMapper.azsl
    Shaders/PostProcessing/DisplayMapper.shader
    Shaders/PostProcessing/DisplayMapperOnlyGammaCorrection.azsl
    Shaders/PostProcessing/DisplayMapperOnlyGammaCorrection.shader
    Shaders/PostProcessing/DownsampleLuminanceMinAvgMaxCS.azsl
    Shaders/PostProcessing/DownsampleLuminanceMinAvgMaxCS.shader
    Shaders/PostProcessing/DownsampleMinAvgMaxCS.azsl
    Shaders/PostProcessing/DownsampleMinAvgMaxCS.shader
    Shaders/PostProcessing/EyeAdaptation.azsl
    Shaders/PostProcessing/EyeAdaptation.shader
    Shaders/PostProcessing/EyeAdaptationUtil.azsli
    Shaders/PostProcessing/FastDepthAwareBlurCommon.azsli
    Shaders/PostProcessing/FastDepthAwareBlurHor.azsl
    Shaders/PostProcessing/FastDepthAwareBlurHor.shader
    Shaders/PostProcessing/FastDepthAwareBlurVer.azsl
    Shaders/PostProcessing/FastDepthAwareBlurVer.shader
    Shaders/PostProcessing/FullscreenCopy.azsl
    Shaders/PostProcessing/FullscreenCopy.shader
    Shaders/PostProcessing/HDRColorGrading.azsl
    Shaders/PostProcessing/HDRColorGrading.shader
    Shaders/PostProcessing/LookModificationTransform.azsl
    Shaders/PostProcessing/LookModificationTransform.shader
    Shaders/PostProcessing/LuminanceHeatmap.azsl
    Shaders/PostProcessing/LuminanceHeatmap.shader
    Shaders/PostProcessing/LuminanceHistogramCommon.azsli
    Shaders/PostProcessing/LuminanceHistogramGenerator.azsl
    Shaders/PostProcessing/LuminanceHistogramGenerator.shader
    Shaders/PostProcessing/ModulateTexture.azsl
    Shaders/PostProcessing/ModulateTexture.shader
    Shaders/PostProcessing/MSAAResolveCustom.azsl
    Shaders/PostProcessing/MSAAResolveCustom.shader
    Shaders/PostProcessing/MSAAResolveDepth.azsl
    Shaders/PostProcessing/MSAAResolveDepth.shader
    Shaders/PostProcessing/NewDepthOfFieldCommon.azsli
    Shaders/PostProcessing/NewDepthOfFieldComposite.azsl
    Shaders/PostProcessing/NewDepthOfFieldComposite.shader
    Shaders/PostProcessing/NewDepthOfFieldDownsample.azsl
    Shaders/PostProcessing/NewDepthOfFieldDownsample.shader
    Shaders/PostProcessing/NewDepthOfFieldFilterLarge.azsl
    Shaders/PostProcessing/NewDepthOfFieldFilterLarge.shader
    Shaders/PostProcessing/NewDepthOfFieldFilterSmall.azsl
    Shaders/PostProcessing/NewDepthOfFieldFilterSmall.shader
    Shaders/PostProcessing/NewDepthOfFieldTile3x3.azsl
    Shaders/PostProcessing/NewDepthOfFieldTile3x3.shader
    Shaders/PostProcessing/NewDepthOfFieldTileReduce.azsl
    Shaders/PostProcessing/NewDepthOfFieldTileReduce.shader
    Shaders/PostProcessing/OutputTransform.azsl
    Shaders/PostProcessing/OutputTransform.shader
    Shaders/PostProcessing/ScreenSpaceSubsurfaceScatteringCS.azsl
    Shaders/PostProcessing/ScreenSpaceSubsurfaceScatteringCS.shader
    Shaders/PostProcessing/SMAA.azsli
    Shaders/PostProcessing/SMAABlendingWeightCalculation.azsl
    Shaders/PostProcessing/SMAABlendingWeightCalculation.shader
    Shaders/PostProcessing/SMAAConvertToPerceptualColor.azsl
    Shaders/PostProcessing/SMAAConvertToPerceptualColor.shader
    Shaders/PostProcessing/SMAAEdgeDetection.azsl
    Shaders/PostProcessing/SMAAEdgeDetection.shader
    Shaders/PostProcessing/SMAANeighborhoodBlending.azsl
    Shaders/PostProcessing/SMAANeighborhoodBlending.shader
    Shaders/PostProcessing/SMAAUtils.azsli
    Shaders/PostProcessing/SsaoCompute.azsl
    Shaders/PostProcessing/SsaoCompute.shader
    Shaders/PostProcessing/Taa.azsl
    Shaders/PostProcessing/Taa.shader
    Shaders/PostProcessing/UniformColor.azsl
    Shaders/PostProcessing/UniformColor.shader
    Shaders/Reflections/ReflectionCommon.azsli
    Shaders/Reflections/ReflectionComposite.azsl
    Shaders/Reflections/ReflectionComposite.shader
    Shaders/Reflections/ReflectionComposite_nomsaa.azsl
    Shaders/Reflections/ReflectionGlobalFullscreen.azsl
    Shaders/Reflections/ReflectionGlobalFullscreen.shader
    Shaders/Reflections/ReflectionGlobalFullscreen_nomsaa.azsl
    Shaders/Reflections/ReflectionProbeBlendWeight.azsl
    Shaders/Reflections/ReflectionProbeBlendWeight.shader
    Shaders/Reflections/ReflectionProbeRenderCommon.azsli
    Shaders/Reflections/ReflectionProbeRenderInner.azsl
    Shaders/Reflections/ReflectionProbeRenderInner.shader
    Shaders/Reflections/ReflectionProbeRenderObjectSrg.azsli
    Shaders/Reflections/ReflectionProbeRenderOuter.azsl
    Shaders/Reflections/ReflectionProbeRenderOuter.shader
    Shaders/Reflections/ReflectionProbeStencil.azsl
    Shaders/Reflections/ReflectionProbeStencil.shader
    Shaders/Reflections/ReflectionScreenSpaceBlurCommon.azsli
    Shaders/Reflections/ReflectionScreenSpaceBlurHorizontal.azsl
    Shaders/Reflections/ReflectionScreenSpaceBlurHorizontal.shader
    Shaders/Reflections/ReflectionScreenSpaceBlurVertical.azsl
    Shaders/Reflections/ReflectionScreenSpaceBlurVertical.shader
    Shaders/Reflections/ReflectionScreenSpaceComposite.azsl
    Shaders/Reflections/ReflectionScreenSpaceComposite.shader
    Shaders/Reflections/ReflectionScreenSpaceTrace.azsl
    Shaders/Reflections/ReflectionScreenSpaceTrace.azsli
    Shaders/Reflections/ReflectionScreenSpaceTrace.shader
    Shaders/ScreenSpace/DeferredFog.azsl
    Shaders/ScreenSpace/DeferredFog.shader
    Shaders/Shadow/DepthExponentiation.azsl
    Shaders/Shadow/DepthExponentiation.shader
    Shaders/Shadow/KawaseShadowBlur.azsl
    Shaders/Shadow/KawaseShadowBlur.shader
    Shaders/Shadow/Shadowmap.azsl
    Shaders/Shadow/Shadowmap.shader
    Shaders/Shadow/ShadowmapCommon.azsli
    Shaders/Shadow/ShadowmapSkin.azsl
    Shaders/Shadow/ShadowmapSkin.shader
    Shaders/SkinnedMesh/LinearSkinningCS.azsl
    Shaders/SkinnedMesh/LinearSkinningCS.shader
    Shaders/SkinnedMesh/LinearSkinningPassSRG.azsli
    Shaders/SkyBox/SkyBox.azsl
    Shaders/SkyBox/SkyBox.shader
    Shaders/SkyBox/SkyBox_TwoOutputs.azsl
    Shaders/SkyBox/SkyBox_TwoOutputs.shader
) 
