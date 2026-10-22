// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU177_B_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU177_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00631E30;

// FUNCTION: GAMEMD 0x631D40 (declaration)
void FUN_00631D40(Obj_00631E30*, int, int);

struct Obj_00631E30
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Obj_00631E30, unknown_00) == 0x0);


// FUNCTION: GAMEMD 0x631E30
Obj_00631E30* FUN_00631E30(Obj_00631E30* a1, int a2, int a3);

#endif  // GG_MATCH_CORE_TRIVIAL_TU177_B_METHODS_H
