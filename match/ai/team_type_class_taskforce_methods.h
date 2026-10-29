// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6F1FA0: `[ESI+0xE4]` (the taskforce pointer),
//   `[ESI+0xEC]`, `[ESI+0xF0]`, `[ESI+0xF1]`, `[ESI+0xF6]` on the team type;
//   `[EAX+0x9C]` (entry count) and `[EAX+EBP]` with EBP starting at 0xA8 and
//   stepping by 8 (the per-entry type pointer) on the taskforce; `[EAX+0xCCE]`,
//   `[EAX+0x5E0]`, `[EAX+0x5B4]` on the techno type. The method name and the
//   entry pairing (amount, type) are cross-checked against YRpp.
#ifndef GG_MATCH_AI_TEAM_TYPE_CLASS_TASKFORCE_METHODS_H
#define GG_MATCH_AI_TEAM_TYPE_CLASS_TASKFORCE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/team_type_class.h"
#include "../_layout/techno_type_class.h"




// FUNCTION: GAMEMD 0x5889F0 (decl; reloc) — folds one type's +0x5B4 value into
// the running value. Two register arguments, nothing on the stack.
int FUN_005889F0(int value, int running);


#endif  // GG_MATCH_AI_TEAM_TYPE_CLASS_TASKFORCE_METHODS_H
