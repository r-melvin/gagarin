// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6385C0: the token returned by the no-argument
//   __thiscall 0x705D20 is read at `[EBX+0x14]` (node count), `[EBX+0x8C]`
//   and the byte `[EBX+0x1C]` (set to 1 on the way out); the owner's vtable
//   slot `[EAX+0x1E8]` is called with (0x1C, 1); 0x636590 is __thiscall on the
//   token with a hidden result pointer and returns a 0x6F-byte record
//   (`MOV ECX,0x1B; REP MOVSD; MOVSW; MOVSB`), of which byte +0 (compared with
//   4) and byte +0x1D (set to 2) are touched; `PUSH 0x6F; CALL 0x7C8E17` is
//   operator new; the record is appended to the DynamicVectorClass at
//   0xAC4B48 (vtable +0, Items 0xAC4B4C, Capacity 0xAC4B50, IsAllocated
//   0xAC4B55, Count 0xAC4B58, CapacityIncrement 0xAC4B5C) by the inlined
//   AddItem. Names cross-checked against YRpp
//     and used as names only.
#ifndef GG_MATCH_AI_TECHNO_CLASS_PLANNING_TOKEN_METHODS_H
#define GG_MATCH_AI_TECHNO_CLASS_PLANNING_TOKEN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// Canonical TechnoClass, PlanningTokenClass and EventClass declarations.
#include "planning_manager.h"

#endif
