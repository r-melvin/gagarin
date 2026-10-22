// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_COMBAT_TRIVIAL_TU172_METHODS_H
#define GG_MATCH_COMBAT_TRIVIAL_TU172_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg2_00628DD0;
struct Obj_00628DD0;

struct Arg2_00628DD0
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Arg2_00628DD0, unknown_00) == 0x0);

struct Obj_00628DD0
{
    char unknown_00[0x100];
    int unknown_100;   // +0x0100
    // FUNCTION: GAMEMD 0x4F4C70
    void FUN_004F4C70(int);
    // FUNCTION: GAMEMD 0x628DD0
    Obj_00628DD0* FUN_00628DD0(int a1, Arg2_00628DD0* a2);
};
GG_STATIC_ASSERT(offsetof(Obj_00628DD0, unknown_100) == 0x100);



#endif  // GG_MATCH_COMBAT_TRIVIAL_TU172_METHODS_H
