/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/std/string/string.h>

namespace AzFramework
{
    namespace Platform
    {
        AZStd::string GetPersistentName()
        {
            return { "Lumberyard" };
        }

        AZStd::string GetNeighborhoodName()
        {
            return {};
        }
    }
}
