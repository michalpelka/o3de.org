/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#if !defined(Q_MOC_RUN)
#include <GemCatalog/GemSortFilterProxyModel.h>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QFrame>
#endif

namespace O3DE::ProjectManager
{
    class GemListHeaderWidget
        : public QFrame
    {
        Q_OBJECT // AUTOMOC

    public:
        explicit GemListHeaderWidget(GemSortFilterProxyModel* proxyModel, QWidget* parent = nullptr);
        ~GemListHeaderWidget() = default;
    };
} // namespace O3DE::ProjectManager
