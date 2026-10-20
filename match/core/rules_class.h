// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Sparse RulesClass view for members independently read at 0x8871E0:
// 0x4158E0 loads +0x54C; 0x65B4F0 and 0x65B530 load +0x1804.
#ifndef GG_MATCH_CORE_RULES_CLASS_H
#define GG_MATCH_CORE_RULES_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct RulesClass
{
    char unknown_00[0x54C];
    int At_54C;
    char unknown_550[0x1804 - 0x550];
    int RadDurationMultiple;
};

GG_STATIC_ASSERT(offsetof(RulesClass, At_54C) == 0x54C);
GG_STATIC_ASSERT(offsetof(RulesClass, RadDurationMultiple) == 0x1804);

// GLOBAL: GAMEMD 0x008871E0 — active RulesClass pointer.
extern RulesClass* RulesInstance;

#endif  // GG_MATCH_CORE_RULES_CLASS_H
