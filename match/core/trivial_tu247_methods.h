// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU247_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU247_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_007236E0;
struct Obj_007236F0;
struct Obj_00723700;

struct Obj_007236E0
{
    // FUNCTION: GAMEMD 0x7236E0
    int FUN_007236E0() const;
};

struct Obj_007236F0
{
    // FUNCTION: GAMEMD 0x7236F0
    int FUN_007236F0() const;
};

struct Obj_00723700
{
    char unknown_00[0x98];
    int unknown_98;   // +0x0098
    // FUNCTION: GAMEMD 0x723700
    int FUN_00723700() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00723700, unknown_98) == 0x98);



#endif  // GG_MATCH_CORE_TRIVIAL_TU247_METHODS_H
