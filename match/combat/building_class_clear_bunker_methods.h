// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x459470: `LEA ECX,[ESI+0x9c]` with three dword loads
//   (the building's CoordStruct), `[ESI+0x2E4]` (BunkerLinkedItem, cleared on
//   both objects), `[ESI+0x520]` (Type) with `ADD EAX,0x127c/0x128c/0x12c0/
//   0x12d0` (Type->Anims[12]/[13] name buffers, base 0xF4C at 0x44 per record
//   per match/economy/building_class_enable_methods.h), `[ESI+0x718]`, the
//   rules globals `[0x8871E0]` `+0x244` (int, -1 = none) and `+0x1700`
//   (double, the FCOMP operand), and the two virtual slots `[EDX+0x274]` and
//   `[EDX+0x1E8]`. YRpp names ClearBunker,
//   BunkerLinkedItem and the health-ratio callee 0x5F5C60.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_CLEAR_BUNKER_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_CLEAR_BUNKER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/building_class.h"
#include "../_layout/voc_class.h"
#include "../core/rules_class.h"


#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_CLEAR_BUNKER_METHODS_H
