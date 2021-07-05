/*
 * Copyright (c) Contributors to the Open 3D Engine Project. For complete copyright and license terms please see the LICENSE at the root of this distribution.
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */
#pragma once

#include <AzCore/base.h>

#define AZCG_Unpack_1(x) auto AZ_JOIN(azcg_unpack_, __COUNTER__) = x;
#define AZCG_Unpack_2(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_1(__VA_ARGS__)
#define AZCG_Unpack_3(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_2(__VA_ARGS__)
#define AZCG_Unpack_4(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_3(__VA_ARGS__)
#define AZCG_Unpack_5(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_4(__VA_ARGS__)
#define AZCG_Unpack_6(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_5(__VA_ARGS__)
#define AZCG_Unpack_7(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_6(__VA_ARGS__)
#define AZCG_Unpack_8(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_7(__VA_ARGS__)
#define AZCG_Unpack_9(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_8(__VA_ARGS__)
#define AZCG_Unpack_10(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_9(__VA_ARGS__)
#define AZCG_Unpack_11(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_10(__VA_ARGS__)
#define AZCG_Unpack_12(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_11(__VA_ARGS__)
#define AZCG_Unpack_13(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_12(__VA_ARGS__)
#define AZCG_Unpack_14(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_13(__VA_ARGS__)
#define AZCG_Unpack_15(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_14(__VA_ARGS__)
#define AZCG_Unpack_16(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_15(__VA_ARGS__)
#define AZCG_Unpack_17(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_16(__VA_ARGS__)
#define AZCG_Unpack_18(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_17(__VA_ARGS__)
#define AZCG_Unpack_19(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_18(__VA_ARGS__)
#define AZCG_Unpack_20(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_19(__VA_ARGS__)
#define AZCG_Unpack_21(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_20(__VA_ARGS__)
#define AZCG_Unpack_22(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_21(__VA_ARGS__)
#define AZCG_Unpack_23(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_22(__VA_ARGS__)
#define AZCG_Unpack_24(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_23(__VA_ARGS__)
#define AZCG_Unpack_25(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_24(__VA_ARGS__)
#define AZCG_Unpack_26(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_25(__VA_ARGS__)
#define AZCG_Unpack_27(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_26(__VA_ARGS__)
#define AZCG_Unpack_28(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_27(__VA_ARGS__)
#define AZCG_Unpack_29(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_28(__VA_ARGS__)
#define AZCG_Unpack_30(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_29(__VA_ARGS__)
#define AZCG_Unpack_31(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_30(__VA_ARGS__)
#define AZCG_Unpack_32(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_31(__VA_ARGS__)
#define AZCG_Unpack_33(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_32(__VA_ARGS__)
#define AZCG_Unpack_34(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_33(__VA_ARGS__)
#define AZCG_Unpack_35(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_34(__VA_ARGS__)
#define AZCG_Unpack_36(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_35(__VA_ARGS__)
#define AZCG_Unpack_37(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_36(__VA_ARGS__)
#define AZCG_Unpack_38(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_37(__VA_ARGS__)
#define AZCG_Unpack_39(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_38(__VA_ARGS__)
#define AZCG_Unpack_40(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_39(__VA_ARGS__)
#define AZCG_Unpack_41(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_40(__VA_ARGS__)
#define AZCG_Unpack_42(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_41(__VA_ARGS__)
#define AZCG_Unpack_43(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_42(__VA_ARGS__)
#define AZCG_Unpack_44(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_43(__VA_ARGS__)
#define AZCG_Unpack_45(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_44(__VA_ARGS__)
#define AZCG_Unpack_46(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_45(__VA_ARGS__)
#define AZCG_Unpack_47(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_46(__VA_ARGS__)
#define AZCG_Unpack_48(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_47(__VA_ARGS__)
#define AZCG_Unpack_49(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_48(__VA_ARGS__)
#define AZCG_Unpack_50(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_49(__VA_ARGS__)
#define AZCG_Unpack_51(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_50(__VA_ARGS__)
#define AZCG_Unpack_52(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_51(__VA_ARGS__)
#define AZCG_Unpack_53(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_52(__VA_ARGS__)
#define AZCG_Unpack_54(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_53(__VA_ARGS__)
#define AZCG_Unpack_55(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_54(__VA_ARGS__)
#define AZCG_Unpack_56(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_55(__VA_ARGS__)
#define AZCG_Unpack_57(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_56(__VA_ARGS__)
#define AZCG_Unpack_58(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_57(__VA_ARGS__)
#define AZCG_Unpack_59(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_58(__VA_ARGS__)
#define AZCG_Unpack_60(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_59(__VA_ARGS__)
#define AZCG_Unpack_61(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_60(__VA_ARGS__)
#define AZCG_Unpack_62(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_61(__VA_ARGS__)
#define AZCG_Unpack_63(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_62(__VA_ARGS__)
#define AZCG_Unpack_64(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_63(__VA_ARGS__)
#define AZCG_Unpack_65(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_64(__VA_ARGS__)
#define AZCG_Unpack_66(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_65(__VA_ARGS__)
#define AZCG_Unpack_67(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_66(__VA_ARGS__)
#define AZCG_Unpack_68(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_67(__VA_ARGS__)
#define AZCG_Unpack_69(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_68(__VA_ARGS__)
#define AZCG_Unpack_70(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_69(__VA_ARGS__)
#define AZCG_Unpack_71(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_70(__VA_ARGS__)
#define AZCG_Unpack_72(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_71(__VA_ARGS__)
#define AZCG_Unpack_73(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_72(__VA_ARGS__)
#define AZCG_Unpack_74(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_73(__VA_ARGS__)
#define AZCG_Unpack_75(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_74(__VA_ARGS__)
#define AZCG_Unpack_76(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_75(__VA_ARGS__)
#define AZCG_Unpack_77(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_76(__VA_ARGS__)
#define AZCG_Unpack_78(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_77(__VA_ARGS__)
#define AZCG_Unpack_79(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_78(__VA_ARGS__)
#define AZCG_Unpack_80(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_79(__VA_ARGS__)
#define AZCG_Unpack_81(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_80(__VA_ARGS__)
#define AZCG_Unpack_82(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_81(__VA_ARGS__)
#define AZCG_Unpack_83(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_82(__VA_ARGS__)
#define AZCG_Unpack_84(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_83(__VA_ARGS__)
#define AZCG_Unpack_85(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_84(__VA_ARGS__)
#define AZCG_Unpack_86(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_85(__VA_ARGS__)
#define AZCG_Unpack_87(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_86(__VA_ARGS__)
#define AZCG_Unpack_88(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_87(__VA_ARGS__)
#define AZCG_Unpack_89(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_88(__VA_ARGS__)
#define AZCG_Unpack_90(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_89(__VA_ARGS__)
#define AZCG_Unpack_91(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_90(__VA_ARGS__)
#define AZCG_Unpack_92(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_91(__VA_ARGS__)
#define AZCG_Unpack_93(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_92(__VA_ARGS__)
#define AZCG_Unpack_94(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_93(__VA_ARGS__)
#define AZCG_Unpack_95(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_94(__VA_ARGS__)
#define AZCG_Unpack_96(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_95(__VA_ARGS__)
#define AZCG_Unpack_97(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_96(__VA_ARGS__)
#define AZCG_Unpack_98(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_97(__VA_ARGS__)
#define AZCG_Unpack_99(x, ...) AZCG_Unpack_1(x) AZCG_Unpack_98(__VA_ARGS__)
#define AZCG_Unpack(...) AZ_MACRO_SPECIALIZE(AZCG_Unpack_, AZ_VA_NUM_ARGS(__VA_ARGS__), (__VA_ARGS__))
#define AZCG_Paste(x) x
