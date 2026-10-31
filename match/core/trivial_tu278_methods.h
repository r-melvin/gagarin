// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU278_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU278_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0076F000;

// FUNCTION: GAMEMD 0x76FF40 (declaration)
void FUN_0076FF40(int, void*, int);

struct Obj_0076F000
{
    char unknown_00[0x2C];
    int unknown_2C;   // +0x002C
    // FUNCTION: GAMEMD 0x76F000
    int FUN_0076F000(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_0076F000, unknown_2C) == 0x2C);



#endif  // GG_MATCH_CORE_TRIVIAL_TU278_METHODS_H
