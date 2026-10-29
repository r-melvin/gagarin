// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_CURSOR_006915D0_H_H
#define GG_MATCH__LAYOUT_CURSOR_006915D0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "owner_006915d0.h"

struct Cursor_006915D0
{
    char Pad_00[0x24];
    Owner_006915D0* unknown_24;
    char Pad_28[4];
    unsigned int unknown_2C;
};
GG_STATIC_ASSERT(offsetof(Cursor_006915D0, unknown_2C) == 0x2C);
#endif
