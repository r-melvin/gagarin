// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU090_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU090_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x8229C0
extern char DAT_008229C0[];
// GLOBAL: GAMEMD 0x822B90
extern char DAT_00822B90[];

// FUNCTION: GAMEMD 0x734E60 (declaration)
void FUN_00734E60(void*, int, void*, int);


// FUNCTION: GAMEMD 0x4E4F30
void __cdecl FUN_004E4F30();
// FUNCTION: GAMEMD 0x4E6140
void __cdecl FUN_004E6140();

#endif  // GG_MATCH_CORE_TRIVIAL_TU090_METHODS_H
