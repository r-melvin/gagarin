// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_006EF5F0_H_H
#define GG_MATCH__LAYOUT_OBJ_006EF5F0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "link_006ef5f0.h"

struct Obj_006EF5F0
{
    char Pad_00[0x54];
    Link_006EF5F0* unknown_54;

    void FUN_006EF5F0(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_006EF5F0, unknown_54) == 0x54);
#endif
