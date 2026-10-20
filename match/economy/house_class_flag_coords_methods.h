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
//   arguments, AL). Names cross-checked against YRpp HouseClass.h
//   (UpdateFlagCoords, OurFlagCarrier, OurFlagCoords; consult-only, no
//   LICENSE) and re-derived here.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_FLAG_COORDS_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_FLAG_COORDS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// CellStruct — the user-declared constructor selects the hidden-pointer
// return convention for the inline coordinate-to-cell helper (see the banked
// "Struct returns" rule).
struct Cell_004FBE40
{
    short X;   // +0x0000
    short Y;   // +0x0002
    Cell_004FBE40() {}
};
GG_STATIC_ASSERT(sizeof(Cell_004FBE40) == 0x4);

struct Coord_004FBE40
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_004FBE40) == 0xC);

// Coordinate to cell (signed division by 256 per axis), by value.
inline Cell_004FBE40 CoordToCell_004FBE40(const Coord_004FBE40* c)
{
    Cell_004FBE40 r;
    r.X = (short)(c->X / 256);
    r.Y = (short)(c->Y / 256);
    return r;
}

// GLOBAL: GAMEMD 0xA8EF98 — the "no cell" CellStruct sentinel.
extern Cell_004FBE40 DAT_00A8EF98;

struct CellClass_004FBE40
{
    char _pad000[0x44];   // +0x0000
    int  At_44;           // +0x0044 — flag owner index, -1 when none.

    // FUNCTION: GAMEMD 0x483460 (decl; reloc) — take this cell's flag away;
    // true when there was one.
    bool FUN_00483460();
};
GG_STATIC_ASSERT(offsetof(CellClass_004FBE40, At_44) == 0x44);

struct Map_004FBE40
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x568300 (decl; reloc) — MapClass::CoordinatesLegal.
    bool CoordinatesLegal(const Cell_004FBE40& cell);
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    CellClass_004FBE40* GetCellAt(const Cell_004FBE40& cell);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer).
extern Map_004FBE40 DAT_0087F7E8;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_004FBE40;

// The flag carrier / flag holder: an ObjectClass, a UnitClass when WhatAmI
// says so.
struct Obj_004FBE40
{
    Vtbl_004FBE40* Vtbl;   // +0x0000

    // FUNCTION: GAMEMD 0x740E20 (decl; reloc) — UnitClass::FlagRemove; true
    // when the unit was carrying a flag.
    bool FlagRemove();
};

typedef int (Obj_004FBE40::*Fn2C_004FBE40)();
typedef Coord_004FBE40* (Obj_004FBE40::*Fn48_004FBE40)(Coord_004FBE40* out);

struct Vtbl_004FBE40
{
    char           _pad000[0x2C];   // +0x0000
    Fn2C_004FBE40  WhatAmI;         // +0x002C
    char           _pad030[0x18];   // +0x0030
    Fn48_004FBE40  GetCoords;       // +0x0048
};
GG_STATIC_ASSERT(offsetof(Vtbl_004FBE40, WhatAmI)   == 0x2C);
GG_STATIC_ASSERT(offsetof(Vtbl_004FBE40, GetCoords) == 0x48);

struct House_004FBE40
{
    char           _pad0000[0x53DC];   // +0x0000
    Obj_004FBE40*  OurFlagCarrier;     // +0x53DC
    Cell_004FBE40  OurFlagCoords;      // +0x53E0

    // FUNCTION: GAMEMD 0x4FBE40
    bool UpdateFlagCoords(Obj_004FBE40* obj, bool clearCell);
};
GG_STATIC_ASSERT(offsetof(House_004FBE40, OurFlagCarrier) == 0x53DC);
GG_STATIC_ASSERT(offsetof(House_004FBE40, OurFlagCoords)  == 0x53E0);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_FLAG_COORDS_METHODS_H
