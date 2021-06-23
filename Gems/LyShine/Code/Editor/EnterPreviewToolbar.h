/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#if !defined(Q_MOC_RUN)
#include <QToolBar>
#endif

class EditorWindow;
class QPushButton;

class EnterPreviewToolbar
    : public QToolBar
{
    Q_OBJECT

public:

    explicit EnterPreviewToolbar(EditorWindow* parent);

private:

    QPushButton* m_previewButton;
};
