// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU000_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU000_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00401FB0;
struct Obj_00402020;
struct Obj_00402850;
struct Obj_00403490;
struct Obj_004034A0;

// FUNCTION: GAMEMD 0x407150 (declaration)
void FUN_00407150(int, int);
// FUNCTION: GAMEMD 0x407170 (declaration)
void FUN_00407170(int, int);

struct Obj_00401FB0
{
    char unknown_00[0xC];
    int unknown_0C;   // +0x000C
    // FUNCTION: GAMEMD 0x401FB0
    int FUN_00401FB0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00401FB0, unknown_0C) == 0xC);

struct Obj_00402020
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
    // FUNCTION: GAMEMD 0x402020
    int FUN_00402020() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00402020, unknown_14) == 0x14);

struct Obj_00402850
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x402850
    void FUN_00402850();
};
GG_STATIC_ASSERT(offsetof(Obj_00402850, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00402850, unknown_08) == 0x8);

struct Obj_00403490
{
    char unknown_00[0xF4];
    int unknown_F4;   // +0x00F4
    // FUNCTION: GAMEMD 0x403490
    int FUN_00403490() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00403490, unknown_F4) == 0xF4);

struct Obj_004034A0
{
    char unknown_00[0xF0];
    int unknown_F0;   // +0x00F0
    // FUNCTION: GAMEMD 0x4034A0
    int FUN_004034A0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004034A0, unknown_F0) == 0xF0);


// FUNCTION: GAMEMD 0x403460
int __cdecl FUN_00403460();
// FUNCTION: GAMEMD 0x403470
void FUN_00403470(int a1, int a2);
// FUNCTION: GAMEMD 0x403480
void FUN_00403480(int a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU000_METHODS_H
