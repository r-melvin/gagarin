// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU275_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU275_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_00769C20;
struct Obj_00767EC0;
struct Obj_00769C20;
struct Obj_00769C40;
struct Obj_00769D70;
struct Obj_0076A5A0;
struct Obj_0076A5B0;

struct Arg1_00769C20
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
};
GG_STATIC_ASSERT(offsetof(Arg1_00769C20, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Arg1_00769C20, unknown_08) == 0x8);

struct Obj_00767EC0
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x5CB6C0
    void FUN_005CB6C0();
    // FUNCTION: GAMEMD 0x767EC0
    void FUN_00767EC0();
};
GG_STATIC_ASSERT(offsetof(Obj_00767EC0, unknown_00) == 0x0);

struct Obj_00769C20
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x769C20
    Obj_00769C20* FUN_00769C20(Arg1_00769C20* a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00769C20, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00769C20, unknown_08) == 0x8);

struct Obj_00769C40
{
    // FUNCTION: GAMEMD 0x769C40
    Obj_00769C40* FUN_00769C40();
};

struct Obj_00769D70
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
};
GG_STATIC_ASSERT(offsetof(Obj_00769D70, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_00769D70, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00769D70, unknown_08) == 0x8);

struct Obj_0076A5A0
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x76A5A0
    Obj_0076A5A0* FUN_0076A5A0();
};
GG_STATIC_ASSERT(offsetof(Obj_0076A5A0, unknown_08) == 0x8);

struct Obj_0076A5B0
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x76A5B0
    Obj_0076A5B0* FUN_0076A5B0();
};
GG_STATIC_ASSERT(offsetof(Obj_0076A5B0, unknown_08) == 0x8);


// FUNCTION: GAMEMD 0x769D70
Obj_00769D70* FUN_00769D70(Obj_00769D70* a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU275_METHODS_H
