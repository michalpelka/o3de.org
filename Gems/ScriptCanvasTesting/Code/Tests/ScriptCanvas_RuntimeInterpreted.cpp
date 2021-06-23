/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/EBus/EBus.h>
#include <AzCore/Math/MathReflection.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/Serialization/SerializeContext.h>
#include <ScriptCanvas/Core/EBusHandler.h>
#include <ScriptCanvas/Core/SubgraphInterfaceUtility.h>
#include <ScriptCanvas/Core/Nodeable.h>
#include <ScriptCanvas/Execution/Interpreted/ExecutionInterpretedAPI.h>
#include <ScriptCanvas/Execution/NodeableOut/NodeableOutNative.h>
#include <ScriptCanvas/Grammar/GrammarContext.h>
#include <ScriptCanvas/Grammar/GrammarContextBus.h>
#include <Source/Framework/ScriptCanvasTestFixture.h>
#include <Source/Framework/ScriptCanvasTestNodes.h>
#include <Source/Framework/ScriptCanvasTestUtilities.h>
#include <Source/ScriptCanvasTestBus.h>

using namespace ScriptCanvas;
using namespace ScriptCanvasTests;
using namespace TestNodes;
using namespace ScriptCanvas::Execution;
using namespace ScriptCanvasEditor;

class GlobalHandler : ScriptCanvasTesting::GlobalEBus::Handler
{
public:
    AZ_CLASS_ALLOCATOR(GlobalHandler, AZ::SystemAllocator, 0);

    AZ::Event<> m_zeroParam;
    AZ::Event<AZStd::vector<AZStd::string>&> m_byReference;
    AZ::Event<int, bool, AZStd::string> m_byValue;

    GlobalHandler()
    {
        ScriptCanvasTesting::GlobalEBus::Handler::BusConnect();
    }

    AZStd::string AppendSweet(AZStd::string_view) override
    {
        AZStd::string result{};
        return result;
    }

    int Increment(int ) override
    {
        int result{};
        return result;
    }

    bool Not(bool ) override
    {
        bool result{};
        return result;
    }

    int Sum(int, int ) override
    {
        int result(0);
        return result;
    }

    void Void(AZStd::string_view) override
    {
    }

    AZ::Event<>* GetZeroParamEvent() override
    {
        return &m_zeroParam;
    }

    AZ::Event<AZStd::vector<AZStd::string>&>* GetByReferenceEvent() override
    {
        return &m_byReference;
    }

    AZ::Event<int, bool, AZStd::string>* GetByValueEvent() override
    {
        return &m_byValue;
    }
};

TEST_F(ScriptCanvasTestFixture, UseBehaviorContextClassConstant)
{
    RunUnitTestGraph("LY_SC_UnitTest_UseBehaviorContextClassConstant");
}

TEST_F(ScriptCanvasTestFixture, ParseFunctionIfBranchWithConnectedInput)
{
    RunUnitTestGraph("LY_SC_UnitTest_ParseFunctionIfBranchWithConnectedInput");
}

TEST_F(ScriptCanvasTestFixture, UseRawBehaviorProperties)
{
    RunUnitTestGraph("LY_SC_UnitTest_UseRawBehaviorProperties");
}

TEST_F(ScriptCanvasTestFixture, StringSanitization)
{
    RunUnitTestGraph("LY_SC_UnitTest_StringSanitization");
}

TEST_F(ScriptCanvasTestFixture, InterpretedHelloWorld)
{
    RunUnitTestGraph("LY_SC_UnitTest_HelloWorld");
}

TEST_F(ScriptCanvasTestFixture, InterpretedReadEnumConstant)
{
    RunUnitTestGraph("LY_SC_UnitTest_ReadEnumConstant");
}

TEST_F(ScriptCanvasTestFixture, UserBranchSanityCheck)
{
    RunUnitTestGraph("LY_SC_UnitTest_UserBranchSanityCheck");
}

TEST_F(ScriptCanvasTestFixture, InterpretedEventHandlerNoDisconnect)
{
    GlobalHandler handler;
    ScriptCanvasEditor::RunSpec runSpec;
    runSpec.m_onPostSimulate = [&handler]()
    {
        AZStd::vector<AZStd::string> reference{ "one", "two", "three" };
        handler.m_byReference.Signal(reference);
        handler.m_byValue.Signal(7, true, "CCC");
        handler.m_zeroParam.Signal();
    };

    RunUnitTestGraph("LY_SC_UnitTest_EventHandlerNoDisconnect", runSpec);
}

