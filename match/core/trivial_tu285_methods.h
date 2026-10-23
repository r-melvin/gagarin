// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU285_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU285_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xB7355C
extern int DAT_00B7355C;

// LIBRARY: GAMEMD 0x7C8A3A (declaration)
void __stdcall FUN_007C8A3A(int, int);


// FUNCTION: GAMEMD 0x777AB0
void __cdecl FUN_00777AB0();
// FUNCTION: GAMEMD 0x778130
void __cdecl FUN_00778130();
// FUNCTION: GAMEMD 0x778150
void __cdecl FUN_00778150();

#endif  // GG_MATCH_CORE_TRIVIAL_TU285_METHODS_H
