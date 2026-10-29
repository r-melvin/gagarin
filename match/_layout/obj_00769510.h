// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00769510_H_H
#define GG_MATCH__LAYOUT_OBJ_00769510_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00769510 {
    int unknown_00;
    int unknown_04;
    int unknown_08;
    bool FUN_00769510(const Obj_00769510* other) const;
};
GG_STATIC_ASSERT(offsetof(Obj_00769510, unknown_08) == 0x08);
#endif
