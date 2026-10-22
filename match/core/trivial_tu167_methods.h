// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU167_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU167_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005FBF70;

struct Obj_005FBF70
{
    char unknown_00[0xC];
    int unknown_0C;   // +0x000C
    // FUNCTION: GAMEMD 0x5FBF70
    int FUN_005FBF70() const;
};
GG_STATIC_ASSERT(offsetof(Obj_005FBF70, unknown_0C) == 0xC);



#endif  // GG_MATCH_CORE_TRIVIAL_TU167_METHODS_H
