// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_NODE_00751040_H_H
#define GG_MATCH__LAYOUT_NODE_00751040_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "holder_00751040.h"

struct Node_00751040
{
    char Pad_00[0x0C];
    Holder_00751040 unknown_C;
    char Pad_0D[0x30 - 0x0D];
    int unknown_30;

    Node_00751040* FUN_004073E0();
};
GG_STATIC_ASSERT(offsetof(Node_00751040, unknown_30) == 0x30);
#endif
