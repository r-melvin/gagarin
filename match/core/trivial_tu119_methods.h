// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU119_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU119_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00556620;
struct Obj_00556630;

struct Obj_00556620
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
    // FUNCTION: GAMEMD 0x556620
    int FUN_00556620() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00556620, unknown_04) == 0x4);

struct Obj_00556630
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x556630
    int FUN_00556630() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00556630, unknown_08) == 0x8);



#endif  // GG_MATCH_CORE_TRIVIAL_TU119_METHODS_H
