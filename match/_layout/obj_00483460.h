// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00483460_H_H
#define GG_MATCH__LAYOUT_OBJ_00483460_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00483460
{
    char Pad_00[0x50];
    int unknown_50;
    char Pad_54[0x140 - 0x54];
    unsigned int unknown_140;
};
GG_STATIC_ASSERT(offsetof(Obj_00483460, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(Obj_00483460, unknown_140) == 0x140);
#endif
