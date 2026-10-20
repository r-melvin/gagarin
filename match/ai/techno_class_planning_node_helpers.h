// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and layout read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x634290 and 0x639F80. Both functions
//   are declared (but not defined) in
//   match/ai/techno_class_clear_tokens_methods.h (read, not edited) as
//   Node_006386E0::FUN_00634290 and Scene_006386E0::FUN_00639F80; this TU
//   supplies their bodies out of line so that header stays untouched.
//
//   0x634290 walks Node_006386E0's own already-confirmed layout: the entry
//   count at +0x10, the entry-pointer array at +0x04, one entry's owner word
//   at [*entry+0x00]. `__thiscall`, one stack argument, returns the matching
//   index or -1 (`OR EAX,0xffffffff` before the loop, `RET 0x4`).
//
//   0x639F80 is a small free-standing `__fastcall(int index)` clamp on a
//   24-entry table of per-house counters at 0xAC4B84: in range, it decrements
//   the counter but never lets it go below 0 (`(v-1)<0 ? 0 : v-1`, built
//   branchlessly from `DEC`/`SETS`/`DEC`/`AND` rather than a compare-and-branch).
#ifndef GG_MATCH_AI_TECHNO_CLASS_PLANNING_NODE_HELPERS_H
#define GG_MATCH_AI_TECHNO_CLASS_PLANNING_NODE_HELPERS_H

#include "techno_class_clear_tokens_methods.h"

// GLOBAL: GAMEMD 0xAC4B84 -- 24 per-house pending-request counters.
extern int DAT_00AC4B84[24];

#endif  // GG_MATCH_AI_TECHNO_CLASS_PLANNING_NODE_HELPERS_H
