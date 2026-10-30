// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4F9750 / 0x4FCDC0 / 0x504740),
//   cross-checked against YRpp (every
//   offset reconfirmed numerically from the disassembly below).
//
// HouseClass-misc — three independent HouseClass leaves:
//   ForceEnd                  declare win/lose end-of-game state
//   GetWeedStoragePercentage  weed-store fill ratio (mirrors GetStoragePercentage)
//   EnsurePlanningPathExists  lazily allocate a planning WaypointPath slot
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_MISC_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_MISC_METHODS_H

#include "../movement/waypoint_path_class_methods.h"
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "storage_class.h"

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84 (read by ForceEnd).
#include "../core/frame_counter.h"
#include "../_layout/house_class.h"
#include "../_layout/rules_class.h"

// ---------------------------------------------------------------------------
// WaypointPathClass — the per-slot "planning mode" path object.
//
// Confirmed from 0x504740: a 0x40-byte object (PUSH 0x40 to operator new) with
// a one-int constructor at 0x763810. Only the size + ctor signature matter for
// the EnsurePlanningPathExists `new` pattern; full layout is P2.
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// HouseClass — only the members these three methods touch are modelled; the
// full AbstractClass-derived layout is P2. Each offset is asserted below and
// confirmed numerically from the disassembly.
//   IsWinner      @0x1F7  bool   (MOV AL,[ECX+0x1F7])
//   IsLoser       @0x1F8  bool   (MOV AL,[ECX+0x1F8])
//   PlanningPaths @0x210  ptr[12](MOV [EDI+ESI*4+0x210])
//   EndFrame_298  @0x298  int    (CMP [ECX+0x298],-1)
//   OwnedWeed     @0x314  Storage(LEA ESI,[ECX+0x314])
// ---------------------------------------------------------------------------


GG_STATIC_ASSERT(offsetof(HouseClass, IsWinner)      == 0x1F7);
GG_STATIC_ASSERT(offsetof(HouseClass, IsLoser)       == 0x1F8);
GG_STATIC_ASSERT(offsetof(HouseClass, PlanningPaths) == 0x210);
GG_STATIC_ASSERT(offsetof(HouseClass, BorrowedTime)  == 0x298);
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedWeed)     == 0x314);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_MISC_METHODS_H
