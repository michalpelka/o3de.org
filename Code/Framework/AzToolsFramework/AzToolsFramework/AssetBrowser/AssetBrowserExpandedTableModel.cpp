/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#include <AssetBrowser/AssetBrowserFilterModel.h>
#include <AssetBrowser/AssetBrowserExpandedTableModel.h>
#include <AzToolsFramework/AssetBrowser/Entries/AssetBrowserEntry.h>

namespace AzToolsFramework
{
    namespace AssetBrowser
    {
        AssetBrowserExpandedTableModel::AssetBrowserExpandedTableModel(QObject* parent /* = nullptr */)
            : QSortFilterProxyModel(parent)
        {
        }

        void AssetBrowserExpandedTableModel::setSourceModel(QAbstractItemModel* sourceModel)
        {
            m_filterModel = qobject_cast<AssetBrowserFilterModel*>(sourceModel);
            AZ_Assert(
                m_filterModel,
                "Error in AssetBrowserTableModel initialization, class expects source model to be an AssetBrowserFilterModel.");

            QSortFilterProxyModel::setSourceModel(sourceModel);

            connect(m_filterModel, &QAbstractItemModel::rowsInserted, this, &AssetBrowserExpandedTableModel::StartUpdateModelMapTimer);
            connect(m_filterModel, &QAbstractItemModel::rowsRemoved, this, &AssetBrowserExpandedTableModel::StartUpdateModelMapTimer);
            connect(m_filterModel, &QAbstractItemModel::layoutChanged, this, &AssetBrowserExpandedTableModel::StartUpdateModelMapTimer);
            connect(m_filterModel, &AssetBrowserFilterModel::filterChanged, this, &AssetBrowserExpandedTableModel::UpdateTableModelMaps);
            connect(m_filterModel, &QAbstractItemModel::dataChanged, this, &AssetBrowserExpandedTableModel::SourceDataChanged);
        }

        QModelIndex AssetBrowserExpandedTableModel::mapToSource(const QModelIndex& proxyIndex) const
        {
            Q_ASSERT(!proxyIndex.isValid() || proxyIndex.model() == this);
            if (!proxyIndex.isValid() || !m_indexMap.contains(proxyIndex.row()))
            {
                return QModelIndex();
            }
            return m_indexMap[proxyIndex.row()];
        }

        QModelIndex AssetBrowserExpandedTableModel::mapFromSource(const QModelIndex& sourceIndex) const
        {
            Q_ASSERT(!sourceIndex.isValid() || sourceIndex.model() == sourceModel());
            if (!sourceIndex.isValid() || !m_rowMap.contains(sourceIndex))
            {
                return QModelIndex();
            }

            return createIndex(m_rowMap[sourceIndex], sourceIndex.column());
        }

        bool AssetBrowserExpandedTableModel::filterAcceptsRow(int source_row, [[maybe_unused]] const QModelIndex& source_parent) const
        {
            return m_indexMap.contains(source_row);
        }

        QVariant AssetBrowserExpandedTableModel::headerData(int section, Qt::Orientation orientation, int role) const
        {
            if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
            {
                return tr(AssetBrowserEntry::m_columnNames[section]);
            }
            return QSortFilterProxyModel::headerData(section, orientation, role);
        }

        QVariant AssetBrowserExpandedTableModel::data(const QModelIndex& index, int role) const
        {
            Q_ASSERT(index.isValid() && index.model() == this);
            return sourceModel()->data(mapToSource(index), role);
        }

        QModelIndex AssetBrowserExpandedTableModel::parent([[maybe_unused]] const QModelIndex& child) const
        {
            return QModelIndex();
        }

        QModelIndex AssetBrowserExpandedTableModel::sibling(
            [[maybe_unused]] int row, [[maybe_unused]] int column, [[maybe_unused]] const QModelIndex& idx) const
        {
            return QModelIndex();
        }

