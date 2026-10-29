// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_0069B540_H_H
#define GG_MATCH__LAYOUT_OBJ_0069B540_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0069B540
{
    char Pad_00[0x24];
    int unknown_24;
    char Pad_28[0x4C - 0x28];
    int unknown_4C[8];
    int unknown_6C[8];
};
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_0069B540, unknown_6C) == 0x6C);
#endif
