// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_005657A0_H_H
#define GG_MATCH__LAYOUT_OBJ_005657A0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "cell_0050def0.h"
#include "entry_005657a0.h"

struct Obj_005657A0
{
    char Pad_00[0x13C];
    Entry_005657A0** unknown_13C;

    Entry_005657A0* FUN_005657A0(const Cell_0050DEF0& cell) const;
};
GG_STATIC_ASSERT(offsetof(Obj_005657A0, unknown_13C) == 0x13C);
#endif
