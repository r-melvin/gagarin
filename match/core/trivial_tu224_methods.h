// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU224_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU224_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006C9930;
struct Obj_006C9AC0;
struct Obj_006C9D30;
struct Obj_006CA7B0;

// FUNCTION: GAMEMD 0x6C9960 (declaration)
void FUN_006C9960(int, int, Obj_006CA7B0*);
// LIBRARY: GAMEMD 0x7C8B3D (declaration)
void __cdecl FUN_007C8B3D(int);

struct Obj_006C9930
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
    // FUNCTION: GAMEMD 0x6C9930
    void FUN_006C9930();
};
GG_STATIC_ASSERT(offsetof(Obj_006C9930, unknown_14) == 0x14);

struct Obj_006C9AC0
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
    int unknown_0C;   // +0x000C
    int unknown_10;   // +0x0010
    int unknown_14;   // +0x0014
    int unknown_18;   // +0x0018
    int unknown_1C;   // +0x001C
    int unknown_20;   // +0x0020
    // FUNCTION: GAMEMD 0x6C9AC0
    Obj_006C9AC0* FUN_006C9AC0();
};
GG_STATIC_ASSERT(offsetof(Obj_006C9AC0, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_006C9AC0, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_006C9AC0, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_006C9AC0, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_006C9AC0, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_006C9AC0, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_006C9AC0, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Obj_006C9AC0, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(Obj_006C9AC0, unknown_20) == 0x20);

struct Obj_006C9D30
{
    char unknown_00[0xC];
    int unknown_0C;   // +0x000C
    // FUNCTION: GAMEMD 0x6C9D30
    void FUN_006C9D30(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_006C9D30, unknown_0C) == 0xC);

struct Obj_006CA7B0
{
};


// FUNCTION: GAMEMD 0x6CA7B0
void FUN_006CA7B0(Obj_006CA7B0* a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU224_METHODS_H
