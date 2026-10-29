// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_PAIR_00487F20_H_H
#define GG_MATCH__LAYOUT_PAIR_00487F20_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Pair_00487F20
{
    int unknown_0;
    int unknown_4;

    Pair_00487F20() {}
    Pair_00487F20(int a, int b) : unknown_0(a), unknown_4(b) {}
    Pair_00487F20 FUN_00487F20(const Pair_00487F20& other) const;
};
GG_STATIC_ASSERT(sizeof(Pair_00487F20) == 8);
#endif
