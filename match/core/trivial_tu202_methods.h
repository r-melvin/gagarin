// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU202_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU202_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00690F20;

// FUNCTION: GAMEMD 0x7C93E8 (declaration)
void __cdecl FUN_007C93E8(int);

struct Obj_00690F20
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x690F20
    void FUN_00690F20();
};
GG_STATIC_ASSERT(offsetof(Obj_00690F20, unknown_00) == 0x0);


// FUNCTION: GAMEMD 0x690150
void __cdecl FUN_00690150();

#endif  // GG_MATCH_CORE_TRIVIAL_TU202_METHODS_H
