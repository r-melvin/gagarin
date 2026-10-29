// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_007BCF90_H_H
#define GG_MATCH__LAYOUT_OBJ_007BCF90_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "rect_007bcf90.h"
#include "surface_007bcf90.h"

struct Obj_007BCF90 {
    unsigned char unknown_00[0x14];
    Surface_007BCF90* unknown_14;
    bool FUN_007BCF90(unsigned short color, Rect_007BCF90 area);
};
GG_STATIC_ASSERT(offsetof(Obj_007BCF90, unknown_14) == 0x14);
#endif
