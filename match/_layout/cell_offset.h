// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001: the (short, short) cell constructor at 0x42D470
//   (called 492 times, expanded inline by VC6 until its inliner budget runs
//   out in the big static tables at 0x561910, 0x5A9C40 and 0x45C300) stores
//   two words. Its inline cost is what the two cut-offs measure -- 288 of 369
//   entries expanded in 0x561910, 55 of 109 slots in 0x5A9C40 -- and a plain
//   two-store body is expanded everywhere. The body that reproduces both is a
//   (short, short) constructor that forwards to an (int, int) constructor of
//   the coordinate-pair base.
#ifndef GG_MATCH_LAYOUT_CELL_OFFSET_H
#define GG_MATCH_LAYOUT_CELL_OFFSET_H

#include "../_rt/gg_static_assert.h"
#include <stddef.h>

// The coordinate pair as retail's constructor chain sees it: two words, built
// from ints, zero by default.
struct CellWords
{
    short X;   // +0x00
    short Y;   // +0x02
    CellWords() { X = 0; Y = 0; }
    CellWords(int x, int y) { X = x; Y = y; }
};

// Constructor at 0x42D470 (row owned by match/core/small_struct_ctor_methods.cpp, which
// models the out-of-line copy that call sites outside the big tables keep).
class CellOffset : public CellWords
{
public:
    CellOffset() {}
    CellOffset(short x, short y) : CellWords(x, y) {}
};
GG_STATIC_ASSERT(sizeof(CellOffset) == 4);
GG_STATIC_ASSERT(offsetof(CellOffset, X) == 0);
GG_STATIC_ASSERT(offsetof(CellOffset, Y) == 2);

#endif  // GG_MATCH_LAYOUT_CELL_OFFSET_H
