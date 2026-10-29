// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_006E81D0_H_H
#define GG_MATCH__LAYOUT_OBJ_006E81D0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006E81D0 {
    unsigned char unknown_00[0x64];
    char ID[1];                     // +0x64, name buffer
    static Obj_006E81D0* FUN_006E81D0(const char* name);
};
#endif
