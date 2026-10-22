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
struct Obj_005BD570;

// GLOBAL: GAMEMD 0xABF239
extern unsigned char DAT_00ABF239;
// GLOBAL: GAMEMD 0xABF23A
extern unsigned char DAT_00ABF23A;
// GLOBAL: GAMEMD 0xABF240
extern int DAT_00ABF240;

// FUNCTION: GAMEMD 0x5BD5C0 (declaration)
int FUN_005BD5C0(Obj_005BD570*, int, int);
// Import ShowWindow from USER32.dll (IAT slot 0x7E1498)
extern "C" __declspec(dllimport) void __stdcall ShowWindow(int, int);

struct Obj_005BCC40
{
    char unknown_00[0x271C];
    int unknown_271C;   // +0x271C
    int unknown_2720;   // +0x2720
    // FUNCTION: GAMEMD 0x5BCC40
    void FUN_005BCC40(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_271C) == 0x271C);
GG_STATIC_ASSERT(offsetof(Obj_005BCC40, unknown_2720) == 0x2720);

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

struct Obj_005BD570
{
    unsigned char unknown_00;   // +0x0000
    char unknown_01[0x3];
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
    int unknown_0C;   // +0x000C
};
GG_STATIC_ASSERT(offsetof(Obj_005BD570, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_005BD570, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_005BD570, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_005BD570, unknown_0C) == 0xC);


// FUNCTION: GAMEMD 0x5BC400
void __cdecl FUN_005BC400();
// FUNCTION: GAMEMD 0x5BD570
Obj_005BD570* FUN_005BD570(Obj_005BD570* a1, int a2, int a3);

#endif  // GG_MATCH_CORE_TRIVIAL_TU139_B_METHODS_H
