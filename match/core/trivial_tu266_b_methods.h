// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU266_B_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU266_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_007598D0;

// FUNCTION: GAMEMD 0x7C30D0 (declaration)
int FUN_007C30D0(int, int, int);

struct Obj_007598D0
{
    char unknown_00[0x200];
    int unknown_200;   // +0x0200
    char unknown_204[0x300];
    int unknown_504;   // +0x0504
    // FUNCTION: GAMEMD 0x7598D0
    void FUN_007598D0(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_007598D0, unknown_200) == 0x200);
GG_STATIC_ASSERT(offsetof(Obj_007598D0, unknown_504) == 0x504);



#endif  // GG_MATCH_CORE_TRIVIAL_TU266_B_METHODS_H
