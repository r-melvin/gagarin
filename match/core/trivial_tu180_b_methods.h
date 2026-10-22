// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU180_B_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU180_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0063D540;

// FUNCTION: GAMEMD 0x731CD0 (declaration)
int FUN_00731CD0(Obj_0063D540*, int);
// FUNCTION: GAMEMD 0x731CE0 (declaration)
int FUN_00731CE0(Obj_0063D540*, int);

struct Obj_0063D540
{
    char unknown_00[0xC];
    char unknown_0C;   // +0x000C
};
GG_STATIC_ASSERT(offsetof(Obj_0063D540, unknown_0C) == 0xC);


// FUNCTION: GAMEMD 0x63D540
int FUN_0063D540(Obj_0063D540* a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU180_B_METHODS_H
