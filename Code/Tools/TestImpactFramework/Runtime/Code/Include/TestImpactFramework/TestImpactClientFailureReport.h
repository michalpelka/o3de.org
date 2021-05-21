/*
 * All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
 * its licensors.
 *
 * For complete copyright and license terms please see the LICENSE at the root of this
 * distribution (the "License"). All use of this software is governed by the License,
 * or, if provided, by the license below or the license accompanying this file. Do not
 * remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *
 */

#pragma once

#include <AzCore/std/string/string.h>
#include <AzCore/std/containers/vector.h>

namespace TestImpact
{
    namespace Client
    {
        //! Represents a test target that failed, either due to failing to execute, completing in an abnormal state or completing with failing tests.
        class TargetFailure
        {
        public:
            TargetFailure(const AZStd::string& targetName);

            //! Returns the name of the test target this failure pertains to.
            const AZStd::string& GetTargetName() const;
        private:
            AZStd::string m_targetName;
        };

        //! Represents a test target that failed to execute.
        class ExecutionFailure
            : public TargetFailure
        {
        public:
            ExecutionFailure(const AZStd::string& targetName, const AZStd::string& command);

            //! Returns the command string used to execute this test target.
            const AZStd::string& GetCommandString() const;
        private:
            AZStd::string m_commandString;
        };

        //! Represents a test target that terminated abnormally.
        class LauncherFailure
            : public ExecutionFailure
        {
        public:
            LauncherFailure(const AZStd::string& targetName, const AZStd::string& command, int returnCode);

            //! The return code of the test target that terminated abnormally.
            int GetReturnCode() const;
        private:
            int m_returnCode;
        };

        //! Represents an individual test of a test target that failed.
        class TestFailure
        {
        public:
            TestFailure(const AZStd::string& testName, const AZStd::string& errorMessage);

            //! Returns the name of the test that failed.
            const AZStd::string& GetName() const;

            //! Returns the error message of the test that failed.
            const AZStd::string& GetErrorMessage() const;

        private:
            AZStd::string m_name;
            AZStd::string m_errorMessage;
        };

        //! Represents a collection of tests that failed.
        //! @note Only the failing tests are included in the collection.
        class TestCaseFailure
        {
        public:
            TestCaseFailure(const AZStd::string& testCaseName, AZStd::vector<TestFailure>&& testFailures);

            //! Returns the name of the test case containing the failing tests.
            const AZStd::string& GetName() const;

            //! Returns the collection of tests in this test case that failed.
            const AZStd::vector<TestFailure>& GetTestFailures() const;

        private:
            AZStd::string m_name;
            AZStd::vector<TestFailure> m_testFailures;
        };

        //! Represents a test target that launched successfully but contains failing tests.
        class TestRunFailure
            : public TargetFailure
        {
        public:
            TestRunFailure(const AZStd::string& targetName, AZStd::vector<TestCaseFailure>&& testFailures);

            //! Returns the total number of failing tests in this run.
            size_t GetNumTestFailures() const;

            //! Returns the test cases in this run containing failing tests.
            const AZStd::vector<TestCaseFailure>& GetTestCaseFailures() const;

        private:
            AZStd::vector<TestCaseFailure> m_testCaseFailures;
        };

        //! Base class for reporting failing test sequences.
        class SequenceFailure
        {
        public:
            SequenceFailure(
                AZStd::vector<ExecutionFailure>&& executionFailures,
                AZStd::vector<LauncherFailure>&& launcherFailures,
                AZStd::vector<TargetFailure>&& unexecutedTests);

            //! Returns the test targets in this sequence that failed to execute.
            const AZStd::vector<ExecutionFailure>& GetExecutionFailures() const;

            //! Returns the test targets in this sequence that terminated abnormally.
            const AZStd::vector<LauncherFailure>& GetLauncherFailures() const;

            //! Returns the test targets in this sequence that were not executed due to the sequence terminating prematurely.
            const AZStd::vector<TargetFailure>& GetUnexecutedTest() const;

        private:
            AZStd::vector<ExecutionFailure> m_executionFailures;
            AZStd::vector<LauncherFailure> m_launcherFailures;
            AZStd::vector<TargetFailure> m_unexecutedTests;
        };

        //! Represents the report for a failed regular test sequence run without test impact analysis.
        class RegularSequenceFailure
            : public SequenceFailure
        {
        public:
            RegularSequenceFailure(
                AZStd::vector<ExecutionFailure>&& executionFailures,
                AZStd::vector<LauncherFailure>&& launcherFailures,
                AZStd::vector<TestRunFailure>&& testRunFailures,
                AZStd::vector<TargetFailure>&& unexecutedTests);

            //! Returns the test targets that contain failing tests.
            const AZStd::vector<TestRunFailure>& GetTestRunFailures() const;

        private:
            AZStd::vector<TestRunFailure> m_testRunFailures;
        };

        //! Represents the report for a failed test sequence run with test impact analysis.
        class ImpactAnalysisSequenceFailure
            : public SequenceFailure
        {
        public:
            ImpactAnalysisSequenceFailure(
                AZStd::vector<ExecutionFailure>&& executionFailures,
                AZStd::vector<LauncherFailure>&& launcherFailures,
                AZStd::vector<TestRunFailure>&& selectedTestRunFailures,
                AZStd::vector<TestRunFailure>&& discardedTestRunFailures,
                AZStd::vector<TargetFailure>&& unexecutedTests);

            //! Returns the test targets that were selected to run but contain failing tests.
            const AZStd::vector<TestRunFailure> GetSelectedTestRunFailures() const;

            //! Returns the test targets that were not selected but still run but contain failing tests.
            const AZStd::vector<TestRunFailure> GetDiscardedTestRunFailures() const;

        private:
            AZStd::vector<TestRunFailure> m_selectedTestRunFailures;
            AZStd::vector<TestRunFailure> m_discardedTestRunFailures;
        };
    } // namespace Client
} // namespace TestImpact
