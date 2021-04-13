/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/
// Original file Copyright Crytek GMBH or its affiliates, used under license.

#ifndef CRYINCLUDE_EDITOR_RENDERVIEWPORT_H
#define CRYINCLUDE_EDITOR_RENDERVIEWPORT_H

#pragma once
// RenderViewport.h : header file
//

#if !defined(Q_MOC_RUN)
#include <Cry_Camera.h>

#include <QSet>

#include "Viewport.h"
#include "Objects/DisplayContext.h"
#include "Undo/Undo.h"
#include "Util/PredefinedAspectRatios.h"

#include <AzCore/Component/EntityId.h>
#include <AzCore/std/optional.h>
#include <AzFramework/Input/Buses/Requests/InputSystemCursorRequestBus.h>
#include <AzToolsFramework/API/ToolsApplicationAPI.h>
#include <AzToolsFramework/API/EditorCameraBus.h>
#include <AzToolsFramework/Entity/EditorEntityContextBus.h>
#include <AzToolsFramework/Viewport/ViewportMessages.h>
#include <MathConversion.h>
#endif

#include <AzFramework/Windowing/WindowBus.h>
#include <AzFramework/Visibility/EntityVisibilityQuery.h>

// forward declarations.
class CBaseObject;
class QMenu;
class QKeyEvent;
class EditorEntityNotifications;
struct ray_hit;
struct IRenderMesh;
struct IVariable;

namespace AzToolsFramework
{
    class ManipulatorManager;
}

