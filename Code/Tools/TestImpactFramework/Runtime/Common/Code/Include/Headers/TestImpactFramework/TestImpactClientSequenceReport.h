/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <TestImpactFramework/TestImpactClientTestRun.h>
#include <TestImpactFramework/TestImpactClientTestSelection.h>
#include <TestImpactFramework/TestImpactTestSequence.h>

#include <AzCore/std/optional.h>
#include <AzCore/std/chrono/chrono.h>

namespace TestImpact
{
    namespace Client
    {
        //! The report types generated by each sequence.
        enum class SequenceReportType : AZ::u8
        {
            RegularSequence,
            SeedSequence,
            ImpactAnalysisSequence,
            SafeImpactAnalysisSequence
        };

        //! Calculates the final sequence result for a composite of multiple sequences.
        TestSequenceResult CalculateMultiTestSequenceResult(const AZStd::vector<TestSequenceResult>& results);

        //! Report detailing the result and duration of a given set of test runs along with the details of each individual test run.
        class TestRunReport
        {
        public:
            //! Constructs the report for the given set of test runs that were run together in the same set.
            //! @param result The result of this set of test runs.
            //! @param startTime The time point his set of test runs started.
            //! @param duration The duration this set of test runs took to complete.
            //! @param passingTestRuns The set of test runs that executed successfully with no failing test runs.
            //! @param failingTestRuns The set of test runs that executed successfully but had one or more failing tests.
            //! @param executionFailureTestRuns The set of test runs that failed to execute.
            //! @param timedOutTestRuns The set of test runs that executed successfully but were terminated prematurely due to timing out.
            //! @param unexecutedTestRuns The set of test runs that were queued up for execution but did not get the opportunity to execute.
            TestRunReport(
                TestSequenceResult result,
                AZStd::chrono::high_resolution_clock::time_point startTime,
                AZStd::chrono::milliseconds duration,
                AZStd::vector<PassingTestRun>&& passingTestRuns,
                AZStd::vector<FailingTestRun>&& failingTestRuns,
                AZStd::vector<TestRunWithExecutionFailure>&& executionFailureTestRuns,
                AZStd::vector<TimedOutTestRun>&& timedOutTestRuns,
                AZStd::vector<UnexecutedTestRun>&& unexecutedTestRuns);

            //! Returns the result of this sequence of test runs.
            TestSequenceResult GetResult() const;

            //! Returns the time this sequence of test runs started relative to T0.
            AZStd::chrono::high_resolution_clock::time_point GetStartTime() const;

            //! Returns the time this sequence of test runs ended relative to T0.
            AZStd::chrono::high_resolution_clock::time_point GetEndTime() const;

            //! Returns the duration this sequence of test runs took to complete.
            AZStd::chrono::milliseconds GetDuration() const;

            //! Returns the total number of test runs.
            size_t GetTotalNumTestRuns() const;

            //! Returns the number of passing test runs.
            size_t GetNumPassingTestRuns() const;

            //! Returns the number of failing test runs.
            size_t GetNumFailingTestRuns() const;

            //! Returns the number of test runs that failed to execute.
            size_t GetNumExecutionFailureTestRuns() const;

            //! Returns the number of timed out test runs.
            size_t GetNumTimedOutTestRuns() const;

            //! Returns the number of unexecuted test runs.
            size_t GetNumUnexecutedTestRuns() const;

            //! Returns the total number of passing tests across all test runs in the report.
            size_t GetTotalNumPassingTests() const;

            //! Returns the total number of failing tests across all test runs in the report.
            size_t GetTotalNumFailingTests() const;

            //! Returns the total number of disabled tests across all test runs in the report.
            size_t GetTotalNumDisabledTests() const;

            //! Returns the set of test runs that executed successfully with no failing tests.
            const AZStd::vector<PassingTestRun>& GetPassingTestRuns() const;

            //! Returns the set of test runs that executed successfully but had one or more failing tests.
            const AZStd::vector<FailingTestRun>& GetFailingTestRuns() const;

            //! Returns the set of test runs that failed to execute.
            const AZStd::vector<TestRunWithExecutionFailure>& GetExecutionFailureTestRuns() const;

            //! Returns the set of test runs that executed successfully but were terminated prematurely due to timing out.
            const AZStd::vector<TimedOutTestRun>& GetTimedOutTestRuns() const;

