// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00485060_H_H
#define GG_MATCH__LAYOUT_OBJ_00485060_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00485060
{
    char Pad_00[0x38];
    int unknown_38;
};
GG_STATIC_ASSERT(offsetof(Obj_00485060, unknown_38) == 0x38);
#endif
