// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU293_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU293_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_007B7D80;

// GLOBAL: GAMEMD 0xB78164
extern int DAT_00B78164;
// GLOBAL: GAMEMD 0xB7816C
extern int DAT_00B7816C;

// FUNCTION: GAMEMD 0x7BA090 (declaration)
void FUN_007BA090(int, int);
// FUNCTION: GAMEMD 0x7CB9B8 (declaration)
void __cdecl FUN_007CB9B8(int, int, int);

struct Obj_007B7D80
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x7B7D80
    void FUN_007B7D80();
};
GG_STATIC_ASSERT(offsetof(Obj_007B7D80, unknown_00) == 0x0);


// FUNCTION: GAMEMD 0x7B84D0
void FUN_007B84D0(int a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU293_METHODS_H
