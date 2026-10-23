// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Sparse RulesClass view for members independently read from the pointer at
// 0x8871E0. Raw retail instructions show: 0x459494 / 0x4594C2 read +0x244;
// 0x5F5E5D reads +0x1700 and 0x5F5DF5 / 0x5F5E30 read +0x1708;
// 0x458349 and 0x4594DA read +0x1700; 0x4158E0 reads +0x54C; and
// 0x65B4F0 / 0x65B530 load +0x1804.
#ifndef GG_MATCH_CORE_RULES_CLASS_H
#define GG_MATCH_CORE_RULES_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "vector_class.h"

class AnimTypeClass;
class WeaponTypeClass;
class UnitTypeClass;

struct RulesClass
{
    int unknown_000; // 0x6850FB -> fastcall55AF40
    int unknown_004;
    int unknown_008; // 0x685108 -> fastcall55AF50
    char unknown_00C[0x04C - 0x00C];
    AnimTypeClass* LandAnim; // +0x04C
    char unknown_050[0x8C - 0x050];
    int unknown_08C;
    char unknown_090[0x108 - 0x090];
    AnimTypeClass** TouchdownAnims; // +0x108
    char unknown_10C[0x1D4 - 0x10C];
    int unknown_1D4;    // +0x1D4 sound played on entering planning mode
    char unknown_1D8[0x1E0 - 0x1D8];
    int unknown_1E0;    // +0x1E0 sound played on leaving it
    char unknown_1E4[0x244 - 0x1E4];
    int BunkerSound;
    char unknown_248[0x344 - 0x248];
    AnimTypeClass* unknown_344;
    char unknown_348[0x354 - 0x348];
    AnimTypeClass* SpawnAnim; // +0x354
    char unknown_358[0x54C - 0x358];
    int At_54C;
    char unknown_550[0x580 - 0x550];
    int unknown_580;
    char unknown_584[0x5A4 - 0x584];
    WeaponTypeClass* Weapon; // +0x5A4
    int unknown_5A8;
    int MinFall; // +0x5AC
    double Angle; // +0x5B0
    char unknown_5B8[0x700 - 0x5B8];
    int unknown_700;    // +0x700 sound played when planning guard areas are refused
    char unknown_704[0x724 - 0x704];
    int unknown_724;
    int unknown_728;
    int unknown_72C;
    char unknown_730[0x788 - 0x730];
    int unknown_788;
    int unknown_78C;
    char unknown_790[0x7A8 - 0x790];
    int unknown_7A8;
    char unknown_7AC[0xB20 - 0x7AC];
    DynamicVectorClass<UnitTypeClass*> unknown_B20; // constructor-type list0x688B55
    char unknown_B38[0xD04 - 0xB38];
    // Three pointer collections selected at 0x68C164..0x68C1A5.
    void** unknown_D04;
    char unknown_D08[8];
    int unknown_D10;
    char unknown_D14[0xD20 - 0xD14];
    void** unknown_D20;
    char unknown_D24[8];
    int unknown_D2C;
    char unknown_D30[0xD3C - 0xD30];
    void** unknown_D3C;
    char unknown_D40[8];
    int unknown_D48;
    char unknown_D4C[8];
    int unknown_D54;
    char unknown_D58[0xE04 - 0xD58];
    int unknown_E04;
    char unknown_E08[0x0FA8 - 0xE08];
    int unknown_FA8;
    char unknown_FAC[0x14B5 - 0xFAC];
    bool unknown_14B5;
    char unknown_14B6[5];
    bool unknown_14BB;
    char unknown_14BC[0x1700 - 0x14BC];
    double ConditionYellow;
    double ConditionRed;
    char unknown_1710[0x1804 - 0x1710];
    int RadDurationMultiple;
    char unknown_1808[0x186C - 0x1808];
    int unknown_186C; // random upper bound minus one0x68508F
    AnimTypeClass* unknown_1870; // 0x6850D9 -> AnimClass constructor0x421EA0
};

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_B20) == 0xB20);
GG_STATIC_ASSERT(offsetof(RulesClass, BunkerSound) == 0x244);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_000) == 0x000);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_008) == 0x008);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_186C) == 0x186C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1870) == 0x1870);

GG_STATIC_ASSERT(offsetof(RulesClass, At_54C) == 0x54C);
GG_STATIC_ASSERT(offsetof(RulesClass, LandAnim) == 0x04C);
GG_STATIC_ASSERT(offsetof(RulesClass, TouchdownAnims) == 0x108);
GG_STATIC_ASSERT(offsetof(RulesClass, SpawnAnim) == 0x354);
GG_STATIC_ASSERT(offsetof(RulesClass, Weapon) == 0x5A4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_5A8) == 0x5A8);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1D4) == 0x1D4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1E0) == 0x1E0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_700) == 0x700);
GG_STATIC_ASSERT(offsetof(RulesClass, MinFall) == 0x5AC);
GG_STATIC_ASSERT(offsetof(RulesClass, Angle) == 0x5B0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_344) == 0x344);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_E04) == 0xE04);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D04) == 0xD04);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D10) == 0xD10);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D20) == 0xD20);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D2C) == 0xD2C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D3C) == 0xD3C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D48) == 0xD48);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D54) == 0xD54);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_788) == 0x788);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_78C) == 0x78C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_7A8) == 0x7A8);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_FA8) == 0x0FA8);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionYellow) == 0x1700);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionRed) == 0x1708);
GG_STATIC_ASSERT(offsetof(RulesClass, RadDurationMultiple) == 0x1804);

// GLOBAL: GAMEMD 0x008871E0 — active RulesClass pointer.
extern RulesClass* RulesInstance;

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_08C) == 0x08C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_580) == 0x580);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_724) == 0x724);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_728) == 0x728);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_72C) == 0x72C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14B5) == 0x14B5);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14BB) == 0x14BB);

#endif  // GG_MATCH_CORE_RULES_CLASS_H
