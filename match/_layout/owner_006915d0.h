// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OWNER_006915D0_H_H
#define GG_MATCH__LAYOUT_OWNER_006915D0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Owner_006915D0
{
    char Pad_00[0xA0];
    unsigned int unknown_A0;
};
GG_STATIC_ASSERT(offsetof(Owner_006915D0, unknown_A0) == 0xA0);
#endif
