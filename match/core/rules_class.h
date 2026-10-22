// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Sparse RulesClass view for members independently read from the pointer at
// 0x8871E0. Raw retail instructions show: 0x459494 / 0x4594C2 read +0x244;
// 0x5F5E5D reads +0x1700 and 0x5F5DF5 / 0x5F5E30 read +0x1708;
// 0x458349 and 0x4594DA read +0x1700; 0x4158E0 reads +0x54C; and
// 0x65B4F0 / 0x65B530 load +0x1804.
#ifndef GG_MATCH_CORE_RULES_CLASS_H
#define GG_MATCH_CORE_RULES_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct AnimTypeClass;
struct WeaponTypeClass;

struct RulesClass
{
    char unknown_00[0x04C];
    AnimTypeClass* LandAnim; // +0x04C
    char unknown_050[0x108 - 0x050];
    AnimTypeClass** TouchdownAnims; // +0x108
    char unknown_10C[0x244 - 0x10C];
    int BunkerSound;
    char unknown_248[0x354 - 0x248];
    AnimTypeClass* SpawnAnim; // +0x354
    char unknown_358[0x54C - 0x358];
    int At_54C;
    char unknown_550[0x5A4 - 0x550];
    WeaponTypeClass* Weapon; // +0x5A4
    int unknown_5A8;
    int MinFall; // +0x5AC
    double Angle; // +0x5B0
    char unknown_5B8[0x0FA8 - 0x5B8];
    int unknown_FA8;
    char unknown_FAC[0x1700 - 0xFAC];
    double ConditionYellow;
    double ConditionRed;
    char unknown_1710[0x1804 - 0x1710];
    int RadDurationMultiple;
};

GG_STATIC_ASSERT(offsetof(RulesClass, BunkerSound) == 0x244);
GG_STATIC_ASSERT(offsetof(RulesClass, At_54C) == 0x54C);
GG_STATIC_ASSERT(offsetof(RulesClass, LandAnim) == 0x04C);
GG_STATIC_ASSERT(offsetof(RulesClass, TouchdownAnims) == 0x108);
GG_STATIC_ASSERT(offsetof(RulesClass, SpawnAnim) == 0x354);
GG_STATIC_ASSERT(offsetof(RulesClass, Weapon) == 0x5A4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_5A8) == 0x5A8);
GG_STATIC_ASSERT(offsetof(RulesClass, MinFall) == 0x5AC);
GG_STATIC_ASSERT(offsetof(RulesClass, Angle) == 0x5B0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_FA8) == 0x0FA8);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionYellow) == 0x1700);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionRed) == 0x1708);
GG_STATIC_ASSERT(offsetof(RulesClass, RadDurationMultiple) == 0x1804);

// GLOBAL: GAMEMD 0x008871E0 — active RulesClass pointer.
extern RulesClass* RulesInstance;

#endif  // GG_MATCH_CORE_RULES_CLASS_H
