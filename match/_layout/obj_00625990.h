// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00625990_H_H
#define GG_MATCH__LAYOUT_OBJ_00625990_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00625990 {
    int count;     // +0x00
    int capacity;  // +0x04
    int* data;     // +0x08
    bool FUN_00625990();
};
GG_STATIC_ASSERT(offsetof(Obj_00625990, data) == 0x08);
#endif
