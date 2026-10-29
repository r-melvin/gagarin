// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_004A50F0_H_H
#define GG_MATCH__LAYOUT_OBJ_004A50F0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004A50F0
{
    int unknown_0;
    int unknown_4;
    int unknown_8;
    int unknown_C;
    int unknown_10;
    int unknown_14;
    char unknown_18;
    char unknown_19;

    Obj_004A50F0();
    bool FUN_004A5130() const;
    bool FUN_004A51B0() const;
    bool FUN_004A51D0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004A50F0, unknown_18) == 0x18);
#endif
