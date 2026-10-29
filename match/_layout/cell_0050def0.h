// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_CELL_0050DEF0_H_H
#define GG_MATCH__LAYOUT_CELL_0050DEF0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Cell_0050DEF0
{
    short X;
    short Y;

    Cell_0050DEF0() {}
    bool operator==(const Cell_0050DEF0& other) const
    {
        return X == other.X && Y == other.Y;
    }
    Cell_0050DEF0 operator+(const Cell_0050DEF0& other) const
    {
        Cell_0050DEF0 result;
        result.X = X + other.X;
        result.Y = Y + other.Y;
        return result;
    }
};
GG_STATIC_ASSERT(sizeof(Cell_0050DEF0) == 4);
GG_STATIC_ASSERT(offsetof(Cell_0050DEF0, X) == 0);
GG_STATIC_ASSERT(offsetof(Cell_0050DEF0, Y) == 2);
#endif
