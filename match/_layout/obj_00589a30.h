// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00589A30_H_H
#define GG_MATCH__LAYOUT_OBJ_00589A30_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00589A30 {
    unsigned char unknown_00[4];
    unsigned char* unknown_04;
    unsigned char unknown_08[4];
    bool unknown_0C;
    unsigned int FUN_00589A30(const void* item) const;
};
GG_STATIC_ASSERT(offsetof(Obj_00589A30, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_00589A30, unknown_0C) == 0x0C);
#endif