            //! Returns the set of test runs that were queued up for execution but did not get the opportunity to execute.
            const AZStd::vector<UnexecutedTestRun>& GetUnexecutedTestRuns() const;
        private:
            TestSequenceResult m_result = TestSequenceResult::Success;
            AZStd::chrono::high_resolution_clock::time_point m_startTime;
            AZStd::chrono::milliseconds m_duration = AZStd::chrono::milliseconds{ 0 };
            AZStd::vector<PassingTestRun> m_passingTestRuns;
            AZStd::vector<FailingTestRun> m_failingTestRuns;
            AZStd::vector<TestRunWithExecutionFailure> m_executionFailureTestRuns;
            AZStd::vector<TimedOutTestRun> m_timedOutTestRuns;
            AZStd::vector<UnexecutedTestRun> m_unexecutedTestRuns;
            size_t m_totalNumPassingTests = 0;
            size_t m_totalNumFailingTests = 0;
            size_t m_totalNumDisabledTests = 0;
        };

        //! Base class for all sequence report types.
        template<SequenceReportType Type, typename PolicyStateType>
        class SequenceReportBase
        {
        public:
            static constexpr SequenceReportType ReportType = Type;
            using PolicyState = PolicyStateType;

            //! Constructs the report for a sequence of selected tests.
            //! @param maxConcurrency The maximum number of concurrent test targets in flight at any given time.
            //! @param testTargetTimeout The maximum duration individual test targets may be in flight for (infinite if empty).
            //! @param globalTimeout The maximum duration the entire test sequence may run for (infinite if empty).
            //! @param policyState The policy state this sequence was executed under.
            //! @param suiteType The suite from which the tests have been selected from.
            //! @param selectedTestRuns The target names of the selected test runs.
            //! @param selectedTestRunReport The report for the set of selected test runs.
            SequenceReportBase(
                size_t maxConcurrency,
                AZStd::optional<AZStd::chrono::milliseconds> testTargetTimeout,
                AZStd::optional<AZStd::chrono::milliseconds> globalTimeout,
                PolicyStateType policyState,
                SuiteType suiteType,
                TestRunSelection selectedTestRuns,
                TestRunReport selectedTestRunReport)
                : m_maxConcurrency(maxConcurrency)
                , m_testTargetTimeout(AZStd::move(testTargetTimeout))
                , m_globalTimeout(AZStd::move(globalTimeout))
                , m_policyState(AZStd::move(policyState))
                , m_suite(suiteType)
                , m_selectedTestRuns(AZStd::move(selectedTestRuns))
                , m_selectedTestRunReport(AZStd::move(selectedTestRunReport))
            {
            }

            SequenceReportBase(SequenceReportBase&& report)
                : SequenceReportBase(
                    AZStd::move(report.m_maxConcurrency),
                    AZStd::move(report.m_testTargetTimeout),
                    AZStd::move(report.m_globalTimeout),
                    AZStd::move(report.m_policyState),
                    AZStd::move(report.m_suite),
                    AZStd::move(report.m_selectedTestRuns),
                    AZStd::move(report.m_selectedTestRunReport))
            {
            }

            SequenceReportBase(const SequenceReportBase& report)
                : SequenceReportBase(
                    report.m_maxConcurrency,
                    report.m_testTargetTimeout,
                    report.m_globalTimeout,
                    report.m_policyState,
                    report.m_suite,
                    report.m_selectedTestRuns,
                    report.m_selectedTestRunReport)
            {
            }

            virtual ~SequenceReportBase() = default;

            //! Returns the maximum concurrency for this sequence.
            size_t GetMaxConcurrency() const
            {
                return m_maxConcurrency;
            }

            //! Returns the global timeout for this sequence.
            const AZStd::optional<AZStd::chrono::milliseconds>& GetGlobalTimeout() const
            {
                return m_globalTimeout;
            }

            //! Returns the test target timeout for this sequence.
            const AZStd::optional<AZStd::chrono::milliseconds>& GetTestTargetTimeout() const
            {
                return m_testTargetTimeout;
            }

            //! Returns the policy state for this sequence.
            const PolicyStateType& GetPolicyState() const
            {
                return m_policyState;
            }

            //! Returns the suite for this sequence.
            SuiteType GetSuite() const
            {
                return m_suite;
            }

             //! Returns the result of the sequence.
            virtual TestSequenceResult GetResult() const
            {
                return m_selectedTestRunReport.GetResult();
            }

            //! Returns the tests selected for running in the sequence.
            TestRunSelection GetSelectedTestRuns() const
            {
                return m_selectedTestRuns;
            }

            //! Returns the report for the selected test runs.
            TestRunReport GetSelectedTestRunReport() const
            {
                return m_selectedTestRunReport;
            }

            //! Returns the start time of the sequence.
            AZStd::chrono::high_resolution_clock::time_point GetStartTime() const
            {
                return m_selectedTestRunReport.GetStartTime();
            }

