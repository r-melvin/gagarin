// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_ECONOMY_TRIVIAL_TU161_METHODS_H
#define GG_MATCH_ECONOMY_TRIVIAL_TU161_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Gbl_008870C0;
struct Obj_005E2F60;
struct Obj_005E3700;

// GLOBAL: GAMEMD 0x82642C
extern char DAT_0082642C[];
// GLOBAL: GAMEMD 0x831DA4
extern char DAT_00831DA4[];
// GLOBAL: GAMEMD 0x8870C0
extern Gbl_008870C0 DAT_008870C0;
// GLOBAL: GAMEMD 0xA8B322
extern char DAT_00A8B322[];
// GLOBAL: GAMEMD 0xA8DAB0
extern unsigned char DAT_00A8DAB0;
// GLOBAL: GAMEMD 0xAC10C8
extern int DAT_00AC10C8;
// GLOBAL: GAMEMD 0xAC116C
extern int DAT_00AC116C;

// FUNCTION: GAMEMD 0x5E23A0 (declaration)
int FUN_005E23A0(Obj_005E3700*, int);
// FUNCTION: GAMEMD 0x7A27D0 (declaration)
int FUN_007A27D0(Obj_005E3700*, int);
// Import SendMessageA from USER32.dll (IAT slot 0x7E14A4)
extern "C" __declspec(dllimport) void __stdcall SendMessageA(int, int, int, void*);
// Import GetDlgItem from USER32.dll (IAT slot 0x7E14A8)
extern "C" __declspec(dllimport) int __stdcall GetDlgItem(Obj_005E2F60*, int);

struct Gbl_008870C0
{
    // FUNCTION: GAMEMD 0x5276D0
    int FUN_005276D0(void*, void*, int);
};

struct Obj_005E2F60
{
    // FUNCTION: GAMEMD 0x5E2F60
    void FUN_005E2F60();
};

struct Obj_005E3700
{
};


// FUNCTION: GAMEMD 0x5E3700
int FUN_005E3700(Obj_005E3700* a1, int a2);
// FUNCTION: GAMEMD 0x5EE190
int __cdecl FUN_005EE190();

#endif  // GG_MATCH_ECONOMY_TRIVIAL_TU161_METHODS_H
