// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm @ 0x565730).
//   Signature cross-checked against YRpp:
//     CellClass* MapClass::GetTargetCell(Point2D& location)
//   All offsets reconfirmed numerically from the disassembly:
//     [ECX+0x13c] = Cells (CellClass**), [ECX+0x140] = TotalCells (int),
//     0xABDC50    = InvalidCell, its MapCoords @0x24 => 0xABDC74.
#ifndef GG_MATCH_MAP_MAP_CLASS_TARGET_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_TARGET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 2D integer point (leptons): location.X@0, location.Y@4 read as ints.
struct Point2D
{
    int X;  // +0x00
    int Y;  // +0x04
};
GG_STATIC_ASSERT(offsetof(Point2D, X) == 0x00);
GG_STATIC_ASSERT(offsetof(Point2D, Y) == 0x04);

// 2D short cell coordinate (sizeof == 4): X@0, Y@2.
struct CellStruct
{
    short X;  // +0x00
    short Y;  // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// Minimal CellClass view: only MapCoords @0x24 is touched (written into
// InvalidCell on the fallback path).
class CellClass
{
public:
    char       _pad0[0x24];   // +0x00
    CellStruct MapCoords;     // +0x24
};
GG_STATIC_ASSERT(offsetof(CellClass, MapCoords) == 0x24);

// InvalidCell global (the dummy cell returned when the index is out of range
// or empty), at fixed retail address 0xABDC50.
#define InvalidCell (*reinterpret_cast<CellClass*>(0x00ABDC50))

// Minimal MapClass view: only the two members GetTargetCell touches.
class MapClass
{
public:
    char        _pad0[0x13c];  // +0x000 (GScreenClass base etc.)
    CellClass** Cells;         // +0x13c  flat cell-pointer array
    int         TotalCells;    // +0x140  number of cells in the array

    CellClass* GetTargetCell(Point2D& location);  // 0x565730
};
GG_STATIC_ASSERT(offsetof(MapClass, Cells)      == 0x13c);
GG_STATIC_ASSERT(offsetof(MapClass, TotalCells) == 0x140);

#endif  // GG_MATCH_MAP_MAP_CLASS_TARGET_METHODS_H