            //! Returns the end time of the sequence.
            AZStd::chrono::high_resolution_clock::time_point GetEndTime() const
            {
                return GetStartTime() + GetDuration();
            }

            //! Returns the entire duration the sequence took from start to finish.
            virtual AZStd::chrono::milliseconds GetDuration() const
            {
                return m_selectedTestRunReport.GetDuration();
            }

            //! Returns the total number of test runs across all test run reports.
            virtual size_t GetTotalNumTestRuns() const
            {
                return m_selectedTestRunReport.GetTotalNumTestRuns();
            }

            //! Returns the total number of passing tests across all test targets in all test run reports.
            virtual size_t GetTotalNumPassingTests() const
            {
                return m_selectedTestRunReport.GetTotalNumPassingTests();
            }

            //! Returns the total number of failing tests across all test targets in all test run reports.
            virtual size_t GetTotalNumFailingTests() const
            {
                return m_selectedTestRunReport.GetTotalNumFailingTests();
            }

            //! Returns the total number of unexecuted tests across all test targets in all test run reports.
            virtual size_t GetTotalNumDisabledTests() const
            {
                return m_selectedTestRunReport.GetTotalNumDisabledTests();
            }

            //! Get the total number of test runs in the sequence that passed.
            virtual size_t GetTotalNumPassingTestRuns() const
            {
                return m_selectedTestRunReport.GetNumPassingTestRuns();
            }

            //! Get the total number of test runs in the sequence that contain one or more test failures.
            virtual size_t GetTotalNumFailingTestRuns() const
            {
                return m_selectedTestRunReport.GetNumFailingTestRuns();
            }

            //! Returns the total number of test runs that failed to execute.
            virtual size_t GetTotalNumExecutionFailureTestRuns() const
            {
                return m_selectedTestRunReport.GetNumExecutionFailureTestRuns();
            }

            //! Get the total number of test runs in the sequence that timed out whilst in flight.
            virtual size_t GetTotalNumTimedOutTestRuns() const
            {
                return m_selectedTestRunReport.GetNumTimedOutTestRuns();
            }

            //! Get the total number of test runs in the sequence that were queued for execution but did not get the opportunity to execute.
            virtual size_t GetTotalNumUnexecutedTestRuns() const
            {
                return m_selectedTestRunReport.GetNumUnexecutedTestRuns();
            }

        private:
            size_t m_maxConcurrency = 0;
            AZStd::optional<AZStd::chrono::milliseconds> m_testTargetTimeout;
            AZStd::optional<AZStd::chrono::milliseconds> m_globalTimeout;
            PolicyStateType m_policyState;
            SuiteType m_suite = SuiteType::Main;
            TestRunSelection m_selectedTestRuns;
            TestRunReport m_selectedTestRunReport;
        };

        //! Report type for regular test sequences.
        class RegularSequenceReport
             : public SequenceReportBase<SequenceReportType::RegularSequence, SequencePolicyState>
        {
        public:
            using SequenceReportBase::SequenceReportBase;
        };

        //! Report type for seed test sequences.
        class SeedSequenceReport
             : public SequenceReportBase<SequenceReportType::SeedSequence, SequencePolicyState>
        {
        public:
            using SequenceReportBase::SequenceReportBase;
        };

