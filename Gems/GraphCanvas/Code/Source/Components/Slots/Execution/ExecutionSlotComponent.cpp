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
#include "precompiled.h"

#include <Components/Slots/Execution/ExecutionSlotComponent.h>

#include <Components/Connections/ConnectionComponent.h>
#include <Components/Slots/SlotConnectionFilterComponent.h>
#include <Components/Slots/Execution/ExecutionSlotLayoutComponent.h>
#include <Components/StylingComponent.h>
#include <GraphCanvas/Components/Connections/ConnectionFilters/ConnectionFilters.h>

namespace GraphCanvas
{
    ///////////////////////////
    // ExecutionSlotComponent
    ///////////////////////////

    void ExecutionSlotComponent::Reflect(AZ::ReflectContext* reflectContext)
    {
        AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(reflectContext);
        if (serializeContext)
        {
            serializeContext->Class<ExecutionSlotComponent, SlotComponent>()
                ->Version(1)
            ;
        }
    }

    AZ::Entity* ExecutionSlotComponent::CreateExecutionSlot(const AZ::EntityId& nodeId, const SlotConfiguration& slotConfiguration)
    {
        AZ::Entity* entity = SlotComponent::CreateCoreSlotEntity();

        ExecutionSlotComponent* executionSlot = entity->CreateComponent<ExecutionSlotComponent>(slotConfiguration);

        entity->CreateComponent<ExecutionSlotLayoutComponent>();

        entity->CreateComponent<StylingComponent>(Styling::Elements::ExecutionSlot, nodeId);

        SlotConnectionFilterComponent* connectionFilter = entity->CreateComponent<SlotConnectionFilterComponent>();

        SlotTypeFilter* slotTypeFilter = aznew SlotTypeFilter(ConnectionFilterType::Include);
        slotTypeFilter->AddSlotType(SlotTypes::ExecutionSlot);

        connectionFilter->AddFilter(slotTypeFilter);

        ConnectionTypeFilter* connectionTypeFilter = aznew ConnectionTypeFilter(ConnectionFilterType::Include);

        switch (executionSlot->GetConnectionType())
        {
            case ConnectionType::CT_Input:
                connectionTypeFilter->AddConnectionType(CT_Output);
                break;
            case ConnectionType::CT_Output:
                connectionTypeFilter->AddConnectionType(CT_Input);
                break;
            default:
                break;
        };

        connectionFilter->AddFilter(connectionTypeFilter);
        return entity;
    }
    
    ExecutionSlotComponent::ExecutionSlotComponent()
        : SlotComponent(SlotTypes::ExecutionSlot)
    {
        if (m_slotConfiguration.m_slotGroup == SlotGroups::Invalid)
        {
            m_slotConfiguration.m_slotGroup = SlotGroups::ExecutionGroup;
        }
    }
    
    ExecutionSlotComponent::ExecutionSlotComponent(const SlotConfiguration& slotConfiguration)
        : SlotComponent(SlotTypes::ExecutionSlot, slotConfiguration)
    {
        if (m_slotConfiguration.m_slotGroup == SlotGroups::Invalid)
        {
            m_slotConfiguration.m_slotGroup = SlotGroups::ExecutionGroup;
        }
    }

    ExecutionSlotComponent::~ExecutionSlotComponent()
    {
    }

    SlotConfiguration* ExecutionSlotComponent::CloneSlotConfiguration() const
    {
        ExecutionSlotConfiguration* executionConfiguration = aznew ExecutionSlotConfiguration();

        PopulateSlotConfiguration((*executionConfiguration));

        return executionConfiguration;
    }

    AZ::Entity* ExecutionSlotComponent::ConstructConnectionEntity(const Endpoint& sourceEndpoint, const Endpoint& targetEndpoint, bool createModelConnection)
    {    
        const AZStd::string k_connectionSubStyle = ".logicFlow";

        return ConnectionComponent::CreateGeneralConnection(sourceEndpoint, targetEndpoint, createModelConnection, k_connectionSubStyle);
    }
}
