// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU244_B_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU244_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0071FA30;

struct Obj_0071FA30
{
    char unknown_00[0x54];
    int unknown_54;   // +0x0054
    // FUNCTION: GAMEMD 0x71FA30
    int FUN_0071FA30() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0071FA30, unknown_54) == 0x54);

#endif  // GG_MATCH_CORE_TRIVIAL_TU244_B_METHODS_H
