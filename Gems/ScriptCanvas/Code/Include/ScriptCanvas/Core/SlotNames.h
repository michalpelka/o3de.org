/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/std/string/string_view.h>

namespace ScriptCanvas
{
    AZ_INLINE AZStd::string_view GetInputSlotName() { return "In"; }
    AZ_INLINE AZStd::string_view GetOutputSlotName() { return "Out"; }

    AZ_INLINE AZStd::string_view GetSourceSlotName() { return "Source"; }
}
