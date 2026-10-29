// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_MAP_TRIVIAL_TU152_METHODS_H
#define GG_MATCH_MAP_TRIVIAL_TU152_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005CC690;
struct Obj_005CC740;

struct Obj_005CC690
{
    char unknown_00[0x40];
    int unknown_40;   // +0x0040
    // FUNCTION: GAMEMD 0x5CC690
    void FUN_005CC690();
};
GG_STATIC_ASSERT(offsetof(Obj_005CC690, unknown_40) == 0x40);

struct Obj_005CC740
{
    char unknown_00[0xC];
    bool unknown_0C;   // +0x000C
    char unknown_0D[0x33];
    unsigned int unknown_40;   // +0x0040
    // FUNCTION: GAMEMD 0x5CC740
    int FUN_005CC740();
};
GG_STATIC_ASSERT(offsetof(Obj_005CC740, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_005CC740, unknown_40) == 0x40);


// FUNCTION: GAMEMD 0x5CD310
void __cdecl FUN_005CD310();

#endif  // GG_MATCH_MAP_TRIVIAL_TU152_METHODS_H
