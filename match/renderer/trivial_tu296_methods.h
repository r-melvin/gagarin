// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_RENDERER_TRIVIAL_TU296_METHODS_H
#define GG_MATCH_RENDERER_TRIVIAL_TU296_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_007C3950;

// GLOBAL: GAMEMD 0x84E7C0
extern char DAT_0084E7C0[];
// GLOBAL: GAMEMD 0x84E7C4
extern char DAT_0084E7C4[];

struct Obj_007C3950
{
    char unknown_00[0x148];
    int unknown_148;   // +0x0148
};
GG_STATIC_ASSERT(offsetof(Obj_007C3950, unknown_148) == 0x148);


// FUNCTION: GAMEMD 0x7BF220
void __cdecl FUN_007BF220();
// FUNCTION: GAMEMD 0x7C36C0
void* __cdecl FUN_007C36C0();
// FUNCTION: GAMEMD 0x7C3740
void* __cdecl FUN_007C3740();
// FUNCTION: GAMEMD 0x7C3950
void FUN_007C3950(Obj_007C3950* a1, int a2);

#endif  // GG_MATCH_RENDERER_TRIVIAL_TU296_METHODS_H
