// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU200_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU200_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_00681220;
struct Arg1_00681260;
struct Arg1_006812A0;
struct Obj_00681070;
struct Obj_006810A0;
struct Obj_00681180;
struct Obj_00681190;
struct Obj_006811F0;
struct Obj_00681220;
struct Obj_00681260;
struct Obj_006812A0;

// FUNCTION: GAMEMD 0x7C91D0 (declaration)
void __cdecl FUN_007C91D0(void*, int, int);
// FUNCTION: GAMEMD 0x7CA422 (declaration)
void __cdecl FUN_007CA422(void*, int, int);

struct Arg1_00681220
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_00681220, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Arg1_00681220, unknown_04) == 0x4);

struct Arg1_00681260
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_00681260, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Arg1_00681260, unknown_04) == 0x4);

struct Arg1_006812A0
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006812A0, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Arg1_006812A0, unknown_04) == 0x4);

struct Obj_00681070
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
    // FUNCTION: GAMEMD 0x681070
    int FUN_00681070() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00681070, unknown_04) == 0x4);

struct Obj_006810A0
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    char unknown_0C[0xFA];
    unsigned short unknown_106;   // +0x0106
    // FUNCTION: GAMEMD 0x6810A0
    void FUN_006810A0(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_006810A0, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_006810A0, unknown_106) == 0x106);

struct Obj_00681180
{
    char unknown_00[0x190];
    int unknown_190;   // +0x0190
    // FUNCTION: GAMEMD 0x681180
    int* FUN_00681180();
};
GG_STATIC_ASSERT(offsetof(Obj_00681180, unknown_190) == 0x190);

struct Obj_00681190
{
    char unknown_00[0x294];
    int unknown_294;   // +0x0294
    char unknown_298[0x3B];
    unsigned char unknown_2D3;   // +0x02D3
    // FUNCTION: GAMEMD 0x681190
    void FUN_00681190(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00681190, unknown_294) == 0x294);
GG_STATIC_ASSERT(offsetof(Obj_00681190, unknown_2D3) == 0x2D3);

struct Obj_006811F0
{
    char unknown_00[0x2D4];
    int unknown_2D4;   // +0x02D4
    // FUNCTION: GAMEMD 0x6811F0
    int* FUN_006811F0();
};
GG_STATIC_ASSERT(offsetof(Obj_006811F0, unknown_2D4) == 0x2D4);

struct Obj_00681220
{
    char unknown_00[0x3D8];
    int unknown_3D8;   // +0x03D8
    int unknown_3DC;   // +0x03DC
    // FUNCTION: GAMEMD 0x681220
    Arg1_00681220* FUN_00681220(Arg1_00681220* a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00681220, unknown_3D8) == 0x3D8);
GG_STATIC_ASSERT(offsetof(Obj_00681220, unknown_3DC) == 0x3DC);

struct Obj_00681260
{
    char unknown_00[0x3E0];
    int unknown_3E0;   // +0x03E0
    int unknown_3E4;   // +0x03E4
    // FUNCTION: GAMEMD 0x681260
    Arg1_00681260* FUN_00681260(Arg1_00681260* a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00681260, unknown_3E0) == 0x3E0);
GG_STATIC_ASSERT(offsetof(Obj_00681260, unknown_3E4) == 0x3E4);

struct Obj_006812A0
{
    char unknown_00[0x3E8];
    int unknown_3E8;   // +0x03E8
    int unknown_3EC;   // +0x03EC
    // FUNCTION: GAMEMD 0x6812A0
    Arg1_006812A0* FUN_006812A0(Arg1_006812A0* a1);
};
GG_STATIC_ASSERT(offsetof(Obj_006812A0, unknown_3E8) == 0x3E8);
GG_STATIC_ASSERT(offsetof(Obj_006812A0, unknown_3EC) == 0x3EC);


// FUNCTION: GAMEMD 0x67FDC0
void __cdecl FUN_0067FDC0();

#endif  // GG_MATCH_CORE_TRIVIAL_TU200_METHODS_H
