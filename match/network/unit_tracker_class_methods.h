// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Layout and every offset were read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI (the five methods below plus the
//   inlined constructor body at 0x748FD7).
//
// UnitTrackerClass — the per-house unit-production tally used for multiplayer
// end-game statistics.
//
// The table is inline in the object: 512 ints at +0x000..+0x7FC, then
// UnitCount at +0x800 and InNetworkFormat at +0x804, for sizeof 0x808. The
// binary proves it two ways:
//   * GetAllTotals @0x7490C0 is `MOV EAX,ECX; RET` — the totals base *is* the
//     object address, so there is no pointer to dereference.
//   * ClearUnitTotal @0x7490D0 reloads UnitCount from [ECX+0x800] on *every*
//     iteration (`MOV ESI,[ECX+0x800]` inside the loop) because the store
//     `UnitTotals[i] = 0` may alias it — only possible if both live in the same
//     object. GetTotalOfAll @0x7490A0, which stores nothing, keeps the count in
//     a register and counts down instead.
#ifndef GG_MATCH_NETWORK_UNIT_TRACKER_CLASS_METHODS_H
#define GG_MATCH_NETWORK_UNIT_TRACKER_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The table width the reset path stamps in before overwriting it with the
// caller's count (`MOV dword ptr [ECX+0x800],0x200` @0x749061).
#define UNIT_TRACKER_MAX_TYPES 0x200

#include "../_layout/unit_tracker_class.h"

#endif  // GG_MATCH_NETWORK_UNIT_TRACKER_CLASS_METHODS_H
