// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU188_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU188_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00659490;
struct Obj_006594E0;
struct Obj_006594F0;
struct Obj_00659510;
struct Obj_00659530;
struct Obj_00659540;
struct Obj_00659560;
struct Obj_00659570;

struct Obj_00659490
{
    char unknown_00[0xC];
    int unknown_0C;   // +0x000C
    // FUNCTION: GAMEMD 0x659490
    void FUN_00659490(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00659490, unknown_0C) == 0xC);

struct Obj_006594E0
{
    char unknown_00[0x3C];
    int unknown_3C;   // +0x003C
    // FUNCTION: GAMEMD 0x6594E0
    void FUN_006594E0(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_006594E0, unknown_3C) == 0x3C);

struct Obj_006594F0
{
    char unknown_00[0x40];
    int unknown_40;   // +0x0040
    int unknown_44;   // +0x0044
    // FUNCTION: GAMEMD 0x6594F0
    void FUN_006594F0(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006594F0, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(Obj_006594F0, unknown_44) == 0x44);

struct Obj_00659510
{
    char unknown_00[0x48];
    int unknown_48;   // +0x0048
    int unknown_4C;   // +0x004C
    // FUNCTION: GAMEMD 0x659510
    void FUN_00659510(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_00659510, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(Obj_00659510, unknown_4C) == 0x4C);

struct Obj_00659530
{
    char unknown_00[0x50];
    int unknown_50;   // +0x0050
    // FUNCTION: GAMEMD 0x659530
    void FUN_00659530(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00659530, unknown_50) == 0x50);

struct Obj_00659540
{
    char unknown_00[0x54];
    int unknown_54;   // +0x0054
    // FUNCTION: GAMEMD 0x659540
    void FUN_00659540(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00659540, unknown_54) == 0x54);

struct Obj_00659560
{
    char unknown_00[0x9];
    unsigned char unknown_09;   // +0x0009
    // FUNCTION: GAMEMD 0x659560
    void FUN_00659560();
};
GG_STATIC_ASSERT(offsetof(Obj_00659560, unknown_09) == 0x9);

struct Obj_00659570
{
    char unknown_00[0x9];
    unsigned char unknown_09;   // +0x0009
    // FUNCTION: GAMEMD 0x659570
    unsigned char FUN_00659570() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00659570, unknown_09) == 0x9);



#endif  // GG_MATCH_CORE_TRIVIAL_TU188_METHODS_H