        void AssetBrowserExpandedTableModel::SourceDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight)
        {
            for (int row = topLeft.row(); row <= bottomRight.row(); ++row)
            {
                if (!m_indexMap.contains(row))
                {
                    UpdateTableModelMaps();
                    return;
                }
            }
        }

        QModelIndex AssetBrowserExpandedTableModel::index(int row, int column, const QModelIndex& parent) const
        {
            Q_ASSERT(!parent.isValid());

            return parent.isValid() ? QModelIndex() : createIndex(row, column, m_indexMap[row].internalPointer());
        }

        int AssetBrowserExpandedTableModel::rowCount(const QModelIndex& parent) const
        {
            return !parent.isValid() ? m_indexMap.size() : 0;
        }

        void AssetBrowserExpandedTableModel::timerEvent([[maybe_unused]] QTimerEvent* event)
        {
            killTimer(m_updateModelMapTimerId);
            m_updateModelMapTimerId = 0;
            UpdateTableModelMaps();
        }

        void AssetBrowserExpandedTableModel::StartUpdateModelMapTimer()
        {
            constexpr int ModelRefreshWaitTimeMS = 250;
            if (m_updateModelMapTimerId > 0)
            {
                killTimer(m_updateModelMapTimerId);
            }
            m_updateModelMapTimerId = startTimer(ModelRefreshWaitTimeMS);
        }

        int AssetBrowserExpandedTableModel::BuildTableModelMap(
            const QAbstractItemModel* model, const QModelIndex& parent /*= QModelIndex()*/, int row /*= 0*/)
        {
            int rows = model ? model->rowCount(parent) : 0;

            if (parent == QModelIndex())
            {
                m_displayedItemsCounter = 0;
            }

            for (int currentRow = 0; currentRow < rows; ++currentRow)
            {
                if (m_displayedItemsCounter < m_numberOfItemsDisplayed)
                {
                    QModelIndex index = model->index(currentRow, 0, parent);
                    AssetBrowserEntry* entry = GetAssetEntry(m_filterModel->mapToSource(index));
                    // We only want to see source and product assets.
                    if (entry->GetEntryType() == AssetBrowserEntry::AssetEntryType::Source ||
                        entry->GetEntryType() == AssetBrowserEntry::AssetEntryType::Product)
                    {
                        m_indexMap[row] = index;
                        m_rowMap[index] = row;
                        ++row;

                        // We only want to increase the displayed counter if it is a parent (Source)
                        // so we don't cut children entries.
                        if (entry->GetEntryType() == AssetBrowserEntry::AssetEntryType::Source)
                        {
                            ++m_displayedItemsCounter;
                        }
                    }

                    if (model->hasChildren(index))
                    {
                        row = BuildTableModelMap(model, index, row);
                    }
                }
                else
                {
                    break;
                }
            }
            return row;
        }

        AssetBrowserEntry* AssetBrowserExpandedTableModel::GetAssetEntry(QModelIndex index) const
        {
            if (!index.isValid())
            {
                AZ_Error("AssetBrowser", false, "Invalid Source Index provided to GetAssetEntry.");
                return nullptr;
            }
            return static_cast<AssetBrowserEntry*>(index.internalPointer());
        }

        void AssetBrowserExpandedTableModel::UpdateTableModelMaps()
        {
            beginResetModel();
            emit layoutAboutToBeChanged();

            if (!m_indexMap.isEmpty() || !m_rowMap.isEmpty())
            {
                m_indexMap.clear();
                m_rowMap.clear();
            }
            AzToolsFramework::EditorSettingsAPIBus::BroadcastResult(
                m_numberOfItemsDisplayed, &AzToolsFramework::EditorSettingsAPIBus::Handler::GetMaxNumberOfItemsShownInSearchView);
            BuildTableModelMap(sourceModel());
            emit layoutChanged();
            endResetModel();
        }
    } // namespace AssetBrowser
} // namespace AzToolsFramework
#include "AssetBrowser/moc_AssetBrowserExpandedTableModel.cpp"
