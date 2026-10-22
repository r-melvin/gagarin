// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU008_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU008_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x887058
extern char DAT_00887058[];
// GLOBAL: GAMEMD 0x8870C0
extern char DAT_008870C0[];
// GLOBAL: GAMEMD 0x887128
extern char DAT_00887128[];
// GLOBAL: GAMEMD 0x887180
extern char DAT_00887180[];
// GLOBAL: GAMEMD 0x887208
extern char DAT_00887208[];

// FUNCTION: GAMEMD 0x5256F0 (declaration)
void FUN_005256F0(void*, int);


// FUNCTION: GAMEMD 0x40E050
void FUN_0040E050(int a1, int a2);
// FUNCTION: GAMEMD 0x40E100
void FUN_0040E100(int a1, int a2);
// FUNCTION: GAMEMD 0x40E1B0
void FUN_0040E1B0(int a1, int a2);
// FUNCTION: GAMEMD 0x40E260
void FUN_0040E260(int a1, int a2);
// FUNCTION: GAMEMD 0x40E310
void FUN_0040E310(int a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU008_METHODS_H