        //! Report detailing a test run sequence of selected and drafted tests.
        template<SequenceReportType Type, typename PolicyStateType>
        class DraftingSequenceReportBase
            : public SequenceReportBase<Type, PolicyStateType>
        {
        public:
            //! Constructs the report for sequences that draft in previously failed/newly added test targets.
            //! @param maxConcurrency The maximum number of concurrent test targets in flight at any given time.
            //! @param testTargetTimeout The maximum duration individual test targets may be in flight for (infinite if empty).
            //! @param globalTimeout The maximum duration the entire test sequence may run for (infinite if empty).
            //! @param policyState The policy state this sequence was executed under.
            //! @param suiteType The suite from which the tests have been selected from.
            //! @param selectedTestRuns The target names of the selected test runs.
            //! @param draftedTestRuns The target names of the drafted test runs.
            //! @param selectedTestRunReport The report for the set of selected test runs.
            //! @param draftedTestRunReport The report for the set of drafted test runs.
            DraftingSequenceReportBase(
                size_t maxConcurrency,
                AZStd::optional<AZStd::chrono::milliseconds> testTargetTimeout,
                AZStd::optional<AZStd::chrono::milliseconds> globalTimeout,
                PolicyStateType policyState,
                SuiteType suiteType,
                TestRunSelection selectedTestRuns,
                AZStd::vector<AZStd::string> draftedTestRuns,
                TestRunReport&& selectedTestRunReport,
                TestRunReport&& draftedTestRunReport)
                : SequenceReportBase<Type, PolicyStateType>(
                    maxConcurrency,
                    testTargetTimeout,
                    globalTimeout,
                    policyState,
                    suiteType,
                    selectedTestRuns,
                    AZStd::move(selectedTestRunReport))
                , m_draftedTestRuns(AZStd::move(draftedTestRuns))
                , m_draftedTestRunReport(AZStd::move(draftedTestRunReport))
            {
            }

            DraftingSequenceReportBase(
                SequenceReportBase<Type, PolicyStateType>&& report,
                AZStd::vector<AZStd::string> draftedTestRuns,
                TestRunReport&& draftedTestRunReport)
                : SequenceReportBase<Type, PolicyStateType>(AZStd::move(report))
                , m_draftedTestRuns(AZStd::move(draftedTestRuns))
                , m_draftedTestRunReport(AZStd::move(draftedTestRunReport))
            {
            }

            //! Returns the tests drafted for running in the sequence.
            const AZStd::vector<AZStd::string>& GetDraftedTestRuns() const
            {
                return m_draftedTestRuns;
            }

            //! Returns the report for the drafted test runs.
            TestRunReport GetDraftedTestRunReport() const
            {
                return m_draftedTestRunReport;
            }

            // SequenceReport overrides ...
            AZStd::chrono::milliseconds GetDuration() const override
            {
                return SequenceReportBase<Type, PolicyStateType>::GetDuration() + m_draftedTestRunReport.GetDuration();
            }

            TestSequenceResult GetResult() const override
            {
                return CalculateMultiTestSequenceResult(
                    { SequenceReportBase<Type, PolicyStateType>::GetResult(), m_draftedTestRunReport.GetResult() });
            }

            size_t GetTotalNumTestRuns() const override
            {
                return SequenceReportBase<Type, PolicyStateType>::GetTotalNumTestRuns() + m_draftedTestRunReport.GetTotalNumTestRuns();
            }

            size_t GetTotalNumPassingTests() const override
            {
                return SequenceReportBase<Type, PolicyStateType>::GetTotalNumPassingTests() + m_draftedTestRunReport.GetTotalNumPassingTests();
            }

            size_t GetTotalNumFailingTests() const override
            {
                return SequenceReportBase<Type, PolicyStateType>::GetTotalNumFailingTests() + m_draftedTestRunReport.GetTotalNumFailingTests();
            }

            size_t GetTotalNumDisabledTests() const override
            {
                return SequenceReportBase<Type, PolicyStateType>::GetTotalNumDisabledTests() + m_draftedTestRunReport.GetTotalNumDisabledTests();
            }

            size_t GetTotalNumPassingTestRuns() const override
            {
                return SequenceReportBase<Type, PolicyStateType>::GetTotalNumPassingTestRuns() + m_draftedTestRunReport.GetNumPassingTestRuns();
            }

            size_t GetTotalNumFailingTestRuns() const override
            {
                return SequenceReportBase<Type, PolicyStateType>::GetTotalNumFailingTestRuns() + m_draftedTestRunReport.GetNumFailingTestRuns();
            }

            size_t GetTotalNumExecutionFailureTestRuns() const override
            {
                return SequenceReportBase<Type, PolicyStateType>::GetTotalNumExecutionFailureTestRuns() + m_draftedTestRunReport.GetNumExecutionFailureTestRuns();
            }

            size_t GetTotalNumTimedOutTestRuns() const override
            {
                return SequenceReportBase<Type, PolicyStateType>::GetTotalNumTimedOutTestRuns() + m_draftedTestRunReport.GetNumTimedOutTestRuns();
            }

            size_t GetTotalNumUnexecutedTestRuns() const override
            {
                return SequenceReportBase<Type, PolicyStateType>::GetTotalNumUnexecutedTestRuns() + m_draftedTestRunReport.GetNumUnexecutedTestRuns();
            }
        private:
            AZStd::vector<AZStd::string> m_draftedTestRuns;
            TestRunReport m_draftedTestRunReport;
        };

