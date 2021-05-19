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

#include <TestImpactFramework/TestImpactException.h>
#include <TestImpactFramework/TestImpactRuntime.h>

#include <AzCore/IO/SystemFile.h>
#include <AzCore/std/containers/vector.h>
#include <AzCore/std/string/string.h>

#pragma once

namespace TestImpact
{
    //! Attempts to read the contents of the specified file into a string.
    //! @tparam ExceptionType The exception type to throw upon failure.
    //! @param path The path to the file to read the contents of.
    //! @returns The contents of the file.
    template<typename ExceptionType>
    AZStd::string ReadFileContents(const RepoPath& path)
    {
        const auto fileSize = AZ::IO::SystemFile::Length(path.c_str());
        AZ_TestImpact_Eval(fileSize > 0, ExceptionType, AZStd::string::format("File %s does not exist", path.c_str()));

        AZStd::vector<char> buffer(fileSize + 1);
        buffer[fileSize] = '\0';
        AZ_TestImpact_Eval(AZ::IO::SystemFile::Read(path.c_str(), buffer.data()), ExceptionType, AZStd::string::format("Could not read contents of file %s", path.c_str()));

        return AZStd::string(buffer.begin(), buffer.end());
    }

    //! Attempts to write the contents of the specified string to a file.
    //! @tparam ExceptionType The exception type to throw upon failure.
    //! @param contents The contents to write to the file.
    //! @param path The path to the file to write the contents to.
    template<typename ExceptionType>
    void WriteFileContents(const AZStd::string& contents, const RepoPath& path)
    {
        AZ::IO::SystemFile file;
        const AZStd::vector<char> bytes(contents.begin(), contents.end());
        AZ_TestImpact_Eval(
            file.Open(path.c_str(),
                AZ::IO::SystemFile::SF_OPEN_CREATE | AZ::IO::SystemFile::SF_OPEN_CREATE_PATH | AZ::IO::SystemFile::SF_OPEN_WRITE_ONLY),
            ExceptionType,
            AZStd::string::format("Couldn't open file %s for writing", path.c_str()));

        AZ_TestImpact_Eval(file.Write(bytes.data(), bytes.size()), ExceptionType, AZStd::string::format("Couldn't write contents for file %s", path.c_str()));

        return;
    }
} // namespace TestImpact
