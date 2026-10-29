// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_RECT_4I_H
#define GG_MATCH__LAYOUT_RECT_4I_H

#include "../_rt/gg_static_assert.h"

// Four ints: x, y, width, height.
struct Rect_4i
{
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0C;
};
GG_STATIC_ASSERT(sizeof(Rect_4i) == 0x10);

#endif