TEST_F(ScriptCanvasTestFixture, InterpretedEventHandlerDisconnect)
{
    GlobalHandler handler;
    ScriptCanvasEditor::RunSpec runSpec;
    runSpec.m_onPostSimulate = [&handler]()
    {
        AZStd::vector<AZStd::string> reference{ "one", "two", "three" };
        handler.m_byReference.Signal(reference);
        handler.m_byValue.Signal(7, true, "CCC");
        handler.m_zeroParam.Signal();
    };

    RunUnitTestGraph("LY_SC_UnitTest_EventHandlerDisconnect", runSpec);
}

TEST_F(ScriptCanvasTestFixture, FunctionLocalStaticsUnique)
{
    RunUnitTestGraph("LY_SC_UnitTest_FunctionLocalStaticsUnique");
}

TEST_F(ScriptCanvasTestFixture, FunctionContainerInputTest)
{
    RunUnitTestGraph("LY_SC_UnitTest_FunctionContainerInputTest");
}

TEST_F(ScriptCanvasTestFixture, InterpretedFixBoundMultipleResults)
{
    RunUnitTestGraph("LY_SC_UnitTest_FixBoundMultipleResults");
}

TEST_F(ScriptCanvasTestFixture, InterpretedDetectSelfDeactivation)
{
    ExpectParseError("LY_SC_UnitTest_DetectSelfDeactivation");
}

TEST_F(ScriptCanvasTestFixture, InterpretedDetectSelfDeactivationSequence)
{
    ExpectParseError("LY_SC_UnitTest_DetectSelfDeactivationSequence");
}

TEST_F(ScriptCanvasTestFixture, InterpretedEraseFrontUntilEmpty)
{
    RunUnitTestGraph("LY_SC_UnitTest_EraseFrontUntilEmpty");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllAABBNodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllAABBNodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllCRC32Nodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllCRC32Nodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllColorNodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllColorNodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllMatrix3x3Nodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllMatrix3x3Nodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllMatrix4x4Nodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllMatrix4x4Nodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllNumberNodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllNumberNodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllOBBNodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllOBBNodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllPlaneNodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllPlaneNodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllQuaternionNodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllQuaternionNodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllRandomNodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllRandomNodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllTransformNodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllTransformNodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllTrigonometryNodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllTrigonometryNodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllVector2Nodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllVector2Nodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllVector3Nodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllVector3Nodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathRunAllVector4Nodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_RunAllVector4Nodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedSelfDeactivateParseError1)
{
    ExpectParseError("LY_SC_UnitTest_SelfDeactivateParseError");
}

TEST_F(ScriptCanvasTestFixture, InterpretedSelfDeactivateParseErrorFromHandler2)
{
    ExpectParseError("LY_SC_UnitTest_SelfDeactivateParseErrorFromHandler");
}

TEST_F(ScriptCanvasTestFixture, InterpretedSelfDeactivateParse3)
{
    ExpectParse("LY_SC_UnitTest_SelfDeactivateParse");
}

TEST_F(ScriptCanvasTestFixture, InterpretedSelfDeactivateParseFromHandler4)
{
    ExpectParse("LY_SC_UnitTest_SelfDeactivateParseFromHandler");
}

TEST_F(ScriptCanvasTestFixture, InterpretedAddMatrix)
{
    RunUnitTestGraph("LY_SC_UnitTest_AddMatrix");
}

TEST_F(ScriptCanvasTestFixture, InterpretedContainerEraseCheck)
{
    RunUnitTestGraph("LY_SC_UnitTest_ContainerEraseCheck");
}

TEST_F(ScriptCanvasTestFixture, InterpretedChainedInfiniteLoop)
{
    ScriptCanvasEditor::RunSpec spec;
    spec.release = false;
    spec.expectRuntimeFailure = true;
    RunUnitTestGraph("LY_SC_UnitTest_ChainedInfiniteLoop", spec);
}

TEST_F(ScriptCanvasTestFixture, InterpretedGetTimeAtCurrentTickRegression)
{
    RunUnitTestGraph("LY_SC_UnitTest_GetTimeAtCurrentTickRegression");
}

TEST_F(ScriptCanvasTestFixture, InterpretedUnhandledEventReturnValueTypeChange)
{
    RunUnitTestGraph("LY_SC_UnitTest_UnhandledEventReturnValueTypeChange");
}

TEST_F(ScriptCanvasTestFixture, InterpretedUnhandledEventReturnValueTypeChangeTuple)
{
    RunUnitTestGraph("LY_SC_UnitTest_UnhandledEventReturnValueTypeChangeTuple");
}

TEST_F(ScriptCanvasTestFixture, NodeableDurationFunction)
{
    ExpectParse("LY_SC_UnitTest_NodeableDurationFunction");
}

