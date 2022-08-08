/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <TestImpactFramework/TestImpactConfiguration.h>
#include <TestImpactFramework/TestImpactUtils.h>

#include <Artifact/Factory/TestImpactModuleCoverageFactory.h>
#include <Artifact/Factory/TestImpactTestRunSuiteFactory.h>
#include <TestRunner/Common/TestImpactTestRunnerException.h>
#include <TestRunner/Common/TestImpactTestRunnerWithCoverage.h>
#include <TestRunner/Common/Job/TestImpactTestRunWithCoverageJobData.h>
#include <TestRunner/Common/Run/TestImpactTestCoverage.h>

namespace TestImpact
{
    class PythonTestRunnerBase
        : public TestRunnerWithCoverage<TestRunWithCoverageJobData, TestCoverage>
    {
    public:
        PythonTestRunnerBase(const ArtifactDir& artifactDir);

    protected:
        JobPayloadOutcome PayloadExtractor(const JobInfo& jobData, const JobMeta& jobMeta) override;

        ArtifactDir m_artifactDir;
    };
} // namespace TestImpact
