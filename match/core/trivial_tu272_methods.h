// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU272_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU272_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00766FA0;
struct Obj_00766FB0;

struct Obj_00766FA0
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x766FA0
    Obj_00766FA0* FUN_00766FA0();
};
GG_STATIC_ASSERT(offsetof(Obj_00766FA0, unknown_08) == 0x8);

struct Obj_00766FB0
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x766FB0
    Obj_00766FB0* FUN_00766FB0();
};
GG_STATIC_ASSERT(offsetof(Obj_00766FB0, unknown_08) == 0x8);



#endif  // GG_MATCH_CORE_TRIVIAL_TU272_METHODS_H
