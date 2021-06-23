/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Debug/TraceMessageBus.h>

namespace SceneBuilder
{
    class TraceMessageHook
        : public AZ::Debug::TraceMessageBus::Handler
    {
    public:
        TraceMessageHook();
        ~TraceMessageHook() override;

        bool OnPrintf(const char* window, const char* message) override;
    };
} // namespace SceneBuilder
