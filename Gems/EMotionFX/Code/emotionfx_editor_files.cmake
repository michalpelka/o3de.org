#
# Copyright (c) Contributors to the Open 3D Engine Project. For complete copyright and license terms please see the LICENSE at the root of this distribution.
# 
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

set(FILES
    ../Assets/Editor/Layouts/Layouts.qrc
    ../Assets/Editor/Images/Icons/Resources.qrc
    ../Assets/Editor/Images/Icons/ActorComponent.svg
    ../Assets/Editor/Images/Icons/AnimGraphComponent.svg
    Source/Integration/Editor/Components/EditorActorComponent.h
    Source/Integration/Editor/Components/EditorActorComponent.cpp
    Source/Integration/Editor/Components/EditorAnimAudioComponent.h
    Source/Integration/Editor/Components/EditorAnimAudioComponent.cpp
    Source/Integration/Editor/Components/EditorAnimGraphComponent.h
    Source/Integration/Editor/Components/EditorAnimGraphComponent.cpp
    Source/Integration/Editor/Components/EditorSimpleMotionComponent.h
    Source/Integration/Editor/Components/EditorSimpleMotionComponent.cpp
    Source/Integration/Editor/Components/EditorSimpleLODComponent.h
    Source/Integration/Editor/Components/EditorSimpleLODComponent.cpp
    Source/Editor/ActorEditorBus.h
    Source/Editor/ActorJointBrowseEdit.h
    Source/Editor/ActorJointBrowseEdit.cpp
    Source/Editor/AnimGraphEditorBus.h
    Source/Editor/ColliderContainerWidget.h
    Source/Editor/ColliderContainerWidget.cpp
    Source/Editor/ColliderHelpers.h
    Source/Editor/ColliderHelpers.cpp
    Source/Editor/InputDialogValidatable.h
    Source/Editor/InputDialogValidatable.cpp
    Source/Editor/JointSelectionWidget.h
    Source/Editor/JointSelectionWidget.cpp
    Source/Editor/JointSelectionDialog.h
    Source/Editor/JointSelectionDialog.cpp
    Source/Editor/LineEditValidatable.h
    Source/Editor/LineEditValidatable.cpp
    Source/Editor/NotificationWidget.h
    Source/Editor/NotificationWidget.cpp
    Source/Editor/ObjectEditor.h
    Source/Editor/ObjectEditor.cpp
    Source/Editor/QtMetaTypes.h
    Source/Editor/ReselectingTreeView.cpp
    Source/Editor/ReselectingTreeView.h
    Source/Editor/SelectionProxyModel.h
    Source/Editor/SelectionProxyModel.cpp
    Source/Editor/SimulatedObjectBus.h
    Source/Editor/SimulatedObjectHelpers.h
    Source/Editor/SimulatedObjectHelpers.cpp
    Source/Editor/SimulatedObjectModel.h
    Source/Editor/SimulatedObjectModel.cpp
    Source/Editor/SimulatedObjectModelCallbacks.cpp
    Source/Editor/SkeletonModel.h
    Source/Editor/SkeletonModel.cpp
    Source/Editor/SkeletonModelJointWidget.h
    Source/Editor/SkeletonModelJointWidget.cpp
    Source/Editor/SkeletonSortFilterProxyModel.h
    Source/Editor/SkeletonSortFilterProxyModel.cpp
    Source/Editor/TagSelector.h
    Source/Editor/TagSelector.cpp
    Source/Editor/TypeChoiceButton.h
    Source/Editor/TypeChoiceButton.cpp
    Source/Editor/Plugins/Cloth/ClothJointInspectorPlugin.h
    Source/Editor/Plugins/Cloth/ClothJointInspectorPlugin.cpp
    Source/Editor/Plugins/Cloth/ClothJointWidget.h
    Source/Editor/Plugins/Cloth/ClothJointWidget.cpp
    Source/Editor/Plugins/SkeletonOutliner/SkeletonOutlinerBus.h
    Source/Editor/Plugins/SkeletonOutliner/SkeletonOutlinerPlugin.h
    Source/Editor/Plugins/SkeletonOutliner/SkeletonOutlinerPlugin.cpp
    Source/Editor/Plugins/HitDetection/HitDetectionJointInspectorPlugin.h
    Source/Editor/Plugins/HitDetection/HitDetectionJointInspectorPlugin.cpp
    Source/Editor/Plugins/HitDetection/HitDetectionJointWidget.h
    Source/Editor/Plugins/HitDetection/HitDetectionJointWidget.cpp
    Source/Editor/Plugins/Ragdoll/RagdollJointLimitWidget.h
    Source/Editor/Plugins/Ragdoll/RagdollJointLimitWidget.cpp
    Source/Editor/Plugins/Ragdoll/RagdollNodeInspectorPlugin.h
    Source/Editor/Plugins/Ragdoll/RagdollNodeInspectorPlugin.cpp
    Source/Editor/Plugins/Ragdoll/RagdollNodeWidget.h
    Source/Editor/Plugins/Ragdoll/RagdollNodeWidget.cpp
    Source/Editor/Plugins/SimulatedObject/SimulatedJointWidget.h
    Source/Editor/Plugins/SimulatedObject/SimulatedJointWidget.cpp
    Source/Editor/Plugins/SimulatedObject/SimulatedObjectActionManager.h
    Source/Editor/Plugins/SimulatedObject/SimulatedObjectActionManager.cpp
    Source/Editor/Plugins/SimulatedObject/SimulatedObjectWidget.h
    Source/Editor/Plugins/SimulatedObject/SimulatedObjectWidget.cpp
    Source/Editor/Plugins/SimulatedObject/SimulatedObjectColliderWidget.h
    Source/Editor/Plugins/SimulatedObject/SimulatedObjectColliderWidget.cpp
    Source/Editor/Plugins/SimulatedObject/SimulatedObjectSelectionWindow.h
    Source/Editor/Plugins/SimulatedObject/SimulatedObjectSelectionWindow.cpp
    Source/Editor/Plugins/SimulatedObject/SimulatedObjectSelectionWidget.h
    Source/Editor/Plugins/SimulatedObject/SimulatedObjectSelectionWidget.cpp
    Source/Editor/PropertyWidgets/AnimGraphNodeHandler.h
    Source/Editor/PropertyWidgets/AnimGraphNodeHandler.cpp
    Source/Editor/PropertyWidgets/AnimGraphNodeNameHandler.h
    Source/Editor/PropertyWidgets/AnimGraphNodeNameHandler.cpp
    Source/Editor/PropertyWidgets/AnimGraphParameterHandler.h
    Source/Editor/PropertyWidgets/AnimGraphParameterHandler.cpp
    Source/Editor/PropertyWidgets/AnimGraphParameterMaskHandler.h
    Source/Editor/PropertyWidgets/AnimGraphParameterMaskHandler.cpp
    Source/Editor/PropertyWidgets/AnimGraphTagHandler.h
    Source/Editor/PropertyWidgets/AnimGraphTagHandler.cpp
    Source/Editor/PropertyWidgets/AnimGraphTransitionHandler.h
    Source/Editor/PropertyWidgets/AnimGraphTransitionHandler.cpp
    Source/Editor/PropertyWidgets/ActorMorphTargetHandler.h
    Source/Editor/PropertyWidgets/ActorMorphTargetHandler.cpp
    Source/Editor/PropertyWidgets/ActorJointHandler.h
    Source/Editor/PropertyWidgets/ActorJointHandler.cpp
    Source/Editor/PropertyWidgets/ActorGoalNodeHandler.h
    Source/Editor/PropertyWidgets/ActorGoalNodeHandler.cpp
    Source/Editor/PropertyWidgets/BlendSpaceEvaluatorHandler.h
    Source/Editor/PropertyWidgets/BlendSpaceEvaluatorHandler.cpp
    Source/Editor/PropertyWidgets/BlendSpaceMotionHandler.h
    Source/Editor/PropertyWidgets/BlendSpaceMotionHandler.cpp
    Source/Editor/PropertyWidgets/BlendSpaceMotionContainerHandler.h
    Source/Editor/PropertyWidgets/BlendSpaceMotionContainerHandler.cpp
    Source/Editor/PropertyWidgets/EventDataHandler.cpp
    Source/Editor/PropertyWidgets/EventDataHandler.h
    Source/Editor/PropertyWidgets/MotionSetMotionIdHandler.h
    Source/Editor/PropertyWidgets/MotionSetMotionIdHandler.cpp
    Source/Editor/PropertyWidgets/MotionSetNameHandler.h
    Source/Editor/PropertyWidgets/MotionSetNameHandler.cpp
    Source/Editor/PropertyWidgets/MotionDataHandler.h
    Source/Editor/PropertyWidgets/MotionDataHandler.cpp
    Source/Editor/PropertyWidgets/RagdollJointHandler.h
    Source/Editor/PropertyWidgets/RagdollJointHandler.cpp
    Source/Editor/PropertyWidgets/BlendTreeRotationLimitHandler.cpp
    Source/Editor/PropertyWidgets/BlendTreeRotationLimitHandler.h
    Source/Editor/PropertyWidgets/TransitionStateFilterLocalHandler.h
    Source/Editor/PropertyWidgets/TransitionStateFilterLocalHandler.cpp
    Source/Editor/PropertyWidgets/PropertyTypes.h
    Source/Editor/PropertyWidgets/PropertyTypes.cpp
    Source/Editor/PropertyWidgets/PropertyWidgetAllocator.h
    Source/Editor/PropertyWidgets/BlendNParamWeightsHandler.h
    Source/Editor/PropertyWidgets/BlendNParamWeightsHandler.cpp
    Source/Editor/PropertyWidgets/LODTreeSelectionHandler.h
    Source/Editor/PropertyWidgets/LODTreeSelectionHandler.cpp
    Source/Editor/PropertyWidgets/LODTreeSelectionWidget.h
    Source/Editor/PropertyWidgets/LODTreeSelectionWidget.cpp
    Source/Editor/PropertyWidgets/LODSceneGraphWidget.h
    Source/Editor/PropertyWidgets/LODSceneGraphWidget.cpp
    Source/Editor/PropertyWidgets/LODSceneGraphWidget.ui
    Source/Editor/PropertyWidgets/SimulatedObjectNameHandler.h
    Source/Editor/PropertyWidgets/SimulatedObjectNameHandler.cpp
    Source/Editor/PropertyWidgets/SimulatedObjectSelectionHandler.h
    Source/Editor/PropertyWidgets/SimulatedObjectSelectionHandler.cpp
    Source/Editor/PropertyWidgets/SimulatedObjectColliderTagHandler.h
    Source/Editor/PropertyWidgets/SimulatedObjectColliderTagHandler.cpp
)
