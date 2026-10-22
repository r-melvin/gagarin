// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_PLATFORM_TRIVIAL_TU058_METHODS_H
#define GG_MATCH_PLATFORM_TRIVIAL_TU058_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0049F9B0;

struct Obj_0049F9B0
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
    unsigned char unknown_0C;   // +0x000C
    unsigned char unknown_0D;   // +0x000D
    char unknown_0E[0x2];
    int unknown_10;   // +0x0010
    // FUNCTION: GAMEMD 0x49F9B0
    Obj_0049F9B0* FUN_0049F9B0();
};
GG_STATIC_ASSERT(offsetof(Obj_0049F9B0, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_0049F9B0, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_0049F9B0, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_0049F9B0, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_0049F9B0, unknown_0D) == 0xD);
GG_STATIC_ASSERT(offsetof(Obj_0049F9B0, unknown_10) == 0x10);



#endif  // GG_MATCH_PLATFORM_TRIVIAL_TU058_METHODS_H
