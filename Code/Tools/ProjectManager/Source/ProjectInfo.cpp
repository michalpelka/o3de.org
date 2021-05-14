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

#include "ProjectInfo.h"

namespace O3DE::ProjectManager
{
    ProjectInfo::ProjectInfo(const QString& path, const QString& projectName, const QString& productName, const AZ::Uuid projectId,
        const QString& imagePath, const QString& backgroundImagePath, bool isNew)
        : m_path(path)
        , m_projectName(projectName)
        , m_productName(productName)
        , m_projectId(projectId)
        , m_imagePath(imagePath)
        , m_backgroundImagePath(backgroundImagePath)
        , m_isNew(isNew)
    {
    }
} // namespace O3DE::ProjectManager
