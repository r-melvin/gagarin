// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm @ 0x5785F0).
//   Signature cross-checked against YRpp MapClass.h (consult-only):
//     bool MapClass::IsWithinUsableArea(const CoordStruct& coords) const
//   which converts the coord to a cell (signed /256 per axis) and tail-calls
//   the CellStruct overload @ 0x578460 with checkLevel = true.
#ifndef GG_MATCH_MAP_MAP_CLASS_AREA_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_AREA_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 3D world coordinate (leptons). IsWithinUsableArea reads X@0 and Y@4 as ints.
struct CoordStruct
{
    int X;  // +0x00
    int Y;  // +0x04
    int Z;  // +0x08
};
GG_STATIC_ASSERT(offsetof(CoordStruct, X) == 0x00);
GG_STATIC_ASSERT(offsetof(CoordStruct, Y) == 0x04);

// 2D short cell coordinate (sizeof == 4): X@0, Y@2.
struct CellStruct
{
    short X;  // +0x00
    short Y;  // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

// Inlined coord->cell conversion (CellClass::Coord2Cell in YRpp): signed /256
// per axis, returned by value as a packed dword.
inline CellStruct Coord2Cell(const CoordStruct& coords)
{
    CellStruct c;
    c.X = (short)(coords.X / 256);
    c.Y = (short)(coords.Y / 256);
    return c;
}

struct MapClass
{
    // CellStruct overload @ 0x578460 — declared (no body) so cl emits a
    // reloc-normalised __thiscall to it from the CoordStruct overload.
    bool IsWithinUsableArea(const CellStruct& cell, bool checkLevel) const;

    // The matched function @ 0x5785F0.
    bool IsWithinUsableArea(const CoordStruct& coords) const;
};

#endif  // GG_MATCH_MAP_MAP_CLASS_AREA_METHODS_H
