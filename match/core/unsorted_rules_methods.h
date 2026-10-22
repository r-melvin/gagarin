// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and the FP constant read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x48ACF0: `MOV EAX,[0x008871E0]` (the global
//   RulesClass pointer), `FILD dword ptr [EAX+0x16B8]`, then `FMUL qword ptr
//   [0x007E1738]`, whose eight bytes read 00 00 00 00 00 00 E0 3F = 0.5.
//   Member name cross-checked against YRpp (`int Gravity`).
#ifndef GG_MATCH_CORE_UNSORTED_RULES_METHODS_H
#define GG_MATCH_CORE_UNSORTED_RULES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct RulesGravityShim
{
    char _layout_pad_P2[0x16B8];  // +0x0000
    int  Gravity;                 // +0x16B8  (FILD operand)
};
GG_STATIC_ASSERT(offsetof(RulesGravityShim, Gravity) == 0x16B8);

// GLOBAL: GAMEMD 0x008871E0 — pointer to the active RulesClass instance.
extern RulesGravityShim* RulesGlobalPtr;

// Half of [General]Gravity, as a double: the per-frame fall acceleration used
// by floating/parachuting objects.
double __fastcall Unsorted_GetFloaterGravity();   // GAMEMD 0x48ACF0

#endif  // GG_MATCH_CORE_UNSORTED_RULES_METHODS_H
