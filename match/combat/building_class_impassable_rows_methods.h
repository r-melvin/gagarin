// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x458A00:
//     * the cell argument is handed to CALL 0x47C520 in ECX and its result
//       compared against `this` (`CMP EAX,ESI`), which types the argument as
//       a CellClass and `this` as a BuildingClass;
//     * `[ESI+0x520]` is the building's type pointer (sizeof(TechnoClass) is
//       0x520, so it is BuildingClass's first own member);
//     * `CMP dword ptr [EAX+0x1620],-1` — an int on the building type;
//     * `MOV CL,byte ptr [EAX+0x16AB]` — a bool on the building type;
//     * `MOV EAX,dword ptr [ESI+0x2E4]` — a pointer on TechnoClass, tested
//       for non-null only;
//     * `CALL dword ptr [EAX+0x1B8]` with a pushed out-pointer — the
//       map-coords slot already pinned by 0x457A10 and 0x43E7B0 in this tree;
//     * `MOVSX EDI,word ptr [EDI+0x24]` — the cell's own map coordinate,
//       AbstractClass being 0x24 bytes so MapCoords is CellClass's first own
//       member, and the X half is the low word.
//   The type-member names (NumberImpassableRows at 0x1620, Bunker at 0x16AB)
//   and TechnoClass::BunkerLinkedItem at 0x2E4 were cross-checked against
//   YRpp
//   (every offset above is re-derived from the user's binary).
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_IMPASSABLE_ROWS_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_IMPASSABLE_ROWS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/building_class.h"
#include "../_layout/cell_class.h"

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_IMPASSABLE_ROWS_METHODS_H
