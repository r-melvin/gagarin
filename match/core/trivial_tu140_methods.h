// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU140_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU140_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xABF294
extern int DAT_00ABF294;
// GLOBAL: GAMEMD 0xABF2DC
extern unsigned char DAT_00ABF2DC;

// FUNCTION: GAMEMD 0x69E500 (declaration)
void FUN_0069E500(int, int);
// LIBRARY: GAMEMD 0x7C8B3D (declaration)
void __cdecl FUN_007C8B3D(int);


// FUNCTION: GAMEMD 0x5BE940
void FUN_005BE940(int a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU140_METHODS_H