TEST_F(ScriptCanvasTestFixture, LatentCallOfPureUserFunction)
{
    RunUnitTestGraph("LY_SC_UnitTest_LatentCallOfPureUserFunction", ExecutionMode::Interpreted, DurationSpec::Ticks(3));
}

TEST_F(ScriptCanvasTestFixture, LatentCallOfNotPureUserFunction)
{
    RunUnitTestGraph("LY_SC_UnitTest_LatentCallOfNotPureUserFunction", ExecutionMode::Interpreted, DurationSpec::Ticks(3));
}

TEST_F(ScriptCanvasTestFixture, NodeableDurationSubgraph)
{
    RunUnitTestGraph("LY_SC_UnitTest_NodeableDurationSubgraph", ExecutionMode::Interpreted, DurationSpec::Ticks(3));
}
 
TEST_F(ScriptCanvasTestFixture, NodeableDurationFunctionDirectExposeOut)
{
    ExpectParse("LY_SC_UnitTest_NodeableDurationFunctionDirectExposeOut");
}

TEST_F(ScriptCanvasTestFixture, NodeableDurationSubgraphDirectExposedOut)
{
    RunUnitTestGraph("LY_SC_UnitTest_NodeableDurationSubgraphDirectExposedOut", ExecutionMode::Interpreted, DurationSpec::Ticks(3));
}

TEST_F(ScriptCanvasTestFixture, ForEachNodeNoInputParseError)
{
    ExpectParseError("LY_SC_UnitTest_ForEachNodeNoInputParseError");
}

TEST_F(ScriptCanvasTestFixture, InterpretedCycleDetectError)
{
    ExpectParseError("LY_SC_UnitTest_CycleDetectError");
}

TEST_F(ScriptCanvasTestFixture, InterpretedCycleDetectSimple)
{
    ExpectParseError("LY_SC_UnitTest_CycleDetectSimple");
}

TEST_F(ScriptCanvasTestFixture, InterpretedMultipleOutDataFlowParseError)
{
    ExpectParseError("LY_SC_UnitTest_MultipleOutDataFlowParseError");
}

TEST_F(ScriptCanvasTestFixture, InterpretedSimultaneousDataInputError)
{
    ExpectParseError("LY_SC_UnitTest_SimultaneousDataInputError");
}

TEST_F(ScriptCanvasTestFixture, InterpretedAnyAsTailNoOp)
{
    RunUnitTestGraph("LY_SC_UnitTest_AnyAsTailNoOp");
}

