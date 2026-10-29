// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_006B5440_H_H
#define GG_MATCH__LAYOUT_OBJ_006B5440_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006B5440 {
    unsigned char unknown_00[0x24];
    char ID[1];                     // +0x24, name buffer
    static int FUN_006B5440(const char* name);
};
#endif
