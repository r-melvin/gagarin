// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail reads at 0x5BCB60 establish an output pair and three scale globals.
#ifndef GG_MATCH_CORE_COORDINATE_005BCB60_H
#define GG_MATCH_CORE_COORDINATE_005BCB60_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x00ABF1E0
extern int ABF1E0;
// GLOBAL: GAMEMD 0x00ABF1C8
extern int ABF1C8;
// GLOBAL: GAMEMD 0x00ABF1D8
extern int ABF1D8;

struct Point_005BCB60 {
    int X;
    int Y;

    // FUNCTION: GAMEMD 0x5BCB60
    Point_005BCB60* Convert(int x, int y);
};
GG_STATIC_ASSERT(offsetof(Point_005BCB60, X) == 0x0);
GG_STATIC_ASSERT(offsetof(Point_005BCB60, Y) == 0x4);
GG_STATIC_ASSERT(sizeof(Point_005BCB60) == 0x8);

#endif
