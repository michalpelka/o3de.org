/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <ScriptCanvas/Internal/Nodes/BaseTimerNode.h>

#include <Include/ScriptCanvas/Libraries/Time/HeartBeat.generated.h>

namespace ScriptCanvas
{
    namespace Nodes
    {
        namespace Time
        {
            //! Deprecated: see HeartBeatNodeableNode
            class HeartBeat
                : public ScriptCanvas::Nodes::Internal::BaseTimerNode
            {
            public:

                SCRIPTCANVAS_NODE(HeartBeat);

                void CustomizeReplacementNode(Node* replacementNode, AZStd::unordered_map<SlotId, AZStd::vector<SlotId>>& outSlotIdMap) const override;

                void OnInputSignal(const SlotId&) override;

                const char* GetBaseTimeSlotName() const override { return "Interval"; }
                const char* GetBaseTimeSlotToolTip() const override { return "The amount of time between pulses."; }

            protected:

                void OnTimeElapsed() override;

             };
        }
    }
}
