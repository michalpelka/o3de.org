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

#include <DefaultClientIdProvider.h>

#include <AzCore/IO/FileIO.h>
#include <AzCore/IO/SystemFile.h>
#include <AzCore/IO/Path/Path.h>
#include <AzFramework/FileFunc/FileFunc.h>

namespace AWSMetrics
{
    AZStd::unique_ptr<IdentityProvider> IdentityProvider::CreateIdentityProvider()
    {
        return AZStd::make_unique<DefaultClientIdProvider>(GetEngineVersion());
    }

    AZStd::string IdentityProvider::GetEngineVersion()
    {
        static constexpr const char* EngineConfigFilePath = "@root@/engine.json";
        static constexpr const char* EngineVersionJsonKey = "O3DEVersion";

        AZ::IO::FileIOBase* fileIO = AZ::IO::FileIOBase::GetDirectInstance();
        if (!fileIO)
        {
            AZ_Error("AWSMetrics", false, "No FileIoBase Instance");
            return "";
        }

        char resolvedPath[AZ_MAX_PATH_LEN] = { 0 };
        if (!fileIO->ResolvePath(EngineConfigFilePath, resolvedPath, AZ_MAX_PATH_LEN))
        {
            AZ_Error("AWSMetrics", false, "Failed to resolve the engine config file directory");
            return "";
        }

        AZ::IO::Path configIoPath(resolvedPath);
        auto readOutcome = AzFramework::FileFunc::ReadJsonFile(configIoPath, fileIO);
        if (!readOutcome.IsSuccess())
        {
            AZ_Error("AWSMetrics", false, readOutcome.GetError().c_str());
            return "";
        }

        rapidjson_ly::Document& jsonDoc = readOutcome.GetValue();
        auto memberIt = jsonDoc.FindMember(EngineVersionJsonKey);
        if (memberIt != jsonDoc.MemberEnd())
        {
            return memberIt->value.GetString();
        }

        return "";
    }
}
