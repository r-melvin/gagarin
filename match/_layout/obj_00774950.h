// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00774950_H_H
#define GG_MATCH__LAYOUT_OBJ_00774950_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef void* HANDLE;

struct Obj_00774950
{
    char Pad_00[0x5C];
    HANDLE unknown_5C;
};
GG_STATIC_ASSERT(offsetof(Obj_00774950, unknown_5C) == 0x5C);
#endif
