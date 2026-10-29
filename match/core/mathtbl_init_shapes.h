// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The math-table header group that opens many retail translation units: each TU
// gets its own copy of a handful of doubles/ints derived from pow(), two helper
// calls and the double constants at 0x7E1708-0x7E1740, plus four small
// zero-initialised members whose constructors the compiler left as stores in
// the static initialisers.
#ifndef GG_MATCH_CORE_MATHTBL_INIT_SHAPES_H
#define GG_MATCH_CORE_MATHTBL_INIT_SHAPES_H

#include "../_rt/gg_static_assert.h"
#include "../_layout/coord_struct.h"

struct MathTblShortPair
{
    short X;
    short Y;
    MathTblShortPair() : X(0), Y(0) {}
};
GG_STATIC_ASSERT(sizeof(MathTblShortPair) == 4);

struct MathTblZero3 : CoordStruct
{
    MathTblZero3() { X = 0; Y = 0; Z = 0; }
};
GG_STATIC_ASSERT(sizeof(MathTblZero3) == 0xC);

struct MathTblZero4
{
    int A;
    int B;
    int C;
    int D;
    MathTblZero4() : A(0), B(0), C(0), D(0) {}
};
GG_STATIC_ASSERT(sizeof(MathTblZero4) == 0x10);

struct MathTblCoord
{
    int X;
    int Y;
    int Z;
    MathTblCoord() : X(128), Y(128), Z(0) {}
};
GG_STATIC_ASSERT(sizeof(MathTblCoord) == 0xC);

#endif  // GG_MATCH_CORE_MATHTBL_INIT_SHAPES_H
