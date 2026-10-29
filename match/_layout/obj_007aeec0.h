// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_007AEEC0_H_H
#define GG_MATCH__LAYOUT_OBJ_007AEEC0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_007AEEC0 {
    int count;     // +0x00
    int capacity;  // +0x04
    int* data;     // +0x08
    bool FUN_007AEEC0();
};
GG_STATIC_ASSERT(offsetof(Obj_007AEEC0, data) == 0x08);
#endif
