// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU043_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU043_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0046D350;
struct Obj_0046D480;
struct Obj_0046D490;
struct Obj_00470C30;

// GLOBAL: GAMEMD 0x89DFE0
extern char DAT_0089DFE0[];
// GLOBAL: GAMEMD 0x89E020
extern int DAT_0089E020;

// LIBRARY: GAMEMD 0x7C8B48 (declaration)
void __cdecl FUN_007C8B48(void*, int, int, int);

struct Obj_0046D350
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x46D350
    void FUN_0046D350();
};
GG_STATIC_ASSERT(offsetof(Obj_0046D350, unknown_00) == 0x0);

struct Obj_0046D480
{
    char unknown_00[0x89E000];
    unsigned char unknown_89E000;   // +0x89E000
};
GG_STATIC_ASSERT(offsetof(Obj_0046D480, unknown_89E000) == 0x89E000);

struct Obj_0046D490
{
    char unknown_00[0x89E000];
    unsigned char unknown_89E000;   // +0x89E000
    // FUNCTION: GAMEMD 0x46D490
    unsigned char FUN_0046D490() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0046D490, unknown_89E000) == 0x89E000);

struct Obj_00470C30
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x470C30
    void FUN_00470C30();
};
GG_STATIC_ASSERT(offsetof(Obj_00470C30, unknown_00) == 0x0);


// FUNCTION: GAMEMD 0x46D480
void FUN_0046D480(Obj_0046D480* a1, int a2);
// FUNCTION: GAMEMD 0x471400
void __cdecl FUN_00471400();

#endif  // GG_MATCH_CORE_TRIVIAL_TU043_METHODS_H
