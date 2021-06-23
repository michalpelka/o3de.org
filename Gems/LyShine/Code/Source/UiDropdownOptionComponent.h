/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include "UiInteractableComponent.h"

#include <LyShine/Bus/UiDropdownOptionBus.h>
#include <LyShine/Bus/UiInitializationBus.h>
#include <LyShine/Bus/UiInteractableBus.h>
#include <LyShine/UiComponentTypes.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
class UiDropdownOptionComponent
    : public AZ::Component
    , public UiDropdownOptionBus::Handler
    , public UiInitializationBus::Handler
    , public UiInteractableNotificationBus::Handler
{
public: // member functions

    AZ_COMPONENT(UiDropdownOptionComponent, LyShine::UiDropdownOptionComponentUuid, AZ::Component);

    UiDropdownOptionComponent();
    ~UiDropdownOptionComponent() override;

    // UiDropdownOptionInterface
    AZ::EntityId GetOwningDropdown() override;
    void SetOwningDropdown(AZ::EntityId owningDropdown) override;
    AZ::EntityId GetTextElement() override;
    void SetTextElement(AZ::EntityId textElement) override;
    AZ::EntityId GetIconElement() override;
    void SetIconElement(AZ::EntityId iconElement) override;
    // ~UiDropdownOptionInterface

    // UiInitializationInterface
    void InGamePostActivate() override;
    // ~UiInitializationInterface

    // UiInteractableNotificationBus
    void OnReleased() override;
    // ~UiInteractableNotificationBus

protected: // member functions

    // AZ::Component
    void Activate() override;
    void Deactivate() override;
    // ~AZ::Component

    static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC("UiDropdownOptionService"));
    }

    static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC("UiDropdownOptionService"));
    }

    static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        required.push_back(AZ_CRC("UiElementService", 0x3dca7ad4));
        required.push_back(AZ_CRC("UiTransformService", 0x3a838e34));
        required.push_back(AZ_CRC("UiInteractableService", 0x1d474c98));
    }

    static void Reflect(AZ::ReflectContext* context);

private: // member functions

    AZ_DISABLE_COPY_MOVE(UiDropdownOptionComponent);

    using EntityComboBoxVec = AZStd::vector< AZStd::pair< AZ::EntityId, AZStd::string > >;
    EntityComboBoxVec PopulateDropdownsEntityList();
    EntityComboBoxVec PopulateChildEntityList();

private: // data

    AZ::EntityId m_owningDropdown;
    AZ::EntityId m_textElement;
    AZ::EntityId m_iconElement;
};
