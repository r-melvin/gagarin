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

struct RulesClass
{
    char unknown_00[0x244];
    int BunkerSound;
    char unknown_248[0x54C - 0x248];
    int At_54C;
    char unknown_550[0x1700 - 0x550];
    double ConditionYellow;
    double ConditionRed;
    char unknown_1710[0x1804 - 0x1710];
    int RadDurationMultiple;
};

GG_STATIC_ASSERT(offsetof(RulesClass, BunkerSound) == 0x244);
GG_STATIC_ASSERT(offsetof(RulesClass, At_54C) == 0x54C);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionYellow) == 0x1700);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionRed) == 0x1708);
GG_STATIC_ASSERT(offsetof(RulesClass, RadDurationMultiple) == 0x1804);

// GLOBAL: GAMEMD 0x008871E0 — active RulesClass pointer.
extern RulesClass* RulesInstance;

#endif  // GG_MATCH_CORE_RULES_CLASS_H
