// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU002_C_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU002_C_METHODS_H

#include <stddef.h>
#include "triple_timer_init_methods.h"
#include "../_rt/gg_static_assert.h"

struct Obj_004080B0;

// FUNCTION: GAMEMD 0x407170 (declaration)

struct Obj_004080B0
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
    // FUNCTION: GAMEMD 0x4080B0
    void FUN_004080B0();
};
GG_STATIC_ASSERT(offsetof(Obj_004080B0, unknown_14) == 0x14);



#endif  // GG_MATCH_CORE_TRIVIAL_TU002_C_METHODS_H
