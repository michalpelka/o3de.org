#
# Copyright (c) Contributors to the Open 3D Engine Project
# 
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

find_library(AV_FOUNDATION_LIBRARY AVFoundation)
find_library(AUDIO_TOOLBOX_GRAPHICS_LIBRARY AudioToolbox)
find_library(CORE_AUDIO_SERVICES_LIBRARY CoreAudio)

set(LY_BUILD_DEPENDENCIES
    PRIVATE
        ${AV_FOUNDATION_LIBRARY}
        ${AUDIO_TOOLBOX_GRAPHICS_LIBRARY}
        ${CORE_AUDIO_SERVICES_LIBRARY}
)
