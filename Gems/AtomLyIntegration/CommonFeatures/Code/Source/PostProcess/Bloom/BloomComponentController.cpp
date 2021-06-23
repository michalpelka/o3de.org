/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <AzCore/RTTI/BehaviorContext.h>

#include <Atom/RPI.Public/Scene.h>

#include <PostProcess/Bloom/BloomComponentController.h>

namespace AZ
{
    namespace Render
    {
        void BloomComponentController::Reflect(ReflectContext* context)
        {
            BloomComponentConfig::Reflect(context);

            if (auto* serializeContext = azrtti_cast<SerializeContext*>(context))
            {
                serializeContext->Class<BloomComponentController>()
                    ->Version(0)
                    ->Field("Configuration", &BloomComponentController::m_configuration);
            }

            if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->EBus<BloomRequestBus>("BloomRequestBus")
                    ->Attribute(AZ::Script::Attributes::Module, "render")
                    ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                    // Auto-gen behavior context...
#define PARAM_EVENT_BUS BloomRequestBus::Events
#include <Atom/Feature/ParamMacros/StartParamBehaviorContext.inl>
#include <Atom/Feature/PostProcess/Bloom/BloomParams.inl>
#include <Atom/Feature/ParamMacros/EndParams.inl>
#undef PARAM_EVENT_BUS

                    ;
            }
        }

        void BloomComponentController::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
        {
            provided.push_back(AZ_CRC_CE("BloomService"));
        }

        void BloomComponentController::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
        {
            incompatible.push_back(AZ_CRC_CE("BloomService"));
        }

        void BloomComponentController::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required)
        {
            required.push_back(AZ_CRC_CE("PostFXLayerService"));
        }

        BloomComponentController::BloomComponentController(const BloomComponentConfig& config)
            : m_configuration(config)
        {
        }

        void BloomComponentController::Activate(EntityId entityId)
        {
            m_entityId = entityId;

            PostProcessFeatureProcessorInterface* fp = RPI::Scene::GetFeatureProcessorForEntity<PostProcessFeatureProcessorInterface>(m_entityId);
            if (fp)
            {
                m_postProcessInterface = fp->GetOrCreateSettingsInterface(m_entityId);
                if (m_postProcessInterface)
                {
                    m_settingsInterface = m_postProcessInterface->GetOrCreateBloomSettingsInterface();
                    OnConfigChanged();
                }
            }
            BloomRequestBus::Handler::BusConnect(m_entityId);
        }

        void BloomComponentController::Deactivate()
        {
            BloomRequestBus::Handler::BusDisconnect(m_entityId);

            if (m_postProcessInterface)
            {
                m_postProcessInterface->RemoveBloomSettingsInterface();
            }

            m_postProcessInterface = nullptr;
            m_settingsInterface = nullptr;
            m_entityId.SetInvalid();
        }

        // Getters & Setters...

        void BloomComponentController::SetConfiguration(const BloomComponentConfig& config)
        {
            m_configuration = config;
            OnConfigChanged();
        }

        const BloomComponentConfig& BloomComponentController::GetConfiguration() const
        {
            return m_configuration;
        }

        void BloomComponentController::OnConfigChanged()
        {
            if (m_settingsInterface)
            {
                m_configuration.CopySettingsTo(m_settingsInterface);
                m_settingsInterface->OnConfigChanged();
            }
        }

        // Auto-gen getter/setter function definitions...
        // The setter functions will set the values on the Atom settings class, then get the value back
        // from the settings class to set the local configuration. This is in case the settings class
        // applies some custom logic that results in the set value being different from the input
#define AZ_GFX_COMMON_PARAM(ValueType, Name, MemberName, DefaultValue)                                  \
        ValueType BloomComponentController::Get##Name() const                                           \
        {                                                                                               \
            return m_configuration.MemberName;                                                          \
        }                                                                                               \
        void BloomComponentController::Set##Name(ValueType val)                                         \
        {                                                                                               \
            if(m_settingsInterface)                                                                     \
            {                                                                                           \
                m_settingsInterface->Set##Name(val);                                                    \
                m_settingsInterface->OnConfigChanged();                                                 \
                m_configuration.MemberName = m_settingsInterface->Get##Name();                          \
            }                                                                                           \
            else                                                                                        \
            {                                                                                           \
                m_configuration.MemberName = val;                                                       \
            }                                                                                           \
        }                                                                                               \

#define AZ_GFX_COMMON_OVERRIDE(ValueType, Name, MemberName, OverrideValueType)                          \
        OverrideValueType BloomComponentController::Get##Name##Override() const                         \
        {                                                                                               \
            return m_configuration.MemberName##Override;                                                \
        }                                                                                               \
        void BloomComponentController::Set##Name##Override(OverrideValueType val)                       \
        {                                                                                               \
            m_configuration.MemberName##Override = val;                                                 \
            if(m_settingsInterface)                                                                     \
            {                                                                                           \
                m_settingsInterface->Set##Name##Override(val);                                          \
                m_settingsInterface->OnConfigChanged();                                                 \
            }                                                                                           \
        }                                                                                               \

#include <Atom/Feature/ParamMacros/MapAllCommon.inl>
#include <Atom/Feature/PostProcess/Bloom/BloomParams.inl>
#include <Atom/Feature/ParamMacros/EndParams.inl>


    } // namespace Render
} // namespace AZ
