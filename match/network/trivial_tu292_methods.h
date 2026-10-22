// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_NETWORK_TRIVIAL_TU292_METHODS_H
#define GG_MATCH_NETWORK_TRIVIAL_TU292_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_007B6280;

// FUNCTION: GAMEMD 0x7C9BFD (declaration)
int __cdecl FUN_007C9BFD(int);

struct Obj_007B6280
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x7B6280
    int FUN_007B6280();
};
GG_STATIC_ASSERT(offsetof(Obj_007B6280, unknown_00) == 0x0);



#endif  // GG_MATCH_NETWORK_TRIVIAL_TU292_METHODS_H
