// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_VTBL_004D2790_H_H
#define GG_MATCH__LAYOUT_VTBL_004D2790_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "obj_004d2790.h"

typedef void* (Obj_004D2790::*Fn_004D2790)(int);

struct Vtbl_004D2790
{
    char Pad_00[0x90];
    Fn_004D2790 At_90;
};

#endif
