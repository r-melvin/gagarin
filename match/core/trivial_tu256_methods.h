// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU256_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU256_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x87F7E8
extern char DAT_0087F7E8[];
// GLOBAL: GAMEMD 0xA8B538
extern int DAT_00A8B538;
// GLOBAL: GAMEMD 0xB0FE58
extern unsigned char DAT_00B0FE58;
// GLOBAL: GAMEMD 0xB0FE65
extern unsigned char DAT_00B0FE65;
// GLOBAL: GAMEMD 0xB0FE68
extern int DAT_00B0FE68;

// FUNCTION: GAMEMD 0x4AC960 (declaration)
void FUN_004AC960(void*, int, int);
// FUNCTION: GAMEMD 0x637AA0 (declaration)
void __cdecl FUN_00637AA0();
// Import timeGetTime from WINMM.dll (IAT slot 0x7E1530)
extern "C" __declspec(dllimport) int __stdcall timeGetTime();


// FUNCTION: GAMEMD 0x730AD0
int __cdecl FUN_00730AD0();
// FUNCTION: GAMEMD 0x730AE0
int __cdecl FUN_00730AE0();
// FUNCTION: GAMEMD 0x731A30
void FUN_00731A30(int a1, int a2);
// FUNCTION: GAMEMD 0x731A90
void __cdecl FUN_00731A90();
// FUNCTION: GAMEMD 0x731BE0
void __cdecl FUN_00731BE0();
// FUNCTION: GAMEMD 0x731CF0
void __cdecl FUN_00731CF0();
// FUNCTION: GAMEMD 0x732CA0
void __cdecl FUN_00732CA0();

#endif  // GG_MATCH_CORE_TRIVIAL_TU256_METHODS_H
