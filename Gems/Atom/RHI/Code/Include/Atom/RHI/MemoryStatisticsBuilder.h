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

#include <Atom/RHI.Reflect/MemoryStatistics.h>
#include <AzCore/std/containers/vector.h>
#include <AzCore/std/containers/unordered_map.h>

namespace AZ
{
    namespace RHI
    {
        enum class MemoryStatisticsReportFlags : uint32_t
        {
            /// Includes pool and platform heap usage. Does not enumerate individual resources.
            Basic,

            /// Includes pool and platform heap usage. Enumerates individual resources for each pool.
            Detail
        };

        class MemoryStatisticsBuilder
        {
        public:
            // Begins a new statistics building pass. The MemoryStatistics struct is cleared and intermediate
            // data is filled until End is called.
            void Begin(MemoryStatistics& memoryStatistics, MemoryStatisticsReportFlags reportFlags);

            // Returns the report flags passed to the builder.
            MemoryStatisticsReportFlags GetReportFlags() const;

            /**
             * Adds a new heap info and returns it. The user can fill out the heap data structure.
             */
            MemoryStatistics::Heap* AddHeap();

            /**
             * Adds a new pool info and returns it. The user can fill out the pool data structure.
             */
            MemoryStatistics::Pool* BeginPool();

            /**
             * Adds a new buffer info to the current pool. This must be called within a BeginPool() / EndPool() scope.
             */
            MemoryStatistics::Buffer* AddBuffer();

            /**
             * Adds a new image info to the current pool. This must be called within a BeginPool() / EndPool() scope.
             */
            MemoryStatistics::Image* AddImage();

            void EndPool();

            void End();

        private:
            MemoryStatisticsReportFlags m_reportFlags = MemoryStatisticsReportFlags::Basic;
            MemoryStatistics::Pool* m_currentPool = nullptr;
            MemoryStatistics* m_statistics = nullptr;
        };
    }
}