// CRenderViewport window
AZ_PUSH_DISABLE_DLL_EXPORT_BASECLASS_WARNING
AZ_PUSH_DISABLE_DLL_EXPORT_MEMBER_WARNING
class SANDBOX_API CRenderViewport
    : public QtViewport
    , public IEditorNotifyListener
    , public IUndoManagerListener
    , public Camera::EditorCameraRequestBus::Handler
    , public AzFramework::InputSystemCursorConstraintRequestBus::Handler
    , public AzToolsFramework::ViewportInteraction::ViewportFreezeRequestBus::Handler
    , public AzToolsFramework::ViewportInteraction::ViewportInteractionRequestBus::Handler
    , public AzToolsFramework::ViewportInteraction::MainEditorViewportInteractionRequestBus::Handler
    , public AzFramework::WindowRequestBus::Handler
{
AZ_POP_DISABLE_DLL_EXPORT_MEMBER_WARNING
AZ_POP_DISABLE_DLL_EXPORT_BASECLASS_WARNING
    Q_OBJECT
public:
    struct SResolution
    {
        SResolution()
            : width(0)
            , height(0)
        {
        }

        SResolution(int w, int h)
            : width(w)
            , height(h)
        {
        }

        int width;
        int height;
    };

public:
    CRenderViewport(const QString& name, QWidget* parent = nullptr);

    static const GUID& GetClassID()
    {
        return QtViewport::GetClassID<CRenderViewport>();
    }

    /** Get type of this viewport.
    */
    virtual EViewportType GetType() const { return ET_ViewportCamera; }
    virtual void SetType([[maybe_unused]] EViewportType type) { assert(type == ET_ViewportCamera); };

    // Implementation
public:
    virtual ~CRenderViewport();

    Q_INVOKABLE void InjectFakeMouseMove(int deltaX, int deltaY, Qt::MouseButtons buttons);

public:
    virtual void Update();

    virtual void ResetContent();
    virtual void UpdateContent(int flags);

    void OnTitleMenu(QMenu* menu) override;

    void SetCamera(const CCamera& camera);
    const CCamera& GetCamera() const { return m_Camera; };
    virtual void SetViewTM(const Matrix34& tm)
    {
        if (m_viewSourceType == ViewSourceType::None)
        {
            m_defaultViewTM = tm;
        }
        SetViewTM(tm, false);
    }

    //! Map world space position to viewport position.
    virtual QPoint WorldToView(const Vec3& wp) const;
    virtual QPoint WorldToViewParticleEditor(const Vec3& wp, int width, int height) const;
    virtual Vec3 WorldToView3D(const Vec3& wp, int nFlags = 0) const;

    //! Map viewport position to world space position.
    virtual Vec3 ViewToWorld(const QPoint& vp, bool* collideWithTerrain = nullptr, bool onlyTerrain = false, bool bSkipVegetation = false, bool bTestRenderMesh = false, bool* collideWithObject = nullptr) const override;
    virtual void ViewToWorldRay(const QPoint& vp, Vec3& raySrc, Vec3& rayDir) const override;
    virtual Vec3 ViewToWorldNormal(const QPoint& vp, bool onlyTerrain, bool bTestRenderMesh = false) override;
    virtual float GetScreenScaleFactor(const Vec3& worldPoint) const;
    virtual float GetScreenScaleFactor(const CCamera& camera, const Vec3& object_position);
    virtual float GetAspectRatio() const;
    virtual bool HitTest(const QPoint& point, HitContext& hitInfo);
    virtual bool IsBoundsVisible(const AABB& box) const;
    virtual void CenterOnSelection();
    virtual void CenterOnAABB(const AABB& aabb);
    void CenterOnSliceInstance() override;

    void focusOutEvent(QFocusEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

    void SetFOV(float fov);
    float GetFOV() const;

    void SetDefaultCamera();
    bool IsDefaultCamera() const;
    void SetSequenceCamera();
    bool IsSequenceCamera() const { return m_viewSourceType == ViewSourceType::SequenceCamera; }
    void SetSelectedCamera();
    bool IsSelectedCamera() const;
    void SetComponentCamera(const AZ::EntityId& entityId);
    void SetEntityAsCamera(const AZ::EntityId& entityId, bool lockCameraMovement = false);
    void SetFirstComponentCamera();
    void SetViewEntity(const AZ::EntityId& cameraEntityId, bool lockCameraMovement = false);
    void PostCameraSet();
    // This switches the active camera to the next one in the list of (default, all custom cams).
    void CycleCamera();

    // Camera::EditorCameraRequestBus
    void SetViewFromEntityPerspective(const AZ::EntityId& entityId) override;
    void SetViewAndMovementLockFromEntityPerspective(const AZ::EntityId& entityId, bool lockCameraMovement) override;
    AZ::EntityId GetCurrentViewEntityId() override { return m_viewEntityId; }
    bool GetActiveCameraPosition(AZ::Vector3& cameraPos) override;
    bool GetActiveCameraState(AzFramework::CameraState& cameraState) override;

    // AzToolsFramework::EditorEntityContextNotificationBus (handler moved to cpp to resolve link issues in unity builds)
    virtual void OnStartPlayInEditor();
    virtual void OnStopPlayInEditor();

    // AzToolsFramework::EditorEvents::Bus (handler moved to cpp to resolve link issues in unity builds)
    // We use this to determine when the viewport context menu is being displayed so we can exit move mode
    void PopulateEditorGlobalContextMenu(QMenu* /*menu*/, const AZ::Vector2& /*point*/, int /*flags*/);

    // AzToolsFramework::ViewportInteractionRequestBus
    AzFramework::CameraState GetCameraState() override;
    bool GridSnappingEnabled() override;
    float GridSize() override;
    bool ShowGrid() override;
    bool AngleSnappingEnabled() override;
    float AngleStep() override;
    QPoint ViewportWorldToScreen(const AZ::Vector3& worldPosition) override;
    AZStd::optional<AZ::Vector3> ViewportScreenToWorld(const QPoint&, float) override { return {}; }
    AZStd::optional<AzToolsFramework::ViewportInteraction::ProjectedViewportRay> ViewportScreenToWorldRay(const QPoint&) override { return {}; }

    // AzToolsFramework::ViewportFreezeRequestBus
    bool IsViewportInputFrozen() override;
    void FreezeViewportInput(bool freeze) override;

    // AzToolsFramework::MainEditorViewportInteractionRequestBus
    AZ::EntityId PickEntity(const QPoint& point) override;
    AZ::Vector3 PickTerrain(const QPoint& point) override;
    float TerrainHeight(const AZ::Vector2& position) override;
    void FindVisibleEntities(AZStd::vector<AZ::EntityId>& visibleEntitiesOut) override;
    bool ShowingWorldSpace() override;
    QWidget* GetWidgetForViewportContextMenu() override;
    void BeginWidgetContext() override;
    void EndWidgetContext() override;

    // WindowRequestBus::Handler...
    void SetWindowTitle(const AZStd::string& title) override;
    AzFramework::WindowSize GetClientAreaSize() const override;
    void ResizeClientArea(AzFramework::WindowSize) override;
    bool GetFullScreenState() const override;
    void SetFullScreenState(bool fullScreenState) override;
    bool CanToggleFullScreenState() const override;
    void ToggleFullScreenState() override;

    void ConnectViewportInteractionRequestBus();
    void DisconnectViewportInteractionRequestBus();

    void ActivateWindowAndSetFocus();

    void LockCameraMovement(bool bLock) { m_bLockCameraMovement = bLock; }
    bool IsCameraMovementLocked() const { return m_bLockCameraMovement; }

    void EnableCameraObjectMove(bool bMove) { m_bMoveCameraObject = bMove; }
    bool IsCameraObjectMove() const { return m_bMoveCameraObject; }

    void SetPlayerControl(uint32 i) { m_PlayerControl = i; };
    uint32 GetPlayerControl() { return m_PlayerControl; };

    const DisplayContext& GetDisplayContext() const { return m_displayContext; }
    CBaseObject* GetCameraObject() const;

    QPoint WidgetToViewport(const QPoint& point) const;
    QPoint ViewportToWidget(const QPoint& point) const;
    QSize WidgetToViewport(const QSize& size) const;

    /// Take raw input and create a final mouse interaction.
    /// @attention Do not map **point** from widget to viewport explicitly,
    /// this is handled internally by BuildMouseInteraction - just pass directly.
    AzToolsFramework::ViewportInteraction::MouseInteraction BuildMouseInteraction(
        Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers, const QPoint& point);

    void SetPlayerPos()
    {
        Matrix34 m = GetViewTM();
        m.SetTranslation(m.GetTranslation() - m_PhysicalLocation.t);
        SetViewTM(m);

        m_AverageFrameTime = 0.14f;

        m_PhysicalLocation.SetIdentity();

        m_LocalEntityMat.SetIdentity();
        m_PrevLocalEntityMat.SetIdentity();

        m_absCameraHigh = 2.0f;
        m_absCameraPos = Vec3(0, 3, 2);
        m_absCameraPosVP = Vec3(0, -3, 1.5);

        m_absCurrentSlope = 0.0f;

        m_absLookDirectionXY = Vec2(0, 1);

        m_LookAt = Vec3(ZERO);
        m_LookAtRate = Vec3(ZERO);
        m_vCamPos = Vec3(ZERO);
        m_vCamPosRate = Vec3(ZERO);

        m_relCameraRotX = 0;
        m_relCameraRotZ = 0;

        uint32 numSample6 = m_arrAnimatedCharacterPath.size();
        for (uint32 i = 0; i < numSample6; i++)
        {
            m_arrAnimatedCharacterPath[i] = Vec3(ZERO);
        }

        numSample6 = m_arrSmoothEntityPath.size();
        for (uint32 i = 0; i < numSample6; i++)
        {
            m_arrSmoothEntityPath[i] = Vec3(ZERO);
        }

        uint32 numSample7 = m_arrRunStrafeSmoothing.size();
        for (uint32 i = 0; i < numSample7; i++)
        {
            m_arrRunStrafeSmoothing[i] = 0;
        }

        m_vWorldDesiredBodyDirection = Vec2(0, 1);
        m_vWorldDesiredBodyDirectionSmooth = Vec2(0, 1);
        m_vWorldDesiredBodyDirectionSmoothRate = Vec2(0, 1);

        m_vWorldDesiredBodyDirection2 = Vec2(0, 1);

        m_vWorldDesiredMoveDirection = Vec2(0, 1);
        m_vWorldDesiredMoveDirectionSmooth = Vec2(0, 1);
        m_vWorldDesiredMoveDirectionSmoothRate = Vec2(0, 1);
        m_vLocalDesiredMoveDirection = Vec2(0, 1);
        m_vLocalDesiredMoveDirectionSmooth = Vec2(0, 1);
        m_vLocalDesiredMoveDirectionSmoothRate = Vec2(0, 1);

        m_vWorldAimBodyDirection = Vec2(0, 1);

        m_MoveSpeedMSec = 5.0f;
        m_key_W = 0;
        m_keyrcr_W = 0;
        m_key_S = 0;
        m_keyrcr_S = 0;
        m_key_A = 0;
        m_keyrcr_A = 0;
        m_key_D = 0;
        m_keyrcr_D = 0;
        m_key_SPACE = 0;
        m_keyrcr_SPACE = 0;
        m_ControllMode = 0;

        m_State = -1;
        m_Stance = 1; //combat

        m_udGround = 0.0f;
        m_lrGround = 0.0f;
        AABB aabb = AABB(Vec3(-40.0f, -40.0f, -0.25f), Vec3(+40.0f, +40.0f, +0.0f));
        m_GroundOBB = OBB::CreateOBBfromAABB(Matrix33(IDENTITY), aabb);
        m_GroundOBBPos = Vec3(0, 0, -0.01f);
    };

    static CRenderViewport* GetPrimaryViewport();

    AZ_PUSH_DISABLE_DLL_EXPORT_MEMBER_WARNING
    CCamera m_Camera;
    AZ_POP_DISABLE_DLL_EXPORT_MEMBER_WARNING

protected:
    struct SScopedCurrentContext;

    void SetViewTM(const Matrix34& tm, bool bMoveOnly);

    virtual float GetCameraMoveSpeed() const;
    virtual float GetCameraRotateSpeed() const;
    virtual bool  GetCameraInvertYRotation() const;
    virtual float GetCameraInvertPan() const;

    // Called to render stuff.
    virtual void OnRender();

    virtual void OnEditorNotifyEvent(EEditorNotifyEvent event);

    //! Get currently active camera object.
    void ToggleCameraObject();

    void RenderConstructionPlane();
    void RenderSnapMarker();
    void RenderCursorString();
    void RenderSnappingGrid();
    void ProcessMouse();
    void ProcessKeys();

    void RenderAll();
    void DrawAxis();
    void DrawBackground();
    void InitDisplayContext();
    void ResetCursor();

    struct SPreviousContext
    {
        CCamera rendererCamera;
        HWND window;
        int width;
        int height;
        bool mainViewport;
    };

    SPreviousContext m_preWidgetContext;

    // Create an auto-sized render context that is sized based on the Editor's current
    // viewport.
    SPreviousContext SetCurrentContext() const;

    SPreviousContext SetCurrentContext(int newWidth, int newHeight) const;
    void RestorePreviousContext(const SPreviousContext& x) const;

    void PreWidgetRendering() override;
    void PostWidgetRendering() override;

    // Update the safe frame, safe action, safe title, and borders rectangles based on
    // viewport size and target aspect ratio.
    void UpdateSafeFrame();

    // Draw safe frame, safe action, safe title rectangles and borders.
    void RenderSafeFrame();

    // Draw one of the safe frame rectangles with the desired color.
    void RenderSafeFrame(const QRect& frame, float r, float g, float b, float a);

    // Draw the selection rectangle.
    void RenderSelectionRectangle();

    // Draw a selected region if it has been selected
    void RenderSelectedRegion();

    virtual bool CreateRenderContext();
    virtual void DestroyRenderContext();

    void OnMenuCommandChangeAspectRatio(unsigned int commandId);

    bool AdjustObjectPosition(const ray_hit& hit, Vec3& outNormal, Vec3& outPos) const;
    bool RayRenderMeshIntersection(IRenderMesh* pRenderMesh, const Vec3& vInPos, const Vec3& vInDir, Vec3& vOutPos, Vec3& vOutNormal) const;

    bool AddCameraMenuItems(QMenu* menu);
    void ResizeView(int width, int height);

    void OnCameraFOVVariableChanged(IVariable* var);

    void HideCursor();
    void ShowCursor();

    bool IsKeyDown(Qt::Key key) const;

    enum class ViewSourceType
    {
        None,
        SequenceCamera,
        LegacyCamera,
        CameraComponent,
        AZ_Entity,
        ViewSourceTypesCount,
    };
    void ResetToViewSourceType(const ViewSourceType& viewSourType);

    //! Assigned renderer.
    IRenderer*  m_renderer = nullptr;
    I3DEngine*  m_engine = nullptr;
    bool m_bRenderContextCreated = false;
    bool m_bInRotateMode = false;
    bool m_bInMoveMode = false;
    bool m_bInOrbitMode = false;
    bool m_bInZoomMode = false;

    QPoint m_mousePos = QPoint(0, 0);
    QPoint m_prevMousePos = QPoint(0, 0);  // for tablets, you can't use SetCursorPos and need to remember the prior point and delta with that.


    float m_moveSpeed = 1;

    float m_orbitDistance = 10.0f;
    AZ_PUSH_DISABLE_DLL_EXPORT_MEMBER_WARNING
    Vec3 m_orbitTarget;

    //-------------------------------------------
    //---   player-control in CharEdit        ---
    //-------------------------------------------
    f32 m_MoveSpeedMSec;

    uint32 m_key_W, m_keyrcr_W;
    uint32 m_key_S, m_keyrcr_S;
    uint32 m_key_A, m_keyrcr_A;
    uint32 m_key_D, m_keyrcr_D;

    uint32 m_key_SPACE, m_keyrcr_SPACE;
    uint32 m_ControllMode;

    int32 m_Stance;
    int32 m_State;
    f32 m_AverageFrameTime;

    uint32 m_PlayerControl = 0;

    f32 m_absCameraHigh;
    Vec3 m_absCameraPos;
    Vec3 m_absCameraPosVP;

    f32  m_absCurrentSlope;  //in radiants

    Vec2 m_absLookDirectionXY;

    Vec3 m_LookAt;
    Vec3 m_LookAtRate;
    Vec3 m_vCamPos;
    Vec3 m_vCamPosRate;
    float m_camFOV;

    f32 m_relCameraRotX;
    f32 m_relCameraRotZ;

    QuatTS m_PhysicalLocation;

    Matrix34 m_AnimatedCharacterMat;

    Matrix34 m_LocalEntityMat;  //this is used for data-driven animations where the character is running on the spot
    Matrix34 m_PrevLocalEntityMat;

    std::vector<Vec3> m_arrVerticesHF;
    std::vector<vtx_idx> m_arrIndicesHF;

    std::vector<Vec3> m_arrAnimatedCharacterPath;
    std::vector<Vec3> m_arrSmoothEntityPath;
    std::vector<f32> m_arrRunStrafeSmoothing;

    Vec2 m_vWorldDesiredBodyDirection;
    Vec2 m_vWorldDesiredBodyDirectionSmooth;
    Vec2 m_vWorldDesiredBodyDirectionSmoothRate;

    Vec2 m_vWorldDesiredBodyDirection2;


    Vec2 m_vWorldDesiredMoveDirection;
    Vec2 m_vWorldDesiredMoveDirectionSmooth;
    Vec2 m_vWorldDesiredMoveDirectionSmoothRate;
    Vec2 m_vLocalDesiredMoveDirection;
    Vec2 m_vLocalDesiredMoveDirectionSmooth;
    Vec2 m_vLocalDesiredMoveDirectionSmoothRate;
    Vec2 m_vWorldAimBodyDirection;

    f32 m_udGround;
    f32 m_lrGround;
    OBB m_GroundOBB;
    Vec3 m_GroundOBBPos;

    //-------------------------------------------
    // Render options.
    bool m_bRenderStats = true;

    // Index of camera objects.
    mutable GUID m_cameraObjectId = GUID_NULL;
    mutable AZ::EntityId m_viewEntityId;
    mutable ViewSourceType m_viewSourceType = ViewSourceType::None;
    AZ::EntityId m_viewEntityIdCachedForEditMode;
    Matrix34 m_preGameModeViewTM;
    uint m_disableRenderingCount = 0;
    bool m_bLockCameraMovement;
    bool m_bUpdateViewport = false;
    bool m_bMoveCameraObject = true;

    enum class KeyPressedState
    {
        AllUp,
        PressedThisFrame,
        PressedInPreviousFrame,
    };
    KeyPressedState m_pressedKeyState = KeyPressedState::AllUp;

    Matrix34 m_defaultViewTM;
    const QString m_defaultViewName;

    DisplayContext m_displayContext;


    bool m_isOnPaint = false;
    static CRenderViewport* m_pPrimaryViewport;

    QRect m_safeFrame;
    QRect m_safeAction;
    QRect m_safeTitle;

    CPredefinedAspectRatios m_predefinedAspectRatios;

    IVariable* m_pCameraFOVVariable = nullptr;
    bool m_bCursorHidden = false;

    void OnMenuResolutionCustom();
    void OnMenuCreateCameraEntityFromCurrentView();
    void OnMenuSelectCurrentCamera();

    int OnCreate();
    void resizeEvent(QResizeEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void OnLButtonDown(Qt::KeyboardModifiers modifiers, const QPoint& point) override;
    void OnLButtonUp(Qt::KeyboardModifiers modifiers, const QPoint& point) override;
    void OnLButtonDblClk(Qt::KeyboardModifiers modifiers, const QPoint& point) override;
    void OnMButtonDown(Qt::KeyboardModifiers modifiers, const QPoint& point) override;
    void OnMButtonUp(Qt::KeyboardModifiers modifiers, const QPoint& point) override;
    void OnRButtonDown(Qt::KeyboardModifiers modifiers, const QPoint& point) override;
    void OnRButtonUp(Qt::KeyboardModifiers modifiers, const QPoint& point) override;
    void OnMouseMove(Qt::KeyboardModifiers modifiers, Qt::MouseButtons buttons, const QPoint& point) override;
    void OnMouseWheel(Qt::KeyboardModifiers modifiers, short zDelta, const QPoint& pt) override;

    // From a series of input primitives, compose a complete mouse interaction.
    AzToolsFramework::ViewportInteraction::MouseInteraction BuildMouseInteractionInternal(
        AzToolsFramework::ViewportInteraction::MouseButtons buttons,
        AzToolsFramework::ViewportInteraction::KeyboardModifiers modifiers,
        const AzToolsFramework::ViewportInteraction::MousePick& mousePick) const;
    // Given a point in the viewport, return the pick ray into the scene.
    // note: The argument passed to parameter **point**, originating
    // from a Qt event, must first be passed to WidgetToViewport before being
    // passed to BuildMousePick.
    AzToolsFramework::ViewportInteraction::MousePick BuildMousePick(const QPoint& point);

    bool event(QEvent* event) override;
    void OnDestroy();

    bool CheckRespondToInput() const;

    // AzFramework::InputSystemCursorConstraintRequestBus
    void* GetSystemCursorConstraintWindow() const override;

    void BuildDragDropContext(AzQtComponents::ViewportDragContext& context, const QPoint& pt) override;

private:
    void ProcessKeyRelease(QKeyEvent* event);
    void PushDisableRendering();
    void PopDisableRendering();
    bool IsRenderingDisabled() const;
    AzToolsFramework::ViewportInteraction::MousePick BuildMousePickInternal(
        const QPoint& point) const;

    void RestoreViewportAfterGameMode();

    double WidgetToViewportFactor() const
    {
#if defined(AZ_PLATFORM_WINDOWS)
        // Needed for high DPI mode on windows
        return devicePixelRatioF();
#else
        return 1.0f;
#endif
    }

    void BeginUndoTransaction() override;
    void EndUndoTransaction() override;

    void UpdateCurrentMousePos(const QPoint& newPosition);

    AzFramework::EntityVisibilityQuery m_entityVisibilityQuery;

    SPreviousContext m_previousContext;
    QSet<int> m_keyDown;

    bool m_freezeViewportInput = false;

    size_t m_cameraSetForWidgetRenderingCount = 0; ///< How many calls to PreWidgetRendering happened before
                                                   ///< subsequent calls to PostWidetRendering.
    AZStd::shared_ptr<AzToolsFramework::ManipulatorManager> m_manipulatorManager;

    // Used to prevent circular set camera events
    bool m_ignoreSetViewFromEntityPerspective = false;
    bool m_windowResizedEvent = false;

    // Cache hwnd value for teardown to avoid infinite loops in retrieving it from destroyed widgets.
    HWND m_hwnd;

    AZStd::unique_ptr<EditorEntityNotifications> m_editorEntityNotifications;

    AZ_POP_DISABLE_DLL_EXPORT_MEMBER_WARNING
};

#endif // CRYINCLUDE_EDITOR_RENDERVIEWPORT_H
