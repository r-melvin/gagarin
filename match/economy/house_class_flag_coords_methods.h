// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4FBE40: the object's WhatAmI slot `[EAX+0x2C]`
//   (compared with 1, UNIT) and GetCoords slot `[EDX+0x48]` (hidden 12-byte
//   buffer at [ESP+0x10], X / Y divided by 256 into a CellStruct built in
//   the first parameter's home slot [ESP+0x20] and copied to [ESP+0xC]);
//   the house's `[EDI+0x53DC]` (flag carrier, compared with the object and
//   zeroed) and `[EDI+0x53E0]` (flag cell, compared word-wise with the
//   sentinel at 0xA8EF98 / 0xA8EF9A and overwritten by a dword copy); the
//   cell's `[EAX+0x44]` stored -1; UnitClass 0x740E20 (__thiscall, no
//   arguments, AL); the map object 0x87F7E8 with CoordinatesLegal 0x568300
//   (one pushed cell pointer, AL) and GetCellAt 0x5657A0 (one pushed cell
//   pointer, cell pointer in EAX); CellClass 0x483460 (__thiscall, no
//   arguments, AL). Names cross-checked against YRpp
//   (UpdateFlagCoords, OurFlagCarrier, OurFlagCoords
//   ) and re-derived here.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_FLAG_COORDS_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_FLAG_COORDS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/house_class.h"
#include "../_layout/unit_class.h"
#include "../_layout/cell_class.h"
#include "../_layout/cell.h"

// Coordinate to cell (signed division by 256 per axis), by value. Cell has a
// constructor, so VC6 returns it through a hidden pointer.
inline Cell CoordToCell_004FBE40(const CoordStruct& c)
{
    Cell r;
    r.X = (short)(c.X / 256);
    r.Y = (short)(c.Y / 256);
    return r;
}

struct Map_004FBE40
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x568300 (decl; reloc) — MapClass::CoordinatesLegal.
    bool CoordinatesLegal(const CellStruct& cell);
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    CellClass* GetCellAt(const CellStruct& cell);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer).
extern Map_004FBE40 DAT_0087F7E8;

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_FLAG_COORDS_METHODS_H
