// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00542FC0_H_H
#define GG_MATCH__LAYOUT_OBJ_00542FC0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "obj_005402b0.h"

struct Obj_00542FC0
{
    char Pad_00[0x48];
    Obj_005402B0* unknown_48;

    void FUN_00542FC0(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00542FC0, unknown_48) == 0x48);
#endif
