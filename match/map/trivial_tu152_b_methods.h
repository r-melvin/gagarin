// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_MAP_TRIVIAL_TU152_B_METHODS_H
#define GG_MATCH_MAP_TRIVIAL_TU152_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005CC6A0;

struct Obj_005CC6A0
{
    char unknown_00[0x28];
    int unknown_28;   // +0x0028
    char unknown_2C[0x14];
    int unknown_40;   // +0x0040
    // FUNCTION: GAMEMD 0x5CC6A0
    void FUN_005CC6A0(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_005CC6A0, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(Obj_005CC6A0, unknown_40) == 0x40);



#endif  // GG_MATCH_MAP_TRIVIAL_TU152_B_METHODS_H
