// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU053_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU053_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0048BA90;

struct Obj_0048BA90
{
    char unknown_00[0x20];
    int unknown_20;   // +0x0020
    // FUNCTION: GAMEMD 0x48BA90
    int FUN_0048BA90() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0048BA90, unknown_20) == 0x20);



#endif  // GG_MATCH_CORE_TRIVIAL_TU053_METHODS_H
