// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU264_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU264_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00754900;

// GLOBAL: GAMEMD 0x846614
extern int DAT_00846614;
// GLOBAL: GAMEMD 0xB1D3D8
extern int DAT_00B1D3D8;
// GLOBAL: GAMEMD 0xB2D7F0
extern int DAT_00B2D7F0;
// GLOBAL: GAMEMD 0xB2D804
extern char DAT_00B2D804[];
// GLOBAL: GAMEMD 0xB2D928
extern int DAT_00B2D928;
// GLOBAL: GAMEMD 0xB2D93C
extern char DAT_00B2D93C[];
// GLOBAL: GAMEMD 0xB2FF78
extern char DAT_00B2FF78[];

// FUNCTION: GAMEMD 0x43AE50 (declaration)
void FUN_0043AE50(void*, int);

struct Obj_00754900
{
    // FUNCTION: GAMEMD 0x754900
    Obj_00754900* FUN_00754900();
};


// FUNCTION: GAMEMD 0x752AB0
void FUN_00752AB0(int a1);
// FUNCTION: GAMEMD 0x7533A0
bool __cdecl FUN_007533A0();
// FUNCTION: GAMEMD 0x753570
int __cdecl FUN_00753570();
// FUNCTION: GAMEMD 0x753A30
void FUN_00753A30(int a1, int a2);
// FUNCTION: GAMEMD 0x753AB0
void FUN_00753AB0(int a1, int a2);
// FUNCTION: GAMEMD 0x753AD0
void __cdecl FUN_00753AD0();
// FUNCTION: GAMEMD 0x753AE0
void __cdecl FUN_00753AE0();
// FUNCTION: GAMEMD 0x753C60
void* __cdecl FUN_00753C60();

#endif  // GG_MATCH_CORE_TRIVIAL_TU264_METHODS_H
