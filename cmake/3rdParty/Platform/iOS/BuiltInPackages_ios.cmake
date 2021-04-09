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

# shared by other platforms:
ly_associate_package(PACKAGE_NAME zlib-1.2.8-rev2-multiplatform      TARGETS zlib       PACKAGE_HASH e6f34b8ac16acf881e3d666ef9fd0c1aee94c3f69283fb6524d35d6f858eebbb)
ly_associate_package(PACKAGE_NAME Lua-5.3.5-rev3-multiplatform       TARGETS Lua        PACKAGE_HASH 171dcdd60bd91fb325feaab0e53dd185c9d6e7b701d53e66fc6c2c6ee91d8bff)
ly_associate_package(PACKAGE_NAME md5-2.0-multiplatform              TARGETS md5        PACKAGE_HASH 29e52ad22c78051551f78a40c2709594f0378762ae03b417adca3f4b700affdf)
ly_associate_package(PACKAGE_NAME RapidJSON-1.1.0-multiplatform      TARGETS RapidJSON  PACKAGE_HASH 18b0aef4e6e849389916ff6de6682ab9c591ebe15af6ea6017014453c1119ea1)
ly_associate_package(PACKAGE_NAME RapidXML-1.13-multiplatform        TARGETS RapidXML   PACKAGE_HASH 510b3c12f8872c54b34733e34f2f69dd21837feafa55bfefa445c98318d96ebf)
ly_associate_package(PACKAGE_NAME cityhash-1.1-multiplatform         TARGETS cityhash   PACKAGE_HASH 0ace9e6f0b2438c5837510032d2d4109125845c0efd7d807f4561ec905512dd2)
ly_associate_package(PACKAGE_NAME lz4-r128-multiplatform             TARGETS lz4        PACKAGE_HASH d7b1d5651191db2c339827ad24f669d9d37754143e9173abc986184532f57c9d)
ly_associate_package(PACKAGE_NAME expat-2.1.0-multiplatform          TARGETS expat      PACKAGE_HASH 452256acd1fd699cef24162575b3524fccfb712f5321c83f1df1ce878de5b418)
ly_associate_package(PACKAGE_NAME zstd-1.35-multiplatform            TARGETS zstd       PACKAGE_HASH 45d466c435f1095898578eedde85acf1fd27190e7ea99aeaa9acfd2f09e12665)
ly_associate_package(PACKAGE_NAME glad-2.0.0-beta-rev2-multiplatform TARGETS glad       PACKAGE_HASH ff97ee9664e97d0854b52a3734c2289329d9f2b4cd69478df6d0ca1f1c9392ee)
ly_associate_package(PACKAGE_NAME lux_core-2.2-rev5-multiplatform    TARGETS lux_core   PACKAGE_HASH c8c13cf7bc351643e1abd294d0841b24dee60e51647dff13db7aec396ad1e0b5)

# platform-specific:
ly_associate_package(PACKAGE_NAME AWSNativeSDK-1.7.167-rev2-ios  TARGETS AWSNativeSDK    PACKAGE_HASH ffd8a1a967bd67c996c64b64986706868bba5393e6d5c234cab578d66b2f8334)
ly_associate_package(PACKAGE_NAME PhysX-4.1.0.25992954-rev1-ios  TARGETS PhysX           PACKAGE_HASH a2a48a09128337c72b9c2c1b8f43187c6c914e8509c9c6cd91810108748d7e09)
ly_associate_package(PACKAGE_NAME mikkelsen-1.0.0.4-ios          TARGETS mikkelsen       PACKAGE_HASH 976aaa3ccd8582346132a10af253822ccc5d5bcc9ea5ba44d27848f65ee88a8a)
ly_associate_package(PACKAGE_NAME googletest-1.8.1-rev4-ios      TARGETS googletest      PACKAGE_HASH 2f121ad9784c0ab73dfaa58e1fee05440a82a07cc556bec162eeb407688111a7)
ly_associate_package(PACKAGE_NAME googlebenchmark-1.5.0-rev2-ios TARGETS GoogleBenchmark PACKAGE_HASH c2ffaed2b658892b1bcf81dee4b44cd1cb09fc78d55584ef5cb8ab87f2d8d1ae)
ly_associate_package(PACKAGE_NAME libsamplerate-0.2.1-rev1-ios   TARGETS libsamplerate   PACKAGE_HASH 126ab8335f3aa12322665c51d6cb144195b9b9e4c9f5a5d3fc1b560025cc772d)
