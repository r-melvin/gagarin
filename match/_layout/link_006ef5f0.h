// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_LINK_006EF5F0_H_H
#define GG_MATCH__LAYOUT_LINK_006EF5F0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Link_006EF5F0
{
    char Pad_00[0xF0];
    int unknown_F0;
    char Pad_F4[0x5D8 - 0xF4];
    Link_006EF5F0* unknown_5D8;
};
GG_STATIC_ASSERT(offsetof(Link_006EF5F0, unknown_F0) == 0xF0);
GG_STATIC_ASSERT(offsetof(Link_006EF5F0, unknown_5D8) == 0x5D8);
#endif
