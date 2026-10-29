// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_004870B0_H_H
#define GG_MATCH__LAYOUT_OBJ_004870B0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004870B0
{
    char Pad_00[0x78];
    int unknown_78;

    int FUN_004870B0(int bit) const;
};
GG_STATIC_ASSERT(offsetof(Obj_004870B0, unknown_78) == 0x78);
#endif
