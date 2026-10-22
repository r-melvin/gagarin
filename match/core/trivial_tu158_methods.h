// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU158_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU158_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005D8FB0;

struct Obj_005D8FB0
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
    int unknown_0C;   // +0x000C
    // FUNCTION: GAMEMD 0x5D8FB0
    Obj_005D8FB0* FUN_005D8FB0();
};
GG_STATIC_ASSERT(offsetof(Obj_005D8FB0, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_005D8FB0, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_005D8FB0, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_005D8FB0, unknown_0C) == 0xC);



#endif  // GG_MATCH_CORE_TRIVIAL_TU158_METHODS_H
