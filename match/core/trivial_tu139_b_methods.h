// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU139_B_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU139_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005BCC40;
struct Obj_005BCC60;

// GLOBAL: GAMEMD 0xABF239
extern unsigned char DAT_00ABF239;
// GLOBAL: GAMEMD 0xABF23A
extern unsigned char DAT_00ABF23A;
// GLOBAL: GAMEMD 0xABF240
extern int DAT_00ABF240;

// Import ShowWindow from USER32.dll (IAT slot 0x7E1498)
extern "C" __declspec(dllimport) void __stdcall ShowWindow(int, int);

#include "../_layout/obj_005bcc40.h"

struct Obj_005BCC60
{
    char unknown_00[0x2724];
    int unknown_2724;   // +0x2724
    int unknown_2728;   // +0x2728
    int unknown_272C;   // +0x272C
    int unknown_2730;   // +0x2730
    // FUNCTION: GAMEMD 0x5BCC60
    void FUN_005BCC60(int a1, int a2, int a3, int a4);
};
GG_STATIC_ASSERT(offsetof(Obj_005BCC60, unknown_2724) == 0x2724);
GG_STATIC_ASSERT(offsetof(Obj_005BCC60, unknown_2728) == 0x2728);
GG_STATIC_ASSERT(offsetof(Obj_005BCC60, unknown_272C) == 0x272C);
GG_STATIC_ASSERT(offsetof(Obj_005BCC60, unknown_2730) == 0x2730);

// FUNCTION: GAMEMD 0x5BC400
void __cdecl FUN_005BC400();
#endif  // GG_MATCH_CORE_TRIVIAL_TU139_B_METHODS_H
