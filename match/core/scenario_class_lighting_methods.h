// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Convention and global read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x555AC0: the three channel pointers
//   arrive in ECX, EDX and `[ESP+0xC]` with `RET 4` (__fastcall, no `this`),
//   each is clamped to 1000 and floored at 0 in place, and the dword global
//   `[0xA8EB78]` selects the mask (0..2) through a `SUB ECX,0 / DEC / DEC`
//   chain. YRpp ScenarioClass.h consulted for the name only (consult-only,
//   no LICENSE).
#ifndef GG_MATCH_CORE_SCENARIO_CLASS_LIGHTING_METHODS_H
#define GG_MATCH_CORE_SCENARIO_CLASS_LIGHTING_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The Windows min/max macro shapes: min gives the register-loaded compare with
// the conditional overwrite, max against zero gives the branchless
// `SETLE/DEC/AND` mask.
#define GG_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define GG_MAX(a, b) (((a) > (b)) ? (a) : (b))

// GLOBAL: GAMEMD 0xA8EB78 — colour-depth selector: 0, 1 or 2 pick the 7-, 6-
// and 5-bit channel masks.
extern int DAT_00A8EB78;

struct ScenarioClass
{
    // FUNCTION: GAMEMD 0x555AC0
    static void __fastcall ScenarioLighting(int* red, int* green, int* blue);
};

#endif  // GG_MATCH_CORE_SCENARIO_CLASS_LIGHTING_METHODS_H
