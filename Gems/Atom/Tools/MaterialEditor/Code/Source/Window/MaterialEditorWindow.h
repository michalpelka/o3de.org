/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#if !defined(Q_MOC_RUN)
#include <AtomToolsFramework/Document/AtomToolsDocumentMainWindow.h>

AZ_PUSH_DISABLE_WARNING(4251 4800, "-Wunknown-warning-option") // disable warnings spawned by QT
#include <Viewport/MaterialViewportWidget.h>
#include <Window/ToolBar/MaterialEditorToolBar.h>
#include <QTimer>
AZ_POP_DISABLE_WARNING
#endif

namespace MaterialEditor
{
    //! MaterialEditorWindow is the main class. Its responsibility is limited to initializing and connecting
    //! its panels, managing selection of assets, and performing high-level actions like saving. It contains...
    //! 2) MaterialViewport        - The user can see the selected Material applied to a model.
    //! 3) MaterialPropertyInspector  - The user edits the properties of the selected Material.
    class MaterialEditorWindow
        : public AtomToolsFramework::AtomToolsDocumentMainWindow
    {
        Q_OBJECT
    public:
        AZ_CLASS_ALLOCATOR(MaterialEditorWindow, AZ::SystemAllocator, 0);

        using Base = AtomToolsFramework::AtomToolsDocumentMainWindow;

        MaterialEditorWindow(QWidget* parent = 0);
        ~MaterialEditorWindow();

    protected:
        void ResizeViewportRenderTarget(uint32_t width, uint32_t height) override;
        void LockViewportRenderTargetSize(uint32_t width, uint32_t height) override;
        void UnlockViewportRenderTargetSize() override;

        bool GetCreateDocumentParams(AZStd::string& openPath, AZStd::string& savePath) override;
        bool GetOpenDocumentParams(AZStd::string& openPath) override;
        void OpenSettings() override;
        void OpenHelp() override;
        void OpenAbout() override;

        void closeEvent(QCloseEvent* closeEvent) override;

        void SetupMetrics();
        void UpdateMetrics();

        MaterialViewportWidget* m_materialViewport = {};
        MaterialEditorToolBar* m_toolBar = {};
        QLabel* m_statusBarFps = {};
        QLabel* m_statusBarCpuTime = {};
        QLabel* m_statusBarGpuTime = {};
        QTimer m_metricsTimer;
    };
} // namespace MaterialEditor
