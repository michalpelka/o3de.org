/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/EBus/EBus.h>

namespace AzToolsFramework
{
    namespace Prefab
    {
        class PrefabPublicNotifications
            : public AZ::EBusTraits
        {
        public:
            virtual ~PrefabPublicNotifications() = default;

            virtual void OnPrefabInstancePropagationBegin() {}
            virtual void OnPrefabInstancePropagationEnd() {}
        };

        using PrefabPublicNotificationBus = AZ::EBus<PrefabPublicNotifications>;

    } // namespace Prefab
} // namespace AzToolsFramework
