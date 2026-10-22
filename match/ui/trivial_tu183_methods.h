// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_UI_TRIVIAL_TU183_METHODS_H
#define GG_MATCH_UI_TRIVIAL_TU183_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00643E60;
struct Obj_00643E70;

struct Obj_00643E60
{
    char unknown_00[0x64];
    int unknown_64;   // +0x0064
    // FUNCTION: GAMEMD 0x643E60
    bool FUN_00643E60() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00643E60, unknown_64) == 0x64);

struct Obj_00643E70
{
    char unknown_00[0x64];
    int unknown_64;   // +0x0064
    // FUNCTION: GAMEMD 0x643E70
    void FUN_00643E70();
};
GG_STATIC_ASSERT(offsetof(Obj_00643E70, unknown_64) == 0x64);



#endif  // GG_MATCH_UI_TRIVIAL_TU183_METHODS_H
