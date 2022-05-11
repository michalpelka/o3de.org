/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzToolsFramework/UI/DocumentPropertyEditor/PropertyEditorToolsSystem.h>

namespace AzToolsFramework
{
    PropertyEditorToolsSystem::PropertyEditorToolsSystem()
    {
        AZ::Interface<PropertyEditorToolsSystemInterface>::Register(this);
    }

    PropertyEditorToolsSystem::~PropertyEditorToolsSystem()
    {
        AZ::Interface<PropertyEditorToolsSystemInterface>::Unregister(this);
    }

    PropertyEditorToolsSystem::PropertyHandlerId PropertyEditorToolsSystem::GetPropertyHandlerForNode(const AZ::Dom::Value node)
    {
        using AZ::DocumentPropertyEditor::GetNodeName;
        using AZ::DocumentPropertyEditor::Nodes::PropertyEditor;

        if (!node.IsNode() || node.GetNodeName() != GetNodeName<PropertyEditor>())
        {
            AZ_Assert(false, "Attempted to look up a property handler for a value that is not a PropertyEditor node");
            return InvalidHandlerId;
        }

        AZStd::string_view typeName = PropertyEditor::Type.ExtractFromDomNode(node).value_or("");
        if (typeName.empty())
        {
            return InvalidHandlerId;
        }

        auto handlerBucketIt = m_registeredHandlers.find(AZ::Name(typeName));
        if (handlerBucketIt == m_registeredHandlers.end())
        {
            return InvalidHandlerId;
        }

        for (auto handlerIt = handlerBucketIt->second.begin(); handlerIt != handlerBucketIt->second.end(); ++handlerIt)
        {
            if (handlerIt->get()->m_shouldHandleNode(node))
            {
                return handlerIt->get();
            }
        }

        return InvalidHandlerId;
    }

    PropertyEditorToolsSystem::PropertyHandlerInstance PropertyEditorToolsSystem::CreateHandlerInstance(PropertyHandlerId handlerId)
    {
        if (handlerId == InvalidHandlerId)
        {
            AZ_Assert(false, "Attempted to instantiate an invalid property handler");
            return {};
        }

        return handlerId->m_factory();
    }

    PropertyEditorToolsSystem::PropertyHandlerId PropertyEditorToolsSystem::RegisterHandler(HandlerData handlerData)
    {
        // Insert a heap allocated holder for the data (heap allocated so that its address can be used as a persistent HandlerId)
        auto storedHandlerData = AZStd::make_unique<HandlerData>(AZStd::move(handlerData));
        PropertyHandlerId newId = storedHandlerData.get();
        // Get or create a bucket for handlers with this handler's name
        m_registeredHandlers[AZ::Name(handlerData.m_name)].push_back(AZStd::move(storedHandlerData));
        return newId;
    }

    void PropertyEditorToolsSystem::UnregisterHandler(PropertyHandlerId handlerId)
    {
        if (handlerId == InvalidHandlerId)
        {
            AZ_Assert(false, "Attempted to unregister an invalid handler ID");
            return;
        }

        auto handlerBucketIt = m_registeredHandlers.find(AZ::Name(handlerId->m_name));
        if (handlerBucketIt == m_registeredHandlers.end())
        {
            AZ_Warning("DPE", false, "UnregisterHandler: the specified handler was not found");
        }

        auto& handlerBucket = handlerBucketIt->second;
        for (auto handlerIt = handlerBucket.begin(); handlerIt != handlerBucket.end(); ++handlerIt)
        {
            if (handlerIt->get() == handlerId)
            {
                auto endIt = handlerBucket.end() - 1;
                if (handlerIt != endIt)
                {
                    AZStd::swap(*handlerIt, *endIt);
                }
                handlerBucket.erase(endIt);
                return;
            }
        }

        AZ_Warning("DPE", false, "UnregisterHandler: the specified handler was not found");
    }
} // namespace AzToolsFramework
