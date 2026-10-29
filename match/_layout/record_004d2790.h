// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_RECORD_004D2790_H_H
#define GG_MATCH__LAYOUT_RECORD_004D2790_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "obj_004d2790.h"

struct Record_004D2790
{
    char Pad_00[0x30];
    int unknown_30;
    char Pad_34[0x60 - 0x34];
    Obj_004D2790** unknown_60;
};
GG_STATIC_ASSERT(offsetof(Record_004D2790, unknown_60) == 0x60);
#endif
