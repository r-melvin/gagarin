// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00717880_H_H
#define GG_MATCH__LAYOUT_OBJ_00717880_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00717880
{
    char Pad_00[0x808];
    int unknown_808;
};
GG_STATIC_ASSERT(offsetof(Obj_00717880, unknown_808) == 0x808);
#endif
