/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#pragma once

#include <AzCore/Component/ComponentBus.h>

namespace GradientSignal
{
    class SurfaceAltitudeGradientRequests
        : public AZ::ComponentBus
    {
    public:
        /**
         * Overrides the default AZ::EBusTraits handler policy to allow one
         * listener only.
         */
        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;

        virtual AZ::EntityId GetShapeEntityId() const = 0;
        virtual void SetShapeEntityId(AZ::EntityId entityId) = 0;

        virtual float GetAltitudeMin() const = 0;
        virtual void SetAltitudeMin(float altitudeMin) = 0;

        virtual float GetAltitudeMax() const = 0;
        virtual void SetAltitudeMax(float altitudeMax) = 0;

        virtual size_t GetNumTags() const = 0;
        virtual AZ::Crc32 GetTag(int tagIndex) const = 0;
        virtual void RemoveTag(int tagIndex) = 0;
        virtual void AddTag(AZStd::string tag) = 0;
    };

    using SurfaceAltitudeGradientRequestBus = AZ::EBus<SurfaceAltitudeGradientRequests>;
}
