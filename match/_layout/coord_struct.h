// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// CoordStruct: absolute 3D lepton coordinate, three ints (sizeof 0xC).
// A plain aggregate: matched by-value users (PlanningNodeClass 0x6343C0,
// 0x634810, 0x634850; CellClass::GetCoords 0x486840) store the three ints
// inline and regress when the type gains any constructor.
#ifndef GG_MATCH_LAYOUT_COORD_STRUCT_H
#define GG_MATCH_LAYOUT_COORD_STRUCT_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CoordStruct
{
    int X;  // +0x00
    int Y;  // +0x04
    int Z;  // +0x08

    // Retail helpers, declared with their raw result-pointer ABI.
    // FUNCTION: GAMEMD 0x41C230 (decl; reloc) -- builds the coordinate in place
    // and returns it (__thiscall, RET 0xC).
    CoordStruct* FUN_0041C230(int x, int y, int z);
    // FUNCTION: GAMEMD 0x41C380 (decl; reloc) -- the length of the vector.
    int FUN_0041C380();
    // FUNCTION: GAMEMD 0x437160 (decl; reloc) -- writes this minus `rhs` into
    // `out` and returns it (__thiscall, RET 8).
    CoordStruct* FUN_00437160(CoordStruct* out, const CoordStruct* rhs);
};
GG_STATIC_ASSERT(offsetof(CoordStruct, X) == 0x00);
GG_STATIC_ASSERT(offsetof(CoordStruct, Y) == 0x04);
GG_STATIC_ASSERT(offsetof(CoordStruct, Z) == 0x08);
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0x0C);

#endif  // GG_MATCH_LAYOUT_COORD_STRUCT_H
