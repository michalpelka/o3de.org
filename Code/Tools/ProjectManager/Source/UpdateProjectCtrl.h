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
#pragma once

#if !defined(Q_MOC_RUN)
#include <ProjectInfo.h>
#include <ScreenWidget.h>
#endif

QT_FORWARD_DECLARE_CLASS(QStackedWidget)
QT_FORWARD_DECLARE_CLASS(QTabWidget)
QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QFrame)

namespace O3DE::ProjectManager
{
    QT_FORWARD_DECLARE_CLASS(ScreenHeader)
    QT_FORWARD_DECLARE_CLASS(UpdateProjectSettingsScreen)
    QT_FORWARD_DECLARE_CLASS(GemCatalogScreen)

    class UpdateProjectCtrl : public ScreenWidget
    {
    public:
        explicit UpdateProjectCtrl(QWidget* parent = nullptr);
        ~UpdateProjectCtrl() = default;
        ProjectManagerScreen GetScreenEnum() override;

    protected:
        void NotifyCurrentScreen() override;

    protected slots:
        void HandleBackButton();
        void HandleNextButton();
        void HandleGemsButton();
        void UpdateCurrentProject(const QString& projectPath);

    private:
        void Update();
        void UpdateSettingsScreen();
        bool UpdateProjectSettings(bool shouldConfirm = false);

        enum ScreenOrder
        {
            Settings,
            Gems
        };

        ScreenHeader* m_header = nullptr;
        QStackedWidget* m_stack = nullptr;
        UpdateProjectSettingsScreen* m_updateSettingsScreen = nullptr;
        GemCatalogScreen* m_gemCatalogScreen = nullptr;

        QPushButton* m_backButton = nullptr;
        QPushButton* m_nextButton = nullptr;
        QVector<ProjectManagerScreen> m_screensOrder;

        ProjectInfo m_projectInfo;
    };

} // namespace O3DE::ProjectManager
