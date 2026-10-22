// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x433CA0. Not bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC27_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC27_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Quad_00433CA0 { int a, b, c, d; };

struct Obj_00433CA0
{
    char _pad00[0x30];
    int  unknown_30;   // +0x0030
    int  unknown_34;   // +0x0034
    int  unknown_38;   // +0x0038
    int  unknown_3C;   // +0x003C

    // FUNCTION: GAMEMD 0x433CA0
    void FUN_00433CA0(const Quad_00433CA0* src);
};
GG_STATIC_ASSERT(offsetof(Obj_00433CA0, unknown_3C) == 0x3C);

#endif  // GG_MATCH_CORE_SMALL_MISC27_METHODS_H
