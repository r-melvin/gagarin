// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU099_B_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU099_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0051F640;

// FUNCTION: GAMEMD 0x521320 (declaration)
int FUN_00521320(Obj_0051F640*, int);

struct Obj_0051F640
{
    // FUNCTION: GAMEMD 0x4D6AA0
    void FUN_004D6AA0();
};


// FUNCTION: GAMEMD 0x51F640
void FUN_0051F640(Obj_0051F640* a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU099_B_METHODS_H
