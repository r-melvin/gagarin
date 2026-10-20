// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x413A30. Not bound by YRpp or the seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC31_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC31_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The result is built in a four-byte stack slot and copied out with one dword
// move, so the copy constructor stays implicit; the user-declared default
// constructor is what forces the memory return in the first place.
struct CellPair
{
    short x;   // +0x0000
    short y;   // +0x0002

    CellPair() { }
};

struct Coord2i
{
    int X;   // +0x0000
    int Y;   // +0x0004

    // FUNCTION: GAMEMD 0x413A30
    CellPair FUN_00413A30() const;
};
GG_STATIC_ASSERT(offsetof(Coord2i, Y) == 0x4);

#endif  // GG_MATCH_CORE_SMALL_MISC31_METHODS_H
