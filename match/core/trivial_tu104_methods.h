// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU104_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU104_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA9F9CC
extern int DAT_00A9F9CC;
// GLOBAL: GAMEMD 0xA9F9F8
extern int DAT_00A9F9F8;
// GLOBAL: GAMEMD 0xA9FA48
extern int DAT_00A9FA48;
// GLOBAL: GAMEMD 0xA9FAB4
extern unsigned char DAT_00A9FAB4;
// GLOBAL: GAMEMD 0xA9FABC
extern int DAT_00A9FABC;
// GLOBAL: GAMEMD 0xA9FAC0
extern int DAT_00A9FAC0;


// FUNCTION: GAMEMD 0x539EA0
void FUN_00539EA0(int a1);
// FUNCTION: GAMEMD 0x53A110
bool __cdecl FUN_0053A110();
// FUNCTION: GAMEMD 0x53A120
bool __cdecl FUN_0053A120();
// FUNCTION: GAMEMD 0x53B3F0
void __cdecl FUN_0053B3F0();
// FUNCTION: GAMEMD 0x53B400
bool __cdecl FUN_0053B400();

#endif  // GG_MATCH_CORE_TRIVIAL_TU104_METHODS_H
