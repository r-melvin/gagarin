// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_AI_TRIVIAL_TU251_METHODS_H
#define GG_MATCH_AI_TRIVIAL_TU251_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/trigger_type_class.h"

struct Obj_00727CC0;

struct Obj_00727CC0
{
    char unknown_00[0x98];
    int unknown_98;   // +0x0098
    // FUNCTION: GAMEMD 0x727CC0
    int FUN_00727CC0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00727CC0, unknown_98) == 0x98);



#endif  // GG_MATCH_AI_TRIVIAL_TU251_METHODS_H
