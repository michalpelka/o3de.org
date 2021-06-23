/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/RTTI/TypeInfo.h>
#include <AzCore/std/smart_ptr/intrusive_ptr.h>

namespace AZ
{
    class ReflectContext;
}

namespace ScriptCanvas
{
    class BehaviorContextObject;
    using BehaviorContextObjectPtr = AZStd::intrusive_ptr<BehaviorContextObject>;
    void BehaviorContextObjectPtrReflect(AZ::ReflectContext* context);
} 
