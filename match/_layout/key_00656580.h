// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_KEY_00656580_H_H
#define GG_MATCH__LAYOUT_KEY_00656580_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Key_00656580
{
    char Pad_00[0xEF0];
    int unknown_EF0;
};
GG_STATIC_ASSERT(offsetof(Key_00656580, unknown_EF0) == 0xEF0);
#endif
