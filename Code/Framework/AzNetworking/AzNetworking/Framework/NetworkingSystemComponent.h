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

#include <AzCore/Name/Name.h>
#include <AzNetworking/Framework/ICompressor.h>
#include <AzNetworking/Framework/INetworking.h>
#include <AzNetworking/Framework/INetworkInterface.h>
#include <AzNetworking/TcpTransport/TcpListenThread.h>
#include <AzNetworking/UdpTransport/UdpReaderThread.h>
#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <AzCore/Console/IConsole.h>
#include <AzCore/Console/ILogger.h>
#include <AzCore/std/containers/unordered_map.h>

namespace AzNetworking
{
    //! Implementation of the networking system interface.
    //! This class creates and manages the set of network interfaces used by the application.
    class NetworkingSystemComponent final
        : public AZ::Component
        , public AZ::TickBus::Handler
        , public INetworking
    {
    public:
        AZ_COMPONENT(NetworkingSystemComponent, "{29914D25-5E8F-49C9-8C57-5125ABD3D489}");

        static void Reflect(AZ::ReflectContext* context);
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);

        NetworkingSystemComponent();
        ~NetworkingSystemComponent() override;

        //! AZ::Component overrides.
        //! @{
        void Activate() override;
        void Deactivate() override;
        //! @}

        //! AZ::TickBus::Handler overrides.
        //! @{
        void OnTick(float deltaTime, AZ::ScriptTimePoint time) override;
        int GetTickOrder() override;
        //! @}

        //! INetworking overrides.
        //! @{
        INetworkInterface* CreateNetworkInterface(AZ::Name name, ProtocolType protocolType, TrustZone trustZone, IConnectionListener& listener) override;
        INetworkInterface* RetrieveNetworkInterface(AZ::Name name) override;
        bool DestroyNetworkInterface(AZ::Name name) override;
        void RegisterCompressorFactory(ICompressorFactory* factory) override;
        AZStd::unique_ptr<ICompressor> CreateCompressor(AZ::Name name) override;
        bool UnregisterCompressorFactory(AZ::Name name) override;
        const NetworkInterfaces& GetNetworkInterfaces() const override;
        uint32_t GetTcpListenThreadSocketCount() const override;
        AZ::TimeMs GetTcpListenThreadUpdateTime() const override;
        uint32_t GetUdpReaderThreadSocketCount() const override;
        AZ::TimeMs GetUdpReaderThreadUpdateTime() const override;
        //! @}

        //! Console commands.
        //! @{
        void DumpStats(const AZ::ConsoleCommandContainer& arguments);
        //! @}

    private:

        AZ_CONSOLEFUNC(NetworkingSystemComponent, DumpStats, AZ::ConsoleFunctorFlags::Null, "Dumps stats for all instantiated network interfaces");

        NetworkInterfaces m_networkInterfaces;
        AZStd::unique_ptr<TcpListenThread> m_listenThread;
        AZStd::unique_ptr<UdpReaderThread> m_readerThread;

        using CompressionFactories = AZStd::unordered_map<AZ::Name, AZStd::unique_ptr<ICompressorFactory>>;
        CompressionFactories m_compressorFactories;
    };
}
