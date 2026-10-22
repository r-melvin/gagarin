// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The run-time initialiser shapes that open many retail translation units: a
// header-level group of globals each TU gets its own copy of. Each copy is
// initialised by three compiler-generated functions in __xc order:
//   A = X / 60.0     (FLD [X]; FDIV [the TU's own 60.0]; FSTP [A])
//   B = 1.0 / A      (FLD [1.0]; FDIV [A]; FSTP [B])
//   C = {128, 128, 0}  (MOV EAX,0x80; Z = 0; X = EAX; Y = EAX)
// C's initialiser exists only because its type had a constructor (a brace
// initialiser would be static data); the tree's CoordStruct is an aggregate,
// so this view supplies one, storing in the order retail does.
#ifndef GG_MATCH_CORE_HEADER_INIT_SHAPES_H
#define GG_MATCH_CORE_HEADER_INIT_SHAPES_H

#include "../_rt/gg_static_assert.h"

#ifndef GG_MATCH_LAYOUT_COORDSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_COORDSTRUCT_DEFINED
struct CoordStruct
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08
};
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);
#endif  // GG_MATCH_LAYOUT_COORDSTRUCT_DEFINED

struct HeaderCoordInit : CoordStruct
{
    HeaderCoordInit(int x, int y, int z) { X = x; Y = y; Z = z; }
};
GG_STATIC_ASSERT(sizeof(HeaderCoordInit) == 0xC);

#endif  // GG_MATCH_CORE_HEADER_INIT_SHAPES_H