        //! Report detailing an impact analysis sequence of selected, discarded and drafted tests.
        class ImpactAnalysisSequenceReport
            : public DraftingSequenceReportBase<SequenceReportType::ImpactAnalysisSequence, ImpactAnalysisSequencePolicyState>
        {
        public:
            //! Constructs the report for an impact analysis sequence.
            //! @param maxConcurrency The maximum number of concurrent test targets in flight at any given time.
            //! @param testTargetTimeout The maximum duration individual test targets may be in flight for (infinite if empty).
            //! @param globalTimeout The maximum duration the entire test sequence may run for (infinite if empty).
            //! @param policyState The policy state this sequence was executed under.
            //! @param suiteType The suite from which the tests have been selected from.
            //! @param selectedTestRuns The target names of the selected test runs.
            //! @param draftedTestRuns The target names of the drafted test runs.
            //! @param selectedTestRunReport The report for the set of selected test runs.
            //! @param draftedTestRunReport The report for the set of drafted test runs.
            ImpactAnalysisSequenceReport(
                size_t maxConcurrency,
                AZStd::optional<AZStd::chrono::milliseconds> testTargetTimeout,
                AZStd::optional<AZStd::chrono::milliseconds> globalTimeout,
                ImpactAnalysisSequencePolicyState policyState,
                SuiteType suiteType,
                TestRunSelection selectedTestRuns,
                AZStd::vector<AZStd::string> discardedTestRuns,
                AZStd::vector<AZStd::string> draftedTestRuns,
                TestRunReport&& selectedTestRunReport,
                TestRunReport&& draftedTestRunReport);

            ImpactAnalysisSequenceReport(DraftingSequenceReportBase&& report, AZStd::vector<AZStd::string> discardedTestRuns);

            //! Returns the test runs discarded from running in the sequence.
            const AZStd::vector<AZStd::string>& GetDiscardedTestRuns() const;
        private:
            AZStd::vector<AZStd::string> m_discardedTestRuns;
        };

        //! Report detailing an impact analysis sequence of selected, discarded and drafted test runs.
        class SafeImpactAnalysisSequenceReport
            : public DraftingSequenceReportBase<SequenceReportType::SafeImpactAnalysisSequence, SafeImpactAnalysisSequencePolicyState>
        {
        public:
            //! Constructs the report for a sequence of selected, discarded and drafted test runs.
            //! @param maxConcurrency The maximum number of concurrent test targets in flight at any given time.
            //! @param testTargetTimeout The maximum duration individual test targets may be in flight for (infinite if empty).
            //! @param globalTimeout The maximum duration the entire test sequence may run for (infinite if empty).
            //! @param policyState The policy state this sequence was executed under.
            //! @param suiteType The suite from which the tests have been selected from.
            //! @param selectedTestRuns The target names of the selected test runs.
            //! @param discardedTestRuns The target names of the discarded test runs.
            //! @param draftedTestRuns The target names of the drafted test runs.
            //! @param selectedTestRunReport The report for the set of selected test runs.
            //! @param discardedTestRunReport The report for the set of discarded test runs.
            //! @param draftedTestRunReport The report for the set of drafted test runs.
            SafeImpactAnalysisSequenceReport(
                size_t maxConcurrency,
                AZStd::optional<AZStd::chrono::milliseconds> testTargetTimeout,
                AZStd::optional<AZStd::chrono::milliseconds> globalTimeout,
                SafeImpactAnalysisSequencePolicyState policyState,
                SuiteType suiteType,
                TestRunSelection selectedTestRuns,
                TestRunSelection discardedTestRuns,
                AZStd::vector<AZStd::string> draftedTestRuns,
                TestRunReport&& selectedTestRunReport,
                TestRunReport&& discardedTestRunReport,
                TestRunReport&& draftedTestRunReport);

            SafeImpactAnalysisSequenceReport(
                DraftingSequenceReportBase&& report, TestRunSelection discardedTestRuns, TestRunReport&& discardedTestRunReport);

            // SequenceReport overrides ...
            AZStd::chrono::milliseconds GetDuration() const override;
            TestSequenceResult GetResult() const override;
            size_t GetTotalNumTestRuns() const override;
            size_t GetTotalNumPassingTests() const override;
            size_t GetTotalNumFailingTests() const override;
            size_t GetTotalNumDisabledTests() const override;
            size_t GetTotalNumPassingTestRuns() const override;
            size_t GetTotalNumFailingTestRuns() const override;
            size_t GetTotalNumExecutionFailureTestRuns() const override;
            size_t GetTotalNumTimedOutTestRuns() const override;
            size_t GetTotalNumUnexecutedTestRuns() const override;

            // ImpactAnalysisSequenceReport overrides ...
            const TestRunSelection GetDiscardedTestRuns() const;

            //! Returns the report for the discarded test runs.
            TestRunReport GetDiscardedTestRunReport() const;

        private:
            TestRunSelection m_discardedTestRuns;
            TestRunReport m_discardedTestRunReport;
        };
    } // namespace Client
} // namespace TestImpact
