// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_004CA160_H_H
#define GG_MATCH__LAYOUT_OBJ_004CA160_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004CA160
{
    char Pad_00[0x58];
    int unknown_58;
};
GG_STATIC_ASSERT(offsetof(Obj_004CA160, unknown_58) == 0x58);
#endif
