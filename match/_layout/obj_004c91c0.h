// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_004C91C0_H_H
#define GG_MATCH__LAYOUT_OBJ_004C91C0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004C91C0
{
    short unknown_0;
    short Pad_02;
    short unknown_4;
    short Pad_06;
    int unknown_8;
    int Pad_0C;
    int unknown_10;
    short unknown_14;

    Obj_004C91C0();
    Obj_004C91C0(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_004C91C0, unknown_14) == 0x14);
#endif
