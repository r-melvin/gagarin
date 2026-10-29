// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_0053EDA0_H_H
#define GG_MATCH__LAYOUT_OBJ_0053EDA0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "triple_0053eda0.h"

struct Obj_0053EDA0
{
    int unknown_0;
    Triple_0053EDA0 unknown_4;

    void FUN_0053EDA0(int* first, Triple_0053EDA0* rest) const;
};
GG_STATIC_ASSERT(offsetof(Obj_0053EDA0, unknown_4) == 4);
#endif
