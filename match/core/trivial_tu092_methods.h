// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU092_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU092_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004F2B40;
struct Obj_004F2B50;

struct Obj_004F2B40
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x4F2B40
    Obj_004F2B40* FUN_004F2B40();
};
GG_STATIC_ASSERT(offsetof(Obj_004F2B40, unknown_08) == 0x8);

struct Obj_004F2B50
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x4F2B50
    Obj_004F2B50* FUN_004F2B50();
};
GG_STATIC_ASSERT(offsetof(Obj_004F2B50, unknown_08) == 0x8);


// FUNCTION: GAMEMD 0x4F1710
void __cdecl FUN_004F1710();

#endif  // GG_MATCH_CORE_TRIVIAL_TU092_METHODS_H
