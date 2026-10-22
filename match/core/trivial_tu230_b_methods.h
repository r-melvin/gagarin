// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU230_B_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU230_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Gbl_0087F7E8;

// GLOBAL: GAMEMD 0x87F7E8
extern Gbl_0087F7E8 DAT_0087F7E8;

struct Gbl_0087F7E8
{
    // FUNCTION: GAMEMD 0x4F42F0
    void FUN_004F42F0(int);
    // FUNCTION: GAMEMD 0x588AC0
    void FUN_00588AC0();
};


// FUNCTION: GAMEMD 0x6E2C20
bool __stdcall FUN_006E2C20(int a1, int a2, int a3, int a4);

#endif  // GG_MATCH_CORE_TRIVIAL_TU230_B_METHODS_H