TEST_F(ScriptCanvasTestFixture, InterpretedConstructionVariableOrder)
{
     RunUnitTestGraph("LY_SC_UnitTest_ConstructionVariableOrder", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedCycleDetectCleanGraph)
{
    RunUnitTestGraph("LY_SC_UnitTest_CycleDetectCleanGraph", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, ParseErrorCycleDetectErrorPastIfBranch)
{
    ExpectParseError("LY_SC_UnitTest_CycleDetectErrorPastIfBranch");
}

TEST_F(ScriptCanvasTestFixture, ParseErrorCycleDetectErrorPastOnce)
{
    ExpectParseError("LY_SC_UnitTest_CycleDetectErrorPastOnce");
}

TEST_F(ScriptCanvasTestFixture, InterpretedCycleDetectErrorPostLatent)
{
    ExpectParseError("LY_SC_UnitTest_CycleDetectErrorPostLatent");
}

TEST_F(ScriptCanvasTestFixture, InterpretedCycleDetectCleanGraphSequenceVersion)
{
    RunUnitTestGraph("LY_SC_UnitTest_CycleDetectCleanGraphSequenceVersion", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedCycleDetectWorksWithSequence)
{
    RunUnitTestGraph("LY_SC_UnitTest_CycleDetectWorksWithSequence", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedAndBranch)
{
    RunUnitTestGraph("LY_SC_UnitTest_AndBranch", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedAny)
{
    RunUnitTestGraph("LY_SC_UnitTest_Any", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedCompareEqual)
{
    RunUnitTestGraph("LY_SC_UnitTest_CompareEqual", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedCompareGreater)
{
    RunUnitTestGraph("LY_SC_UnitTest_CompareGreater", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedCompareGreaterEqual)
{
    RunUnitTestGraph("LY_SC_UnitTest_CompareGreaterEqual", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedCompareLess)
{
    RunUnitTestGraph("LY_SC_UnitTest_CompareLess", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedCompareLessEqual)
{
    RunUnitTestGraph("LY_SC_UnitTest_CompareLessEqual", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedCompareNotEqual)
{
    RunUnitTestGraph("LY_SC_UnitTest_CompareNotEqual", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedContainerBasicOperators)
{
    RunUnitTestGraph("LY_SC_UnitTest_ContainerBasicOperators", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedCycle)
{
    RunUnitTestGraph("LY_SC_UnitTest_Cycle", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedCycleData)
{
    RunUnitTestGraph("LY_SC_UnitTest_CycleData", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedDataConversionsBooleanNumber)
{
    RunUnitTestGraph("LY_SC_UnitTest_DataConversionsBooleanNumber", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedDataConversionsColor)
{
    RunUnitTestGraph("LY_SC_UnitTest_DataConversionsColor", ExecutionMode::Interpreted);
}

// restore this test after conversions are restored
//
// TEST_F(ScriptCanvasTestFixture, InterpretedDataConversionsMatrix)
// {
//     RunUnitTestGraph("LY_SC_UnitTest_DataConversionsMatrix", ExecutionMode::Interpreted);
// }
// 
//  TEST_F(ScriptCanvasTestFixture, InterpretedDataConversionsString)
//  { 
//      RunUnitTestGraph("LY_SC_UnitTest_DataConversionsString", ExecutionMode::Interpreted);
//  }
// 
//  TEST_F(ScriptCanvasTestFixture, InterpretedDataConversionsTransformQuaternion)
//  {
//      RunUnitTestGraph("LY_SC_UnitTest_DataConversionsTransformQuaternion", ExecutionMode::Interpreted);
//  }

TEST_F(ScriptCanvasTestFixture, InterpretedDataConversionsVector)
{
    RunUnitTestGraph("LY_SC_UnitTest_DataConversionsVector", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedDisabledNode)
{
    RunUnitTestGraph("LY_SC_UnitTest_DisabledNode", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedEventHandling)
{
    RunUnitTestGraph("LY_SC_UnitTest_EventHandling", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedEventHandlingAddressUpdate)
{
    RunUnitTestGraph("LY_SC_UnitTest_EventHandlingAddressUpdate", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedEventHandlingAddressUpdateReference)
{
    RunUnitTestGraph("LY_SC_UnitTest_EventHandlingAddressUpdateReference", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedEventHandlingDataConversion)
{
    RunUnitTestGraph("LY_SC_UnitTest_EventHandlingDataConversion", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedEventHandlingDataOnly)
{
    RunUnitTestGraph("LY_SC_UnitTest_EventHandlingDataOnly", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedEventHandlingDetectInfiniteLoop)
{
    ScriptCanvasEditor::RunSpec spec;
    spec.release = false;
    spec.expectRuntimeFailure = true;
    RunUnitTestGraph("LY_SC_UnitTest_EventHandlingDetectInfiniteLoop", spec);
}

TEST_F(ScriptCanvasTestFixture, InterpretedEventHandlingLocal)
{
    RunUnitTestGraph("LY_SC_UnitTest_EventHandlingLocal", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedEventHandlingLocalAddressByConnection)
{
    RunUnitTestGraph("LY_SC_UnitTest_EventHandlingLocalAddressByConnection", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedEventHandlingLocalVoid)
{
    RunUnitTestGraph("LY_SC_UnitTest_EventHandlingLocalVoid", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedEventHandlingVoid)
{
    RunUnitTestGraph("LY_SC_UnitTest_EventHandlingVoid", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedScriptEventGlobal)
{
    RunUnitTestGraph("LY_SC_UnitTest_GlobalScriptEvent", ExecutionMode::Interpreted, "globalscriptevents");
}

TEST_F(ScriptCanvasTestFixture, InterpretedScriptEventLocal)
{
    RunUnitTestGraph("LY_SC_UnitTest_LocalScriptEvent", ExecutionMode::Interpreted, "localscriptevents");
}

TEST_F(ScriptCanvasTestFixture, InterpretedScriptEventAddressUpdate)
{
    RunUnitTestGraph("LY_SC_UnitTest_ScriptEventAddressUpdate", ExecutionMode::Interpreted, "localscriptevents");
}

TEST_F(ScriptCanvasTestFixture, InterpretedScriptEventAddressUpdateReference)
{
    RunUnitTestGraph("LY_SC_UnitTest_ScriptEventAddressUpdateReference", ExecutionMode::Interpreted, "localscriptevents");
}

TEST_F(ScriptCanvasTestFixture, InterpretedScriptEventLocalAddressByConnection)
{
    RunUnitTestGraph("LY_SC_UnitTest_ScriptEventLocalAddressByConnection", ExecutionMode::Interpreted, "localscriptevents");
}

TEST_F(ScriptCanvasTestFixture, InterpretedExplicitOverloadDivideByNumber)
{
    RunUnitTestGraph("LY_SC_UnitTest_ExplicitOverloadDivideByNumber", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedExplicitOverloadLength)
{
    RunUnitTestGraph("LY_SC_UnitTest_ExplicitOverloadLength", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedForEachIterationArray)
{
    RunUnitTestGraph("LY_SC_UnitTest_ForEachIterationArray", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedForEachIterationArrayUseValueAsInputAfterBreak)
{
    RunUnitTestGraph("LY_SC_UnitTest_ForEachIterationArrayUseValueAsInputAfterBreak", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedForEachIterationArrayUseValueAsInputAfterBreakNested)
{
    RunUnitTestGraph("LY_SC_UnitTest_ForEachIterationArrayUseValueAsInputAfterBreakNested", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedForEachIterationMap)
{
    RunUnitTestGraph("LY_SC_UnitTest_ForEachIterationMap", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedGetElementMap)
{
    RunUnitTestGraph("LY_SC_UnitTest_GetElementMap", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedIfBranch)
{
    RunUnitTestGraph("LY_SC_UnitTest_IfBranch", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedIsEmptyMap)
{
    RunUnitTestGraph("LY_SC_UnitTest_IsEmptyMap", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedIsNull)
{
    RunUnitTestGraph("LY_SC_UnitTest_IsNull", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedLerpBetween)
{
    RunUnitTestGraph("LY_SC_UnitTest_LerpBetween", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedMathExpression)
{
    RunUnitTestGraph("LY_SC_UnitTest_MathExpression", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedMultipleOut)
{
    RunUnitTestGraph("LY_SC_UnitTest_MultipleOut", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedMultipleOutDataFlow)
{
    RunUnitTestGraph("LY_SC_UnitTest_MultipleOutDataFlow", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedMultipleOutInputBugFix)
{
    RunUnitTestGraph("LY_SC_UnitTest_MultipleOutInputBugFix", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedMultipleOutFromIf)
{
    RunUnitTestGraph("LY_SC_UnitTest_MultipleOutFromIf", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedMultipleOutFromRoot)
{
    RunUnitTestGraph("LY_SC_UnitTest_MultipleOutFromRoot", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedMultipleOutSyntaxSugar)
{
    RunUnitTestGraph("LY_SC_UnitTest_MultipleOutSyntaxSugar", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedMultipleReturnResults)
{
    RunUnitTestGraph("LY_SC_UnitTest_MultipleReturnResults", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedMultipleReturnResultsGeneric)
{
    RunUnitTestGraph("LY_SC_UnitTest_MultipleReturnResultsGeneric", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedMultipleReturnResultsGenericByValue)
{
    RunUnitTestGraph("LY_SC_UnitTest_MultipleReturnResultsGenericByValue", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedMultipleStartNodes)
{
    RunUnitTestGraph("LY_SC_UnitTest_MultipleStartNodes");
}

TEST_F(ScriptCanvasTestFixture, InterpretedNodeableDuration)
{
    RunUnitTestGraph("LY_SC_UnitTest_NodeableDuration", ExecutionMode::Interpreted, DurationSpec::Seconds(1.1f));
}

TEST_F(ScriptCanvasTestFixture, InterpretedNodeableDelay)
{
    RunUnitTestGraph("LY_SC_UnitTest_NodeableDelay", ExecutionMode::Interpreted, DurationSpec::Seconds(3.1f));
}

TEST_F(ScriptCanvasTestFixture, InterpretedNodeableDelayWithLooping)
{
    RunUnitTestGraph("LY_SC_UnitTest_NodeableDelayWithLooping", ExecutionMode::Interpreted, DurationSpec::Seconds(3.1f));
}

TEST_F(ScriptCanvasTestFixture, InterpretedNodeableTimer)
{
    RunUnitTestGraph("LY_SC_UnitTest_NodeableTimer", ExecutionMode::Interpreted, DurationSpec::Ticks(6));
}

TEST_F(ScriptCanvasTestFixture, InterpretedNodeableTimeDelay)
{
    RunUnitTestGraph("LY_SC_UnitTest_NodeableTimeDelay", ExecutionMode::Interpreted, DurationSpec::Ticks(6));
}

TEST_F(ScriptCanvasTestFixture, InterpretedNodeableHeartBeat)
{
    RunUnitTestGraph("LY_SC_UnitTest_NodeableHeartBeat", ExecutionMode::Interpreted, DurationSpec::Ticks(31));
}

TEST_F(ScriptCanvasTestFixture, InterpretedNodeableRepeater)
{
    RunUnitTestGraph("LY_SC_UnitTest_NodeableRepeater", ExecutionMode::Interpreted, DurationSpec::Ticks(11));
}

TEST_F(ScriptCanvasTestFixture, InterpretedNotBranch)
{
    RunUnitTestGraph("LY_SC_UnitTest_NotBranch", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedOnce)
{
    RunUnitTestGraph("LY_SC_UnitTest_Once", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedOperatorAdd)
{
    RunUnitTestGraph("LY_SC_UnitTest_OperatorAdd", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedOperatorDiv)
{
    RunUnitTestGraph("LY_SC_UnitTest_OperatorDiv", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedOperatorMul)
{
    RunUnitTestGraph("LY_SC_UnitTest_OperatorMul", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedOperatorSub)
{
    RunUnitTestGraph("LY_SC_UnitTest_OperatorSub", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedOrBranch)
{
    RunUnitTestGraph("LY_SC_UnitTest_OrBranch", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedOrderedSequencer)
{
    RunUnitTestGraph("LY_SC_UnitTest_OrderedSequencer", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedPerformance)
{
    RunUnitTestGraph("LY_SC_UnitTest_Performance", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedPrint)
{
    RunUnitTestGraph("LY_SC_UnitTest_Print", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedPrintConnectedInput)
{
    RunUnitTestGraph("LY_SC_UnitTest_PrintConnectedInput", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedPrintFormatEmptyValue)
{
    RunUnitTestGraph("LY_SC_UnitTest_PrintFormatEmptyValue", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedProperties)
{
    RunUnitTestGraph("LY_SC_UnitTest_Properties", ExecutionMode::Interpreted);
}
 
TEST_F(ScriptCanvasTestFixture, InterpretedPropertiesLiteReference)
{
    RunUnitTestGraph("LY_SC_UnitTest_PropertiesLite", ExecutionMode::Interpreted);
}
 
TEST_F(ScriptCanvasTestFixture, InterpretedPropertiesLiteConnection)
{
    RunUnitTestGraph("LY_SC_UnitTest_PropertiesByConnection", ExecutionMode::Interpreted);
}
 
TEST_F(ScriptCanvasTestFixture, InterpretedPropertiesRecursion)
{
    RunUnitTestGraph("LY_SC_UnitTest_PropertiesRecursion", ExecutionMode::Interpreted);
}
 
TEST_F(ScriptCanvasTestFixture, InterpretedPropertiesSet)
{
    RunUnitTestGraph("LY_SC_UnitTest_PropertiesSet", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedRandomSignal)
{
    RunUnitTestGraph("LY_SC_UnitTest_RandomSignal", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedStringFormat)
{
    RunUnitTestGraph("LY_SC_UnitTest_StringFormat", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedStringFormatEmptyValue)
{
    RunUnitTestGraph("LY_SC_UnitTest_StringFormatEmptyValue", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedStringFormatWithRepeatedValueName)
{
    RunUnitTestGraph("LY_SC_UnitTest_StringFormatWithRepeatedValueName", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedSwitch)
{
    RunUnitTestGraph("LY_SC_UnitTest_Switch", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedVariableChangeEvent)
{
    RunUnitTestGraph("LY_SC_UnitTest_VariableChangeEvent", ExecutionMode::Interpreted);
}
 
TEST_F(ScriptCanvasTestFixture, InterpretedVariableChangeEventConnectionControl)
{
    RunUnitTestGraph("LY_SC_UnitTest_VariableChangeEventConnectionControl", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedVariableChangeEventWithCheck)
{
    RunUnitTestGraph("LY_SC_UnitTest_VariableChangeEventWithCheck", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedVariableChangeEventInfiniteLoopCheckError)
{
    ExpectParseError("LY_SC_UnitTest_VariableChangeEventInfiniteLoopCheckError");
}

TEST_F(ScriptCanvasTestFixture, InterpretedVariableReferences)
{
    RunUnitTestGraph("LY_SC_UnitTest_VariableReferences", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedVariableReferenceChangeEventWithCheck)
{
    RunUnitTestGraph("LY_SC_UnitTest_VariableReferenceChangeEventWithCheck", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedVector)
{
    RunUnitTestGraph("LY_SC_UnitTest_Vector", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedWhile)
{
    RunUnitTestGraph("LY_SC_UnitTest_While", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedWhileDetectInfiniteLoop)
{
    ScriptCanvasEditor::RunSpec spec;
    spec.release = false;
    spec.expectRuntimeFailure = true;
    RunUnitTestGraph("LY_SC_UnitTest_WhileDetectInfiniteLoop", spec);
}

TEST_F(ScriptCanvasTestFixture, InterpretedWhileBreak)
{
    RunUnitTestGraph("LY_SC_UnitTest_WhileBreak", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedDivideByNumber)
{
    RunUnitTestGraph("LY_SC_UnitTest_DivideByNumber");
}

TEST_F(ScriptCanvasTestFixture, InterpretedPathologicalFlowOfControl)
{
    RunUnitTestGraph("LY_SC_UnitTest_PathologicalFlowOfControl");
}

TEST_F(ScriptCanvasTestFixture, InterpretedPathologicalFlowOfControlFixSwitchLite)
{
    RunUnitTestGraph("LY_SC_UnitTest_PathologicalFlowOfControlFixSwitchLite");
}

TEST_F(ScriptCanvasTestFixture, InterpretedPathologicalFlowOfControlFixSwitch)
{
    RunUnitTestGraph("LY_SC_UnitTest_PathologicalFlowOfControlFixSwitch");
}

TEST_F(ScriptCanvasTestFixture, InterpretedInputValuePointerReferenceType)
{
    RunUnitTestGraph("LY_SC_UnitTest_InputValuePointerReferenceType");
}

TEST_F(ScriptCanvasTestFixture, InterpretedReturnValuePointerReferenceType)
{
    RunUnitTestGraph("LY_SC_UnitTest_ReturnValuePointerReferenceType");
}

TEST_F(ScriptCanvasTestFixture, InterpretedBranchInputValuePointerReferenceType)
{
    RunUnitTestGraph("LY_SC_UnitTest_BranchInputValuePointerReferenceType");
}

// \todo formal support of shared slots
// TEST_F(ScriptCanvasTestFixture, InterpretedNodeableBranchMethodSharedDataSlot)
// {
//     RunUnitTestGraph("LY_SC_UnitTest_NodeableBranchMethodSharedDataSlot", ExecutionMode::Interpreted);
// }

TEST_F(ScriptCanvasTestFixture, InterpretedNodeableInputMethodSharedDataSlot)
{
    RunUnitTestGraph("LY_SC_UnitTest_NodeableInputMethodSharedDataSlot", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedExecutionOutPerformance)
{
    RunUnitTestGraph("LY_SC_UnitTest_ExecutionOutPerformance", ExecutionMode::Interpreted);
}

#if defined(FUNCTION_LEGACY_SUPPORT_ENABLED)

TEST_F(ScriptCanvasTestFixture, InterpretedSubgraph_UserNodeable)
{
    ExpectParse("LY_SC_UnitTest_Subgraph_UserNodeableD");
}

TEST_F(ScriptCanvasTestFixture, InterpretedSubgraph_UserNodeableLatent)
{
    ExpectParse("LY_SC_UnitTest_Subgraph_UserNodeableLatent");
}

TEST_F(ScriptCanvasTestFixture, InterpretedUseFunctionWithOnGraphStart)
{
    RunUnitTestGraph("LY_SC_UnitTest_UseFunctionWithOnGraphStart");
}

TEST_F(ScriptCanvasTestFixture, InterpretedUseSubgraphWithStartAndEBus)
{
    RunUnitTestGraph("LY_SC_UnitTests_UseSubgraphWithStartAndEBus");
}

TEST_F(ScriptCanvasTestFixture, InterpretedDeviousStateFunctionFixGraph)
{
    RunUnitTestGraph("LY_SC_UnitTest_DeviousStateFunctionFixGraph");
}

TEST_F(ScriptCanvasTestFixture, InterpretedCallFunctionLocalValues)
{
    RunUnitTestGraph("LY_SC_UnitTest_CallFunctionLocalValues");
}

TEST_F(ScriptCanvasTestFixture, ParseFunctionLocalObjects)
{
    ExpectParse("LY_SC_UnitTest_FunctionLocalObjects");
}

TEST_F(ScriptCanvasTestFixture, InterpretedFunctionLocalObjectsCall)
{
    RunUnitTestGraph("LY_SC_UnitTest_FunctionLocalObjectsCall", ExecutionMode::Interpreted, DurationSpec::Ticks(31));
}

TEST_F(ScriptCanvasTestFixture, ParseFunctionWithOnGraphStart)
{
    ExpectParse("LY_SC_UnitTest_FunctionWithOnGraphStart");
}

TEST_F(ScriptCanvasTestFixture, NodeableDurationSubgraphDirectionExposedOutWithOutput)
{
    RunUnitTestGraph("LY_SC_UnitTest_NodeableDurationSubgraphDirectionExposedOutWithOutput", ExecutionMode::Interpreted, DurationSpec::Ticks(3));
}

TEST_F(ScriptCanvasTestFixture, ParseOrderedSequencerFunction)
{
    ExpectParse("LY_SC_UnitTest_OrderedSequencerFunction");
}

TEST_F(ScriptCanvasTestFixture, ParseFunction_Names_With_Spaces)
{
    ExpectParse("LY_SC_UnitTest_Function Names With Spaces");
}

TEST_F(ScriptCanvasTestFixture, ParseFunctionNameEvilVersion)
{
    ExpectParse("LY_SC_UnitTest_Function Names(With) Random+Strings Evil~Version");
}

TEST_F(ScriptCanvasTestFixture, ParseFunctionNameEvilVersionInFolder)
{
    ExpectParse("TestFunction/LY_SC_UnitTest_Function Names(With) Random+Strings Evil~Version-In^Forder");
}

TEST_F(ScriptCanvasTestFixture, ParseNodeableDurationFunction)
{
    ExpectParse("LY_SC_UnitTest_NodeableDurationFunction");
}

TEST_F(ScriptCanvasTestFixture, ParseNodeableDurationFunctionDirectExposure)
{
    ExpectParse("LY_SC_UnitTest_NodeableDurationFunctionDirectExposure");
}

TEST_F(ScriptCanvasTestFixture, ParseNodeableDurationFunctionDirectExposureWithOutput)
{
    ExpectParse("LY_SC_UnitTest_NodeableDurationFunctionDirectExposureWithOutput");
}


TEST_F(ScriptCanvasTestFixture, ParseFunctionBranchSingleNamedOutJustReturns)
{
    ExpectParse("LY_SC_UnitTest_ParseFunctionBranchSingleNamedOutJustReturns");
}

TEST_F(ScriptCanvasTestFixture, ParseExposeAnyOut)
{
    ExpectParse("LY_SC_UnitTest_ExposeAnyOut");
}

TEST_F(ScriptCanvasTestFixture, ParseMultipleInputNoParseError)
{
    ExpectParse("LY_SC_UnitTest_MultipleInputNoParseError");
}

TEST_F(ScriptCanvasTestFixture, InterpretedSubgraphMultipleInError)
{
    ExpectParseError("LY_SC_UnitTest_InterpretedSubgraphMultipleInError");
}

TEST_F(ScriptCanvasTestFixture, InterpretedSubgraphMultipleOutError)
{
    ExpectParseError("LY_SC_UnitTest_InterpretedSubgraphMultipleOutError");
}

TEST_F(ScriptCanvasTestFixture, InterpretedSubgraphOutInLoop)
{
    ExpectParseError("LY_SC_UnitTest_InterpretedSubgraphOutInLoop");
}

TEST_F(ScriptCanvasTestFixture, InterpretedSubgraphOutMidCycleMissingSlots)
{
    ExpectParseError("LY_SC_UnitTest_InterpretedSubgraphOutMidCycleMissingSlots");
}

TEST_F(ScriptCanvasTestFixture, InterpretedSubgraphComplexityError)
{
    ExpectParseError("LY_SC_UnitTest_SubgraphComplexityError");
}

TEST_F(ScriptCanvasTestFixture, InterpretedSubgraphReturnValueFromIn)
{
    ExpectParseError("LY_SC_UnitTest_SubgraphReturnValueFromIn");
}

TEST_F(ScriptCanvasTestFixture, InterpretedSubgraphReturnValueFromInOut)
{
    ExpectParseError("LY_SC_UnitTest_SubgraphReturnValueFromInOut");
}

TEST_F(ScriptCanvasTestFixture, InterpretedVerifyByValueCorrectness)
{
    RunUnitTestGraph("LY_SC_UnitTest_VerifyByValueCorrectness", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedFunctionNoInputOneOutputCall)
{
    RunUnitTestGraph("LY_SC_UnitTest_FunctionNoInputOneOutputCall", ExecutionMode::Interpreted);
}

TEST_F(ScriptCanvasTestFixture, InterpretedFunctionAddVector3Call)
{
    RunUnitTestGraph("LY_SC_UnitTest_FunctionAddVector3Call", ExecutionMode::Interpreted);
}
TEST_F(ScriptCanvasTestFixture, InterpretedParseFunction)
{
    ExpectParse("LY_SC_UnitTest_ParseFunction");
}

TEST_F(ScriptCanvasTestFixture, InterpretedParseFunctionBranch)
{
    ExpectParse("LY_SC_UnitTest_ParseFunctionBranch");
}

TEST_F(ScriptCanvasTestFixture, InterpretedParseFunctionBranchDefaultOut)
{
    ExpectParse("LY_SC_UnitTest_ParseFunctionBranchDefaultOut");
}

TEST_F(ScriptCanvasTestFixture, InterpretedParseFunctionDefaultOut)
{
    ExpectParse("LY_SC_UnitTest_ParseFunctionDefaultOut");
}

TEST_F(ScriptCanvasTestFixture, InterpretedParseFunctionOut)
{
    ExpectParse("LY_SC_UnitTest_ParseFunctionOut");
}
#endif
