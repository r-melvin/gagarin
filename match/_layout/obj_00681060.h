// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00681060_H_H
#define GG_MATCH__LAYOUT_OBJ_00681060_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00681060 {
    unsigned char unknown_00[0x4];
    int unknown_04;
    void FUN_00681060(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00681060, unknown_04) == 0x4);
#endif
