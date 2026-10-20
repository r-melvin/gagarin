// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x486BF0), cross-checked against
//   YRpp CellClass.h / MapClass.h (consult-only; reconfirmed numerically here).
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
struct CellStruct
{
    short X;  // +0x00
    short Y;  // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

struct CellClass;

// MapClass singleton — only GetCellAt is forwarded to here, declared (no body)
// so cl emits a relocatable __thiscall call. The retail singleton object lives
// at the fixed address 0x87F7E8.
struct MapClass
{
    CellClass* GetCellAt(CellStruct const& mapCoords) const;  // 0x5657A0
};

struct CellClass
{
    char        _base[0x24];                 // +0x00  AbstractClass (vtable + base)
    CellStruct  MapCoords;                    // +0x24
    char        _pad28[0x11B - 0x28];         // +0x28
    signed char Level;                        // +0x11B
    char        _pad11c[0x140 - 0x11C];       // +0x11C
    int         Flags;                        // +0x140

    // 0x486C50  CellClass::ClearFoggedObjects — retail callee we are NOT
    // matching; declared (no body) so cl emits a relocatable __thiscall call.
    void ClearFoggedObjects();

    // 0x486BF0
    void CleanFog();
};

GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass, Level)     == 0x11B);
GG_STATIC_ASSERT(offsetof(CellClass, Flags)     == 0x140);

#endif  // GG_MATCH_MAP_CELL_CLASS_FOG_METHODS_H
