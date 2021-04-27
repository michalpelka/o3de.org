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

#include <Atom/RHI/DeviceObject.h>
#include <Atom/RHI.Reflect/AttachmentEnums.h>
#include <Atom/RHI.Reflect/Limits.h>
#include <Atom/RHI/ObjectPool.h>
#include <AzCore/std/containers/list.h>
#include <AzCore/std/parallel/mutex.h>
#include <RHI/CommandList.h>

namespace AZ
{
    namespace Vulkan
    {
        class CommandBuffer;
        class Device;

        class CommandPool final
            : public RHI::DeviceObject 
        {
            using Base = RHI::DeviceObject;

        public:
            AZ_CLASS_ALLOCATOR(CommandPool, AZ::SystemAllocator, 0);
            AZ_RTTI(CommandPool, "167326E7-5B9C-48B6-A792-79270C368100", Base);

            struct Descriptor
            {
                Device* m_device = nullptr;
                uint32_t m_queueFamilyIndex = 0;
            };

            static RHI::Ptr<CommandPool> Create();
            RHI::ResultCode Init(const Descriptor& descriptor);
            ~CommandPool() = default;
            VkCommandPool GetNativeCommandPool() const;
            RHI::Ptr<CommandList> AllocateCommandList(VkCommandBufferLevel level);
            const Descriptor& GetDescriptor() const;

            void Reset();
            //////////////////////////////////////////////////////////////////////////
            // RHI::DeviceObject
            void Shutdown() override;
            //////////////////////////////////////////////////////////////////////////

        private:
            CommandPool() = default;

            //////////////////////////////////////////////////////////////////////////
            // RHI::Object
            void SetNameInternal(const AZStd::string_view& name) override;
            //////////////////////////////////////////////////////////////////////////

            RHI::ResultCode BuildNativeCommandPool();

            VkCommandPool m_nativeCommandPool = VK_NULL_HANDLE;
            Descriptor m_descriptor;
            AZStd::vector<RHI::Ptr<CommandList>> m_commandLists;
            AZStd::vector<RHI::Ptr<CommandList>> m_freeCommandLists;
        };        
    }
}
