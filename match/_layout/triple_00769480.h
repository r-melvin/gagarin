// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_TRIPLE_00769480_H_H
#define GG_MATCH__LAYOUT_TRIPLE_00769480_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class Triple_00769480
{
public:
    // FUNCTION: GAMEMD 0x769480
    Triple_00769480();

    int unknown_00;   // +0x00
    int unknown_04;   // +0x04
    int unknown_08;   // +0x08
};
GG_STATIC_ASSERT(offsetof(Triple_00769480, unknown_08) == 0x08);
#endif
