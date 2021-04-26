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
#include "Atom_RHI_Vulkan_precompiled.h"
#include <RHI/Conversion.h>
#include <RHI/Device.h>
#include <RHI/Semaphore.h>

namespace AZ
{
    namespace Vulkan
    {
        RHI::Ptr<Semaphore> Semaphore::Create()
        {
            return aznew Semaphore();
        }

        RHI::ResultCode Semaphore::Init(Device& device)
        {
            Base::Init(device);

            VkSemaphoreCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
            createInfo.pNext = 0;
            createInfo.flags = 0;

            const VkResult result = vkCreateSemaphore(device.GetNativeDevice(), &createInfo, nullptr, &m_nativeSemaphore);
            AssertSuccess(result);

            RETURN_RESULT_IF_UNSUCCESSFUL(ConvertResult(result));

            SetName(GetName());
            return RHI::ResultCode::Success;
        }

        void Semaphore::SignalEvent()
        {
            m_signalEvent.Signal();
        }

        void Semaphore::WaitEvent() const
        {
            m_signalEvent.Wait();
        }

        void Semaphore::ResetSignalEvent()
        {
            m_signalEvent.SetValue(false);
        }

        void Semaphore::SetRecycleValue(bool canRecycle)
        {
            m_recyclable = canRecycle;
        }

        bool Semaphore::GetRecycleValue() const
        {
            return m_recyclable;
        }

        VkSemaphore Semaphore::GetNativeSemaphore() const
        {
            return m_nativeSemaphore;
        }

        void Semaphore::SetNameInternal(const AZStd::string_view& name)
        {
            if (IsInitialized() && !name.empty())
            {
                Debug::SetNameToObject(reinterpret_cast<uint64_t>(m_nativeSemaphore), name.data(), VK_OBJECT_TYPE_SEMAPHORE, static_cast<Device&>(GetDevice()));
            }
        }

        void Semaphore::Shutdown()
        {
            if (m_nativeSemaphore != VK_NULL_HANDLE)
            {
                auto& device = static_cast<Device&>(GetDevice());
                vkDestroySemaphore(device.GetNativeDevice(), m_nativeSemaphore, nullptr);
                m_nativeSemaphore = VK_NULL_HANDLE;
            }
            // Signal any pending threads.
            m_signalEvent.Signal();
            Base::Shutdown();
        }
    }
}
