// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_00407F40_H_H
#define GG_MATCH__LAYOUT_OBJ_00407F40_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Worker_00407F40 { void FUN_004025B0(); };   // GAMEMD 0x4025B0

struct Obj_00407F40
{
    char               _pad000[0x14];
    Worker_00407F40*   unknown_14;   // +0x0014
    char               _pad18[0x88 - 0x18];
    int                unknown_88;   // +0x0088

    // FUNCTION: GAMEMD 0x407F40 (decl; reloc) -- stop the streamer.
    void FUN_00407F40();
};
GG_STATIC_ASSERT(offsetof(Obj_00407F40, unknown_88) == 0x88);

#endif
