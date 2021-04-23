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

#include <AzCore/EBus/EBus.h>
#include <AzToolsFramework/Debug/TraceContext.h>
#include <SceneAPI/SceneUI/RowWidgets/ManifestNameHandler.h>

namespace AZ
{
    namespace SceneAPI
    {
        namespace SceneUI
        {
            AZ_CLASS_ALLOCATOR_IMPL(ManifestNameHandler, SystemAllocator, 0)

            ManifestNameHandler* ManifestNameHandler::s_instance = nullptr;

            QWidget* ManifestNameHandler::CreateGUI(QWidget* parent)
            {
                ManifestNameWidget* instance = aznew ManifestNameWidget(parent);
                connect(instance, &ManifestNameWidget::valueChanged, this,
                    [instance]()
                    {
                        EBUS_EVENT(AzToolsFramework::PropertyEditorGUIMessages::Bus, RequestWrite, instance);
                    });
                return instance;
            }

            u32 ManifestNameHandler::GetHandlerName() const
            {
                return AZ_CRC("ManifestName", 0x5215b349);
            }

            bool ManifestNameHandler::AutoDelete() const
            {
                return false;
            }

            void ManifestNameHandler::ConsumeAttribute(ManifestNameWidget* widget, u32 attrib,
                AzToolsFramework::PropertyAttributeReader* attrValue, const char* debugName)
            {
                AZ_TraceContext("Attribute name", debugName);

                if (attrib == AZ_CRC("FilterType", 0x2661cf01))
                {
                    ConsumeFilterTypeAttribute(widget, attrValue);
                }
            }

            void ManifestNameHandler::WriteGUIValuesIntoProperty(size_t /*index*/, ManifestNameWidget* GUI,
                property_t& instance, AzToolsFramework::InstanceDataNode* /*node*/)
            {
                instance = static_cast<property_t>(GUI->GetName());
            }

            bool ManifestNameHandler::ReadValuesIntoGUI(size_t /*index*/, ManifestNameWidget* GUI, const property_t& instance,
                AzToolsFramework::InstanceDataNode* /*node*/)
            {
                GUI->SetName(instance);
                return false;
            }

            void ManifestNameHandler::Register()
            {
                if (!s_instance)
                {
                    s_instance = aznew ManifestNameHandler();
                    EBUS_EVENT(AzToolsFramework::PropertyTypeRegistrationMessages::Bus, RegisterPropertyType, s_instance);
                }
            }

            void ManifestNameHandler::Unregister()
            {
                if (s_instance)
                {
                    EBUS_EVENT(AzToolsFramework::PropertyTypeRegistrationMessages::Bus, UnregisterPropertyType, s_instance);
                    delete s_instance;
                    s_instance = nullptr;
                }
            }

            void ManifestNameHandler::ConsumeFilterTypeAttribute(ManifestNameWidget* widget,
                AzToolsFramework::PropertyAttributeReader* attrValue)
            {
                Uuid filterType;
                if (attrValue->Read<Uuid>(filterType))
                {
                    widget->SetFilterType(filterType);
                }
                else
                {
                    AZ_Assert(false, "Failed to read uuid from 'FilterType' attribute.");
                }
            }
        } // SceneUI
    } // SceneAPI
} // AZ

#include <RowWidgets/moc_ManifestNameHandler.cpp>
