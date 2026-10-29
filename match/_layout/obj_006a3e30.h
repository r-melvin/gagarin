// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_006A3E30_H_H
#define GG_MATCH__LAYOUT_OBJ_006A3E30_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006A3E30 {
    unsigned char unknown_00[0xC];
    int unknown_0C;
    int FUN_006A3E30(int arg);
};
GG_STATIC_ASSERT(offsetof(Obj_006A3E30, unknown_0C) == 0x0C);
#endif
