// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU095_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU095_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg2_0050E450;
struct Obj_004F7850;
struct Obj_0050C160;
struct Obj_0050C160_34;
struct Obj_0050DA40;
struct Obj_0050E430;
struct Obj_0050E450;

struct Arg2_0050E450
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Arg2_0050E450, unknown_00) == 0x0);

struct Obj_004F7850
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
    int unknown_0C;   // +0x000C
    int unknown_10;   // +0x0010
    // FUNCTION: GAMEMD 0x4F7850
    Obj_004F7850* FUN_004F7850();
};
GG_STATIC_ASSERT(offsetof(Obj_004F7850, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_004F7850, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_004F7850, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_004F7850, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_004F7850, unknown_10) == 0x10);

struct Obj_0050C160
{
    char unknown_00[0x34];
    Obj_0050C160_34* unknown_34;   // +0x0034
    // FUNCTION: GAMEMD 0x50C160
    float FUN_0050C160() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0050C160, unknown_34) == 0x34);

struct Obj_0050C160_34
{
    char unknown_00[0x148];
    float unknown_148;   // +0x0148
};
GG_STATIC_ASSERT(offsetof(Obj_0050C160_34, unknown_148) == 0x148);

struct Obj_0050DA40
{
    char unknown_00[0x54F8];
    int unknown_54F8;   // +0x54F8
    // FUNCTION: GAMEMD 0x50DA40
    void FUN_0050DA40(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0050DA40, unknown_54F8) == 0x54F8);

struct Obj_0050E430
{
    unsigned char unknown_00;   // +0x0000
    unsigned char unknown_01;   // +0x0001
    unsigned char unknown_02;   // +0x0002
    // FUNCTION: GAMEMD 0x50E430
    void FUN_0050E430(unsigned char a1, unsigned char a2, unsigned char a3);
};
GG_STATIC_ASSERT(offsetof(Obj_0050E430, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_0050E430, unknown_01) == 0x1);
GG_STATIC_ASSERT(offsetof(Obj_0050E430, unknown_02) == 0x2);

struct Obj_0050E450
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
    unsigned char unknown_08;   // +0x0008
    char unknown_09[0x3];
    int unknown_0C;   // +0x000C
    // FUNCTION: GAMEMD 0x50E450
    Obj_0050E450* FUN_0050E450(int a1, Arg2_0050E450* a2);
};
GG_STATIC_ASSERT(offsetof(Obj_0050E450, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_0050E450, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_0050E450, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_0050E450, unknown_0C) == 0xC);


// FUNCTION: GAMEMD 0x506B70
void __cdecl FUN_00506B70();
// FUNCTION: GAMEMD 0x506B80
void __cdecl FUN_00506B80();
// FUNCTION: GAMEMD 0x509CC0
void __stdcall FUN_00509CC0(int a1);
// FUNCTION: GAMEMD 0x50FF40
void __cdecl FUN_0050FF40();

#endif  // GG_MATCH_CORE_TRIVIAL_TU095_METHODS_H
