// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00426A70_H_H
#define GG_MATCH__LAYOUT_OBJ_00426A70_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00426A70 {
    unsigned char unknown_00[0xA0];
    unsigned short unknown_A0;
    int FUN_00426A70();
};
GG_STATIC_ASSERT(offsetof(Obj_00426A70, unknown_A0) == 0xA0);
#endif
