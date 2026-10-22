// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU200_B_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU200_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_00681200;
struct Arg1_00681240;
struct Arg1_00681280;
struct Obj_006810D0;
struct Obj_00681150;
struct Obj_006811C0;
struct Obj_00681200;
struct Obj_00681240;
struct Obj_00681280;

// FUNCTION: GAMEMD 0x7C91D0 (declaration)
void __cdecl FUN_007C91D0(void*, int, int);
// FUNCTION: GAMEMD 0x7CA422 (declaration)
void __cdecl FUN_007CA422(void*, int, int);

struct Arg1_00681200
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_00681200, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Arg1_00681200, unknown_04) == 0x4);

struct Arg1_00681240
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_00681240, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Arg1_00681240, unknown_04) == 0x4);

struct Arg1_00681280
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_00681280, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Arg1_00681280, unknown_04) == 0x4);

struct Obj_006810D0
{
    char unknown_00[0x108];
    int unknown_108;   // +0x0108
    char unknown_10C[0x7A];
    unsigned short unknown_186;   // +0x0186
    // FUNCTION: GAMEMD 0x6810D0
    void FUN_006810D0(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_006810D0, unknown_108) == 0x108);
GG_STATIC_ASSERT(offsetof(Obj_006810D0, unknown_186) == 0x186);

struct Obj_00681150
{
    char unknown_00[0x190];
    int unknown_190;   // +0x0190
    char unknown_194[0xFF];
    unsigned char unknown_293;   // +0x0293
    // FUNCTION: GAMEMD 0x681150
    void FUN_00681150(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00681150, unknown_190) == 0x190);
GG_STATIC_ASSERT(offsetof(Obj_00681150, unknown_293) == 0x293);

struct Obj_006811C0
{
    char unknown_00[0x2D4];
    int unknown_2D4;   // +0x02D4
    char unknown_2D8[0xFF];
    unsigned char unknown_3D7;   // +0x03D7
    // FUNCTION: GAMEMD 0x6811C0
    void FUN_006811C0(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_006811C0, unknown_2D4) == 0x2D4);
GG_STATIC_ASSERT(offsetof(Obj_006811C0, unknown_3D7) == 0x3D7);

struct Obj_00681200
{
    char unknown_00[0x3D8];
    int unknown_3D8;   // +0x03D8
    int unknown_3DC;   // +0x03DC
    // FUNCTION: GAMEMD 0x681200
    void FUN_00681200(Arg1_00681200* a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00681200, unknown_3D8) == 0x3D8);
GG_STATIC_ASSERT(offsetof(Obj_00681200, unknown_3DC) == 0x3DC);

struct Obj_00681240
{
    char unknown_00[0x3E0];
    int unknown_3E0;   // +0x03E0
    int unknown_3E4;   // +0x03E4
    // FUNCTION: GAMEMD 0x681240
    void FUN_00681240(Arg1_00681240* a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00681240, unknown_3E0) == 0x3E0);
GG_STATIC_ASSERT(offsetof(Obj_00681240, unknown_3E4) == 0x3E4);

struct Obj_00681280
{
    char unknown_00[0x3E8];
    int unknown_3E8;   // +0x03E8
    int unknown_3EC;   // +0x03EC
    // FUNCTION: GAMEMD 0x681280
    void FUN_00681280(Arg1_00681280* a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00681280, unknown_3E8) == 0x3E8);
GG_STATIC_ASSERT(offsetof(Obj_00681280, unknown_3EC) == 0x3EC);



#endif  // GG_MATCH_CORE_TRIVIAL_TU200_B_METHODS_H
