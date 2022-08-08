/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Memory/SystemAllocator.h>
#include <AzCore/RTTI/ReflectContext.h>
#include <AzCore/RTTI/RTTI.h>
#include <AzCore/std/containers/map.h>
#include <AzCore/std/containers/unordered_map.h>
#include <AzCore/std/string/string.h>

class QMenuBar;
class QWidget;

namespace AzToolsFramework
{
    class MenuManagerInterface;
    class MenuManagerInternalInterface;

    class EditorMenuBar final
    {
    public:
        AZ_CLASS_ALLOCATOR(EditorMenuBar, AZ::SystemAllocator, 0);
        AZ_RTTI(EditorMenuBar, "{6242037D-9BC5-41A1-91BE-441B33875DC6}");

        EditorMenuBar();

        static void Initialize(QWidget* defaultParentWidget);
        static void Reflect(AZ::ReflectContext* context);

        void AddMenu(int sortKey, AZStd::string menuIdentifier);
        
        // Returns whether the menu queried is contained in this menu.
        bool ContainsMenu(const AZStd::string& menuIdentifier) const;

        // Returns the sort key for the queried menu, or 0 if it's not found.
        AZStd::optional<int> GetMenuSortKey(const AZStd::string& menuIdentifier) const;
        
        // Returns the pointer to the menu bar.
        QMenuBar* GetMenuBar();
        const QMenuBar* GetMenuBar() const;
        
        // Clears the menu bar and creates a new one from the EditorMenuBar information.
        void RefreshMenuBar();

    private:
        QMenuBar* m_menuBar = nullptr;
        AZStd::map<int, AZStd::vector<AZStd::string>> m_menus;
        AZStd::unordered_map<AZStd::string, int> m_menuToSortKeyMap;
        
        inline static QWidget* m_defaultParentWidget = nullptr;

        inline static MenuManagerInterface* m_menuManagerInterface = nullptr;
        inline static MenuManagerInternalInterface* m_menuManagerInternalInterface = nullptr;
    };

} // namespace AzToolsFramework
