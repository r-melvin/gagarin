// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_OBJ_005FBF80_H_H
#define GG_MATCH__LAYOUT_OBJ_005FBF80_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef struct HWND__* HWND;

struct Obj_005FBF80
{
    char unknown_00[0x4C];
    int unknown_4C;         // +0x4C last soviet entry unlocked
    int unknown_50;         // +0x50 last allied entry unlocked
    // FUNCTION: GAMEMD 0x5FBF80
    void FUN_005FBF80(const char* name);
    // FUNCTION: GAMEMD 0x5FC000
    void FUN_005FC000(HWND list);
};
GG_STATIC_ASSERT(offsetof(Obj_005FBF80, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_005FBF80, unknown_50) == 0x50);

#endif
