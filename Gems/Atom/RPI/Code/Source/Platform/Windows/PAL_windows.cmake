#
# All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
# its licensors.
#
# For complete copyright and license terms please see the LICENSE at the root of this
# distribution (the "License"). All use of this software is governed by the License,
# or, if provided, by the license below or the license accompanying this file. Do not
# remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#

set (PAL_TRAIT_BUILD_ATOM_RPI_ASSETS_SUPPORTED TRUE)
set (PAL_TRAIT_BUILD_ATOM_RPI_MASKED_OCCLUSION_CULLING_SUPPORTED TRUE)

ly_add_source_properties(
    SOURCES External/MaskedOcclusionCulling/MaskedOcclusionCullingAVX2.cpp
    PROPERTY COMPILE_OPTIONS
    VALUES /arch:AVX2 /W3
)
ly_add_source_properties(
    SOURCES 
        External/MaskedOcclusionCulling/MaskedOcclusionCullingAVX512.cpp
        External/MaskedOcclusionCulling/MaskedOcclusionCulling.cpp
    PROPERTY COMPILE_OPTIONS
    VALUES /W3
)