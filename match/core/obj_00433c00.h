// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH_CORE_OBJ_00433C00_H_H
#define GG_MATCH_CORE_OBJ_00433C00_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00433C00
{
    char  _pad00[0x18];
    void* unknown_18;   // +0x0018
    void* unknown_1C;   // +0x001C
    char  _pad20[4];
    short unknown_24;   // +0x0024
    char  _pad26[0x41 - 0x26];
    unsigned char unknown_41;   // +0x0041

    // FUNCTION: GAMEMD 0x433C00
    void FUN_00433C00();
    // FUNCTION: GAMEMD 0x433C70
    short FUN_00433C70(short value);
    // FUNCTION: GAMEMD 0x433C90
    unsigned char FUN_00433C90(unsigned char value);
};
GG_STATIC_ASSERT(offsetof(Obj_00433C00, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(Obj_00433C00, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_00433C00, unknown_41) == 0x41);

#endif
