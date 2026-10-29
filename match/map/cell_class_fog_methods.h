// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x486BF0), cross-checked against
//   YRpp (reconfirmed numerically here).
//   CellClass derives AbstractClass.
//
// CellClass — fog helper. This TU models only the members CleanFog touches:
//   * MapCoords @0x24  (CellStruct, 4 bytes) — the loop's running cell coord
//   * Level     @0x11B (signed char)         — movsx ecx,byte [eax+0x11b]
//   * Flags     @0x140 (int)                 — and [eax+0x140], 0xFFBFFFFF
#ifndef GG_MATCH_MAP_CELL_CLASS_FOG_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_FOG_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 2D short cell coordinate (sizeof == 4): the dword at [this+0x24]. CleanFog
// copies it to a stack local and ++'s X then Y each iteration (inc word [esp+N]).
#include "../_layout/cell.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

class CellClass;

// MapClass singleton — only GetCellAt is forwarded to here, declared (no body)
// so cl emits a relocatable __thiscall call. The retail singleton object lives
// at the fixed address 0x87F7E8.
class MapClass
{
public:
    CellClass* GetCellAt(CellStruct const& mapCoords) const;  // 0x5657A0
};

#include "../_layout/cell_class.h"

GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass, Level)     == 0x11B);
GG_STATIC_ASSERT(offsetof(CellClass, Flags)     == 0x140);

#endif  // GG_MATCH_MAP_CELL_CLASS_FOG_METHODS_H
