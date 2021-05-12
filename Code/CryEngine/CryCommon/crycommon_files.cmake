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
    QTangent.h
    CryCommon.cpp
    Allocator.h
    FinalizingSpline.h
    IAudioInterfacesCommonData.h
    IAudioSystem.h
    IChunkFile.h
    ICmdLine.h
    IColorGradingController.h
    IConsole.h
    IEntityRenderState.h
    IEntityRenderState_info.cpp
    IFont.h
    IFunctorBase.h
    IFuncVariable.h
    IGem.h
    IGeneralMemoryHeap.h
    IGeomCache.h
    IImage.h
    IImageHandler.h
    IIndexedMesh.h
    IIndexedMesh_info.cpp
    ILevelSystem.h
    ILocalizationManager.h
    LocalizationManagerBus.h
    LocalizationManagerBus.inl
    ILog.h
    ILZ4Decompressor.h
    IMaterial.h
    IMemory.h
    IMeshBaking.h
    IMiniLog.h
    IMovieSystem.h
    IPhysics.h
    IPhysicsDebugRenderer.h
    IPostEffectGroup.h
    IProcess.h
    IReadWriteXMLSink.h
    IRenderAuxGeom.h
    IRenderer.h
    IRenderMesh.h
    IResourceCollector.h
    IResourceManager.h
    ISerialize.h
    IShader.h
    IShader_info.h
    ISplines.h
    IStatObj.h
    StatObjBus.h
    IStereoRenderer.h
    IStreamEngine.h
    IStreamEngineDefs.h
    ISurfaceType.h
    ISystem.h
    ITextModeConsole.h
    ITexture.h
    ITimer.h
    IValidator.h
    IVideoRenderer.h
    IViewSystem.h
    IWindowMessageHandler.h
    IXml.h
    IZLibCompressor.h
    IZlibDecompressor.h
    IZStdDecompressor.h
    IProximityTriggerSystem.h
    MicrophoneBus.h
    physinterface.h
    HMDBus.h
    VRCommon.h
    StereoRendererBus.h
    HeightmapUpdateNotificationBus.h
    IObjManager.h
    INavigationSystem.h
    IMNM.h
    AzDXGIFormat.h
    SFunctor.h
    FunctorBaseFunction.h
    CustomMemoryHeap.h
    FunctorBaseMember.h
    stridedptr.h
    Options.h
    SerializationTypes.h
    CryEndian.h
    CryRandomInternal.h
    Random.h
    LCGRandom.h
    MaterialUtils.h
    MTPseudoRandom.cpp
    CryTypeInfo.cpp
    BaseTypes.h
    CompileTimeAssert.h
    CryThreadSafeWorkerContainer.h
    CryThreadSafeRendererContainer.h
    intrusive_list.hpp
    MemoryAccess.h
    Algorithm.h
    AnimKey.h
    BitFiddling.h
    CGFContent.h
    CGFContent_info.cpp
    Common_TypeInfo.cpp
    CountedValue.h
    CrtDebugStats.h
    CryArray.h
    CryArray2d.h
    CryAssert.h
    CryCrc32.h
    CryCustomTypes.h
    CryFile.h
    CryFixedArray.h
    CryFixedString.h
    CryHeaders.h
    CryHeaders_info.cpp
    CryListenerSet.h
    CryMemoryAllocator.h
    CryMemoryManager.h
    CryLegacyAllocator.h
    CryName.h
    CryPath.h
    CryPodArray.h
    CryPtrArray.h
    CrySizer.h
    CryString.h
    CrySystemBus.h
    CryThread.h
    CryThreadImpl.h
    CryTypeInfo.h
    CryUtils.h
    CryVersion.h
    CryZlib.h
    FrameProfiler.h
    HashGrid.h
    HeapAllocator.h
    HeapContainer.h
    ImageExtensionHelper.cpp
    ImageExtensionHelper.h
    ImageExtensionHelper_info.h
    InplaceFactory.h
    LegacyAllocator.h
    MetaUtils.h
    MiniQueue.h
    MTPseudoRandom.h
    MultiThread.h
    MultiThread_Containers.h
    Name_TypeInfo.h
    NullAudioSystem.h
    PNoise3.h
    PoolAllocator.h
    primitives.h
    primitives_info.h
    ProjectDefines.h
    Range.h
    RenderContextConfig.h
    RingBuffer.h
    ScopeGuard.h
    ScopedVariableSetter.h
    SerializeFwd.h
    SimpleSerialize.h
    SmartPointersHelpers.h
    smartptr.h
    StackContainer.h
    STLGlobalAllocator.h
    STLPoolAllocator.h
    StlUtils.h
    StringUtils.h
    Synchronization.h
    Tarray.h
    Timer.h
    TimeValue.h
    TimeValue_info.h
    TypeInfo_decl.h
    TypeInfo_impl.h
    UnalignedBlit.h
    UnicodeBinding.h
    UnicodeEncoding.h
    UnicodeFunctions.h
    UnicodeIterator.h
    VectorMap.h
    VectorSet.h
    VertexFormats.h
    XMLBinaryHeaders.h
    RenderBus.h
    MainThreadRenderRequestBus.h
    OceanConstants.h
    PakLoadDataUtils.cpp
    PakLoadDataUtils.h
    TPool.h
    Cry_Matrix33.h
    Cry_Matrix34.h
    Cry_Matrix44.h
    Cry_MatrixDiag.h
    Cry_Vector4.h
    AABBSV.h
    Cry_Camera.h
    Cry_Color.h
    Cry_Geo.h
    Cry_GeoDistance.h
    Cry_GeoIntersect.h
    Cry_GeoOverlap.h
    Cry_Math.h
    Cry_Quat.h
    Cry_ValidNumber.h
    Cry_Vector2.h
    Cry_Vector3.h
    Cry_XOptimise.h
    CryHalf_info.h
    GeomQuery.h
    CryHalf.inl
    MathConversion.h
    Cry_HWMatrix.h
    Cry_HWVector3.h
    AndroidSpecific.h
    AppleSpecific.h
    Console_std.h
    CryAssert_Android.h
    CryAssert_impl.h
    CryAssert_iOS.h
    CryAssert_Linux.h
    CryAssert_Mac.h
    CryLibrary.cpp
    CryLibrary.h
    CryMemoryManager_impl.h
    CryThread_dummy.h
    CryThread_pthreads.h
    CryThread_windows.h
    CryThreadImpl_pthreads.h
    CryThreadImpl_windows.h
    CryWindows.h
    Linux32Specific.h
    Linux64Specific.h
    Linux_Win32Wrapper.h
    LinuxSpecific.h
    LoadScreenBus.h
    MacSpecific.h
    platform.h
    platform_impl.cpp
    Win32specific.h
    Win64specific.h
    stl/STLAlignedAlloc.h
    LyShine/IDraw2d.h
    LyShine/ILyShine.h
    LyShine/ISprite.h
    LyShine/IRenderGraph.h
    LyShine/UiAssetTypes.h
    LyShine/UiComponentTypes.h
    LyShine/UiBase.h
    LyShine/UiEntityContext.h
    LyShine/UiLayoutCellBase.h
    LyShine/UiSerializeHelpers.h
    LyShine/Animation/IUiAnimation.h
    LyShine/Bus/UiAnimateEntityBus.h
    LyShine/Bus/UiAnimationBus.h
    LyShine/Bus/UiButtonBus.h
    LyShine/Bus/UiCanvasBus.h
    LyShine/Bus/UiCanvasManagerBus.h
    LyShine/Bus/UiCanvasUpdateNotificationBus.h
    LyShine/Bus/UiCheckboxBus.h
    LyShine/Bus/UiCursorBus.h
    LyShine/Bus/UiDraggableBus.h
    LyShine/Bus/UiDropdownBus.h
    LyShine/Bus/UiDropdownOptionBus.h
    LyShine/Bus/UiDropTargetBus.h
    LyShine/Bus/UiDynamicLayoutBus.h
    LyShine/Bus/UiDynamicScrollBoxBus.h
    LyShine/Bus/UiEditorBus.h
    LyShine/Bus/UiEditorCanvasBus.h
    LyShine/Bus/UiEditorChangeNotificationBus.h
    LyShine/Bus/UiElementBus.h
    LyShine/Bus/UiEntityContextBus.h
    LyShine/Bus/UiFaderBus.h
    LyShine/Bus/UiFlipbookAnimationBus.h
    LyShine/Bus/UiGameEntityContextBus.h
    LyShine/Bus/UiImageBus.h
    LyShine/Bus/UiImageSequenceBus.h
    LyShine/Bus/UiIndexableImageBus.h
    LyShine/Bus/UiInitializationBus.h
    LyShine/Bus/UiInteractableActionsBus.h
    LyShine/Bus/UiInteractableBus.h
    LyShine/Bus/UiInteractableStatesBus.h
    LyShine/Bus/UiInteractionMaskBus.h
    LyShine/Bus/UiLayoutBus.h
    LyShine/Bus/UiLayoutCellBus.h
    LyShine/Bus/UiLayoutCellDefaultBus.h
    LyShine/Bus/UiLayoutColumnBus.h
    LyShine/Bus/UiLayoutControllerBus.h
    LyShine/Bus/UiLayoutFitterBus.h
    LyShine/Bus/UiLayoutGridBus.h
    LyShine/Bus/UiLayoutManagerBus.h
    LyShine/Bus/UiLayoutRowBus.h
    LyShine/Bus/UiMarkupButtonBus.h
    LyShine/Bus/UiMaskBus.h
    LyShine/Bus/UiNavigationBus.h
    LyShine/Bus/UiParticleEmitterBus.h
    LyShine/Bus/UiRadioButtonBus.h
    LyShine/Bus/UiRadioButtonCommunicationBus.h
    LyShine/Bus/UiRadioButtonGroupBus.h
    LyShine/Bus/UiRadioButtonGroupCommunicationBus.h
    LyShine/Bus/UiRenderBus.h
    LyShine/Bus/UiRenderControlBus.h
    LyShine/Bus/UiScrollableBus.h
    LyShine/Bus/UiScrollBarBus.h
    LyShine/Bus/UiScrollBoxBus.h
    LyShine/Bus/UiScrollerBus.h
    LyShine/Bus/UiSliderBus.h
    LyShine/Bus/UiSpawnerBus.h
    LyShine/Bus/UiSystemBus.h
    LyShine/Bus/UiTextBus.h
    LyShine/Bus/UiTextInputBus.h
    LyShine/Bus/UiTooltipBus.h
    LyShine/Bus/UiTooltipDataPopulatorBus.h
    LyShine/Bus/UiTooltipDisplayBus.h
    LyShine/Bus/UiTransform2dBus.h
    LyShine/Bus/UiTransformBus.h
    LyShine/Bus/UiVisualBus.h
    LyShine/Bus/Sprite/UiSpriteBus.h
    LyShine/Bus/World/UiCanvasOnMeshBus.h
    LyShine/Bus/World/UiCanvasRefBus.h
    LyShine/Bus/Tools/UiSystemToolsBus.h
    Maestro/Bus/EditorSequenceAgentComponentBus.h
    Maestro/Bus/EditorSequenceBus.h
    Maestro/Bus/EditorSequenceComponentBus.h
    Maestro/Bus/SequenceComponentBus.h
    Maestro/Bus/SequenceAgentComponentBus.h
    Maestro/Types/AnimNodeType.h
    Maestro/Types/AnimParamType.h
    Maestro/Types/AnimValue.h
    Maestro/Types/AnimValueType.h
    Maestro/Types/AssetBlendKey.h
    Maestro/Types/AssetBlends.h
    Maestro/Types/SequenceType.h
    Terrain/Bus/WorldMaterialRequestsBus.h
    Terrain/Bus/TerrainBus.h
    Terrain/Bus/TerrainRendererBus.h
    Terrain/Bus/HeightmapDataBus.h
    Terrain/Bus/TerrainProviderBus.h
    StaticInstance.h
    Pak/CryPakUtils.h
)
