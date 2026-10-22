// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU177_C_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU177_C_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00631EE0;

struct Obj_00631EE0
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x631EE0
    unsigned char FUN_00631EE0(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00631EE0, unknown_38) == 0x38);



#endif  // GG_MATCH_CORE_TRIVIAL_TU177_C_METHODS_H
