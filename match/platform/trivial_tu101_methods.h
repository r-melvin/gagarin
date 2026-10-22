// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_PLATFORM_TRIVIAL_TU101_METHODS_H
#define GG_MATCH_PLATFORM_TRIVIAL_TU101_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00526950;

struct Obj_00526950
{
    char unknown_00[0x2C];
    int unknown_2C;   // +0x002C
    // FUNCTION: GAMEMD 0x526950
    int FUN_00526950() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00526950, unknown_2C) == 0x2C);



#endif  // GG_MATCH_PLATFORM_TRIVIAL_TU101_METHODS_H
