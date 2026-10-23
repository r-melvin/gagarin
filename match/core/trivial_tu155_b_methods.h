// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU155_B_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU155_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005D5820;

// FUNCTION: GAMEMD 0x407000 (declaration)
int __cdecl FUN_00407000();
// LIBRARY: GAMEMD 0x7D5408 (declaration)
int __cdecl FUN_007D5408(int);

struct Obj_005D5820
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
    unsigned char unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x5D5820
    Obj_005D5820* FUN_005D5820(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_005D5820, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_005D5820, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_005D5820, unknown_08) == 0x8);



#endif  // GG_MATCH_CORE_TRIVIAL_TU155_B_METHODS_H
