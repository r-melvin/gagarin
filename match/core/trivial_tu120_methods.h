// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU120_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU120_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00556B30;
struct Obj_00556B30_4;

struct Obj_00556B30
{
    char unknown_00[0x4];
    Obj_00556B30_4* unknown_04;   // +0x0004
    // FUNCTION: GAMEMD 0x556B30
    void FUN_00556B30();
};
GG_STATIC_ASSERT(offsetof(Obj_00556B30, unknown_04) == 0x4);

struct Obj_00556B30_4
{
    char unknown_00[0xA8];
    int unknown_A8;   // +0x00A8
};
GG_STATIC_ASSERT(offsetof(Obj_00556B30_4, unknown_A8) == 0xA8);



#endif  // GG_MATCH_CORE_TRIVIAL_TU120_METHODS_H
