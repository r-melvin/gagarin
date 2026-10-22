// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and the frame read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x578080. 0x0047B3A0 is
//   CellClass::GetFloorHeight, already bound in cell_class_shroud_methods.h.
//
// The cell lookup is a flat index: `(Y / 256) * 512 + (X / 256)`, bounds-checked
// against the count at 0x0087F928 and read from the item base at 0x0087F924.
// When it misses, retail falls back to the spare cell object at 0x00ABDC50 and
// stamps its MapCoords first — the store lands at 0x00ABDC74, i.e. +0x24, which
// independently confirms CellClass::MapCoords @0x24.
#ifndef GG_MATCH_MAP_MAP_CLASS_ZPOS_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_ZPOS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CellStruct { short X; short Y; };
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// The sub-cell offset handed to GetFloorHeight — two ints in an 8-byte stack
// temporary (`SUB ESP,0x8`, then `LEA EDX,[ESP+4]`).
struct Point2D { int X; int Y; };
GG_STATIC_ASSERT(sizeof(Point2D) == 8);

struct CoordStruct { int X; int Y; int Z; };

class CellClass
{
public:
    char       _pad00[0x24];   // +0x0000
    CellStruct MapCoords;      // +0x0024

    int GetFloorHeight(Point2D const& subcoords) const;   // GAMEMD 0x47B3A0 (declared; reloc)
};
GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);

// GLOBAL: GAMEMD 0x0087F924 / 0x0087F928 — the cell array base and its count.
extern CellClass** CellArrayItems;
extern int         CellArrayCount;
// GLOBAL: GAMEMD 0x00ABDC50 — the spare cell used when the index misses.
extern CellClass   SpareCell;

// Map cell pitch: the index is `cellY * 512 + cellX` (`SHL ECX,9`).
#define MAP_CELL_PITCH 512

class MapClass
{
public:
    int GetZPos(CoordStruct* coords);   // GAMEMD 0x578080 __thiscall
};

#endif  // GG_MATCH_MAP_MAP_CLASS_ZPOS_METHODS_H
