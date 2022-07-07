/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */


#include "MultiplayerConnectionViewportMessageSystemComponent.h"
#include <Atom/RPI.Public/ViewportContextBus.h>
#include <Atom/RPI.Public/ViewportContext.h>
#include <AzCore/Console/IConsole.h>
#include <AzFramework/Entity/EntityDebugDisplayBus.h>
#include <AzNetworking/Framework/INetworking.h>
#include <Multiplayer/IMultiplayerSpawner.h>
#include <Multiplayer/MultiplayerConstants.h>

namespace Multiplayer
{
    constexpr float defaultConnectionMessageFontSize = 0.7f;
    const AZ::Vector2 viewportConnectionTopLeftBorderPadding(40.0f, 22.0f);

    AZ_CVAR_SCOPED(bool, cl_viewportConnectionStatus, true, nullptr, AZ::ConsoleFunctorFlags::DontReplicate,
        "This will enable displaying connection status in the client's viewport while running multiplayer.");

    AZ_CVAR_SCOPED(float, cl_viewportConnectionMessageFontSize, defaultConnectionMessageFontSize, nullptr, AZ::ConsoleFunctorFlags::DontReplicate, 
        "The font size used for displaying updates on screen while the multiplayer editor is connecting to the server.");
    
    void MultiplayerConnectionViewportMessageSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (AZ::SerializeContext* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<MultiplayerConnectionViewportMessageSystemComponent, AZ::Component>()
                ->Version(1);
        }
    }
    
    MultiplayerConnectionViewportMessageSystemComponent::MultiplayerConnectionViewportMessageSystemComponent()
    {
        AZ::Interface<IMultiplayerConnectionViewportMessage>::Register(this);
    }

    MultiplayerConnectionViewportMessageSystemComponent::~MultiplayerConnectionViewportMessageSystemComponent()
    {
        AZ::Interface<IMultiplayerConnectionViewportMessage>::Unregister(this);
    }

    void MultiplayerConnectionViewportMessageSystemComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        required.push_back(AZ_CRC_CE("MultiplayerService"));
    }

    void MultiplayerConnectionViewportMessageSystemComponent::Activate()
    {
        AZ::TickBus::Handler::BusConnect();
    }

    void MultiplayerConnectionViewportMessageSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
    }

    void MultiplayerConnectionViewportMessageSystemComponent::OnTick(float, AZ::ScriptTimePoint)
    {
        if (!cl_viewportConnectionStatus)
        {
            return;
        }

        AZ::RPI::ViewportContextPtr viewport = AZ::RPI::ViewportContextRequests::Get()->GetDefaultViewportContext();
        if (!viewport)
        {
            return;
        }

        // Display the custom center viewport text
        if (!m_centerViewportDebugText.empty())
        {            
            AzFramework::WindowSize viewportSize = viewport->GetViewportSize();
            const float dpiScalingFactor = viewport->GetDpiScalingFactor();
            const float center_screenposition_x = 0.5f*viewportSize.m_width;
            const float center_screenposition_y = 0.5f*viewportSize.m_height;
            const float screenposition_title_y = center_screenposition_y-9;
            const float screenposition_debugtext_y = screenposition_title_y+18*dpiScalingFactor;

            AzFramework::DebugDisplayRequestBus::Broadcast(&AzFramework::DebugDisplayRequestBus::Events::SetColor, AZ::Colors::Yellow);
            AzFramework::DebugDisplayRequestBus::Broadcast(&AzFramework::DebugDisplayRequestBus::Events::Draw2dTextLabel, 
                center_screenposition_x / dpiScalingFactor, screenposition_title_y / dpiScalingFactor, cl_viewportConnectionMessageFontSize, "Multiplayer Editor", true);

            AzFramework::DebugDisplayRequestBus::Broadcast(&AzFramework::DebugDisplayRequestBus::Events::SetColor, AZ::Colors::White);
            AzFramework::DebugDisplayRequestBus::Broadcast(&AzFramework::DebugDisplayRequestBus::Events::Draw2dTextLabel, 
                center_screenposition_x / dpiScalingFactor, screenposition_debugtext_y / dpiScalingFactor, cl_viewportConnectionMessageFontSize, m_centerViewportDebugText.c_str(), true);
        }

        // Build the connection status string (just show client connected or disconnected status for now)
        const auto multiplayerSystemComponent = AZ::Interface<IMultiplayer>::Get();
        MultiplayerAgentType agentType = multiplayerSystemComponent->GetAgentType();        
        if (agentType != MultiplayerAgentType::Client)
        {
            return;
        }
        
        // Display the connection status to the top-left viewport
        if (AzNetworking::INetworkInterface* networkInterface = AZ::Interface<AzNetworking::INetworking>::Get()->RetrieveNetworkInterface(AZ::Name(MpNetworkInterfaceName)))
        {
            AzNetworking::IConnectionSet& connectionSet = networkInterface->GetConnectionSet();
            if (connectionSet.GetConnectionCount() > 0)
            {
                // Display the connection status (calling VisitConnections(), but there's only 1 since we're a client)
                auto displayConnectionStatus = [](AzNetworking::IConnection& connection)
                {
                    AZStd::string connectionStatusText = AZStd::string::format("Operating as multiplayer Client: %s", ToString(connection.GetConnectionState()).data());
                    AzFramework::DebugDisplayRequestBus::Broadcast(&AzFramework::DebugDisplayRequestBus::Events::SetColor, AZ::Colors::White);
                    AzFramework::DebugDisplayRequestBus::Broadcast(&AzFramework::DebugDisplayRequestBus::Events::Draw2dTextLabel, 
                        viewportConnectionTopLeftBorderPadding.GetX(), viewportConnectionTopLeftBorderPadding.GetY(), cl_viewportConnectionMessageFontSize, 
                        connectionStatusText.c_str(), false);
                };
                connectionSet.VisitConnections(displayConnectionStatus);
            }
            else
            {
                // If we're a client yet are lacking a connection then we've been unintentionally disconnected
                // Display a disconnect message in the viewport
                AzFramework::DebugDisplayRequestBus::Broadcast(&AzFramework::DebugDisplayRequestBus::Events::SetColor, AZ::Colors::Red);
                AzFramework::DebugDisplayRequestBus::Broadcast(&AzFramework::DebugDisplayRequestBus::Events::Draw2dTextLabel, 
                    viewportConnectionTopLeftBorderPadding.GetX(), viewportConnectionTopLeftBorderPadding.GetY(), cl_viewportConnectionMessageFontSize, 
                    "Multiplayer Client Disconnected!", false);
            }
        }
    }

    void MultiplayerConnectionViewportMessageSystemComponent::DisplayCenterViewportMessage(const char* text)
    {
        if (strlen(text) == 0)
        {
            StopCenterViewportDebugMessaging();
            return;
        }
        
        m_centerViewportDebugText = text;
    }
    
    void MultiplayerConnectionViewportMessageSystemComponent::StopCenterViewportDebugMessaging()
    {
        m_centerViewportDebugText = "";
    }
}
