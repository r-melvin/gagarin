// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00705D20_H_H
#define GG_MATCH__LAYOUT_OBJ_00705D20_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00705D20
{
    char Pad_00[0x514];
    int unknown_514;
};
GG_STATIC_ASSERT(offsetof(Obj_00705D20, unknown_514) == 0x514);
#endif
