// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU286_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU286_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0077A760;
struct Obj_0077A780;
struct Obj_0077A7A0;
struct Obj_0077A870;
struct Obj_0077A890;
struct Obj_0077A8B0;

// GLOBAL: GAMEMD 0x849F58
extern char DAT_00849F58[];
// GLOBAL: GAMEMD 0xB73590
extern char DAT_00B73590[];

// FUNCTION: GAMEMD 0x7B4630 (declaration)
void FUN_007B4630(void*, int, void*);
// FUNCTION: GAMEMD 0x7B46F0 (declaration)
void FUN_007B46F0(void*, int);
// FUNCTION: GAMEMD 0x7C978A (declaration)
void __cdecl FUN_007C978A(int);

struct Obj_0077A760
{
    char unknown_00[0x8];
    unsigned char unknown_08;   // +0x0008
    char unknown_09[0x2F];
    unsigned char unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x77A760
    unsigned char FUN_0077A760(unsigned char a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0077A760, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_0077A760, unknown_38) == 0x38);

struct Obj_0077A780
{
    char unknown_00[0x8];
    unsigned char unknown_08;   // +0x0008
    char unknown_09[0x13];
    int unknown_1C;   // +0x001C
    // FUNCTION: GAMEMD 0x77A780
    int FUN_0077A780(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0077A780, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_0077A780, unknown_1C) == 0x1C);

struct Obj_0077A7A0
{
    char unknown_00[0x8];
    unsigned char unknown_08;   // +0x0008
    char unknown_09[0x17];
    int unknown_20;   // +0x0020
    // FUNCTION: GAMEMD 0x77A7A0
    int FUN_0077A7A0(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0077A7A0, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_0077A7A0, unknown_20) == 0x20);

struct Obj_0077A870
{
    char unknown_00[0x8];
    unsigned char unknown_08;   // +0x0008
    char unknown_09[0x23];
    int unknown_2C;   // +0x002C
    // FUNCTION: GAMEMD 0x77A870
    void FUN_0077A870(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0077A870, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_0077A870, unknown_2C) == 0x2C);

struct Obj_0077A890
{
    char unknown_00[0x8];
    unsigned char unknown_08;   // +0x0008
    char unknown_09[0x27];
    int unknown_30;   // +0x0030
    // FUNCTION: GAMEMD 0x77A890
    void FUN_0077A890(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0077A890, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_0077A890, unknown_30) == 0x30);

struct Obj_0077A8B0
{
    char unknown_00[0x8];
    unsigned char unknown_08;   // +0x0008
    char unknown_09[0x2B];
    int unknown_34;   // +0x0034
    // FUNCTION: GAMEMD 0x77A8B0
    void FUN_0077A8B0(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0077A8B0, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_0077A8B0, unknown_34) == 0x34);


// FUNCTION: GAMEMD 0x7786E0
void FUN_007786E0(int a1, int a2);
// FUNCTION: GAMEMD 0x778700
void FUN_00778700(int a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU286_METHODS_H
