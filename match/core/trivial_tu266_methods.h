// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU266_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU266_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00759810;
struct Obj_00759810_200;
struct Obj_00759830;
struct Obj_00759E60;
struct Obj_00759E80;
struct Obj_00759E80_0;
struct Obj_00759E80_200;

// FUNCTION: GAMEMD 0x4A4780 (declaration)
void FUN_004A4780(int, int);
// FUNCTION: GAMEMD 0x7C2C60 (declaration)
void FUN_007C2C60(int, int);

struct Obj_00759810
{
    char unknown_00[0x200];
    Obj_00759810_200* unknown_200;   // +0x0200
    // FUNCTION: GAMEMD 0x759810
    int FUN_00759810();
};
GG_STATIC_ASSERT(offsetof(Obj_00759810, unknown_200) == 0x200);

struct Obj_00759810_200
{
    unsigned short unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Obj_00759810_200, unknown_00) == 0x0);

struct Obj_00759830
{
    char unknown_00[0x1DC];
    int unknown_1DC;   // +0x01DC
    // FUNCTION: GAMEMD 0x759830
    int FUN_00759830(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00759830, unknown_1DC) == 0x1DC);

struct Obj_00759E60
{
    char unknown_00[0x200];
    int unknown_200;   // +0x0200
    char unknown_204[0x310];
    unsigned char unknown_514;   // +0x0514
};
GG_STATIC_ASSERT(offsetof(Obj_00759E60, unknown_200) == 0x200);
GG_STATIC_ASSERT(offsetof(Obj_00759E60, unknown_514) == 0x514);

struct Obj_00759E80
{
    Obj_00759E80_0* unknown_00;   // +0x0000
    char unknown_04[0x1FC];
    Obj_00759E80_200* unknown_200;   // +0x0200
    // FUNCTION: GAMEMD 0x759E80
    void FUN_00759E80();
};
GG_STATIC_ASSERT(offsetof(Obj_00759E80, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_00759E80, unknown_200) == 0x200);

struct Obj_00759E80_0
{
    // FUNCTION: GAMEMD 0x6C9D20
    void FUN_006C9D20();
};

struct Obj_00759E80_200
{
    // FUNCTION: GAMEMD 0x7C35C0
    void FUN_007C35C0();
};


// FUNCTION: GAMEMD 0x759790
void FUN_00759790(int a1, int a2);
// FUNCTION: GAMEMD 0x759E60
void FUN_00759E60(Obj_00759E60* a1, int a2);
// FUNCTION: GAMEMD 0x75A400
int __cdecl FUN_0075A400();
// FUNCTION: GAMEMD 0x75A410
void __cdecl FUN_0075A410();
// FUNCTION: GAMEMD 0x75A420
void __cdecl FUN_0075A420();

#endif  // GG_MATCH_CORE_TRIVIAL_TU266_METHODS_H
