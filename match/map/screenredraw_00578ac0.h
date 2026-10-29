// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH_MAP_SCREENREDRAW_00578AC0_H_H
#define GG_MATCH_MAP_SCREENREDRAW_00578AC0_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct ScreenRedraw_00578AC0 {
    char unknown_000[0x1158];
    unsigned char redrawCounter; // +0x1158
    // FUNCTION: GAMEMD 0x578AC0 (decl; reloc) -- bump the redraw counter.
    void FUN_00578AC0();
};
GG_STATIC_ASSERT(offsetof(ScreenRedraw_00578AC0, redrawCounter) == 0x1158);

GG_STATIC_ASSERT(sizeof(ScreenRedraw_00578AC0) == 0x1159);

#endif
