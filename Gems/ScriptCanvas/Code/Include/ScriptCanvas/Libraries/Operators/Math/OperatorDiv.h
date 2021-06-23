/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include "OperatorArithmetic.h"
#include <Include/ScriptCanvas/Libraries/Operators/Math/OperatorDiv.generated.h>

namespace ScriptCanvas
{
    namespace Nodes
    {
        namespace Operators
        {
            //! Node that provides division
            class OperatorDiv : public OperatorArithmetic
            {
            public:

                SCRIPTCANVAS_NODE(OperatorDiv);

                OperatorDiv() = default;
                ~OperatorDiv() = default;

                AZStd::string_view OperatorFunction() const override { return "Divide"; }
                AZStd::unordered_set< Data::Type > GetSupportedNativeDataTypes() const override;

                void Operator(Data::eType type, const ArithmeticOperands& operands, Datum& result) override;

            protected:

                void InitializeSlot(const SlotId& slotId, const ScriptCanvas::Data::Type& dataType) override;                
                bool IsValidArithmeticSlot(const SlotId& slotId) const override;

                void OnResetDatumToDefaultValue(ModifiableDatumView& datumView) override;
            };
        }
    }
}
