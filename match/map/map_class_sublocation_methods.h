// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4ACA10: the cell's flag word `[EAX+0x140]` (bit
//   0x100 tested as `TEST CH,1`), its signed level byte `MOVSX ECX,[EAX+0x11B]`,
//   the coordinate's Z `[ESI+0x8]`, the level height global `IMUL ECX,[0x8A0740]`,
//   and the map singleton as the immediate `MOV ECX,0x87F7E8`. The callee at
//   0x565730 reads `[EDI]`/`[EDI+4]` of its argument (a CoordStruct), and the
//   one at 0x481180 takes five stack arguments (out, coords, three bytes).
//   Names (PickInfantrySublocation, FindInfantrySubposition, GetCellAt, Level,
//   Flags) cross-checked against YRpp.
#ifndef GG_MATCH_MAP_MAP_CLASS_SUBLOCATION_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_SUBLOCATION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/coord_struct.h"
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);

// CellClass (partial) — only the members PickInfantrySublocation reads.
#include "../_layout/cell_class.h"
GG_STATIC_ASSERT(offsetof(CellClass, Level) == 0x11B);
GG_STATIC_ASSERT(offsetof(CellClass, Flags) == 0x140);

// GLOBAL: GAMEMD 0x8A0740 — the height of one cell level in leptons.
extern int DAT_008A0740;

#include "../ui/input_controls/ui_display_chain.h"

// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer:
// retail loads its address as the immediate `MOV ECX,0x87F7E8`).
extern MapClass DAT_0087F7E8;

#endif  // GG_MATCH_MAP_MAP_CLASS_SUBLOCATION_METHODS_H
