// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU165_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU165_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005F3D90;
struct Obj_005F3D90_A8;
struct Obj_005F6CB0;

// FUNCTION: GAMEMD 0x405FD0 (declaration)
void FUN_00405FD0(void*, int);

struct Obj_005F3D90
{
    char unknown_00[0xA8];
    Obj_005F3D90_A8* unknown_A8;   // +0x00A8
    // FUNCTION: GAMEMD 0x5F3D90
    void FUN_005F3D90();
};
GG_STATIC_ASSERT(offsetof(Obj_005F3D90, unknown_A8) == 0xA8);

struct Obj_005F3D90_A8
{
    // FUNCTION: GAMEMD 0x556B30
    void FUN_00556B30();
};

struct Obj_005F6CB0
{
    char unknown_00[0x50];
    int unknown_50;   // +0x0050
    char unknown_54[0x10];
    int unknown_64;   // +0x0064
};
GG_STATIC_ASSERT(offsetof(Obj_005F6CB0, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(Obj_005F6CB0, unknown_64) == 0x64);


// FUNCTION: GAMEMD 0x5F5C10
void __cdecl FUN_005F5C10();
// FUNCTION: GAMEMD 0x5F6CB0
void FUN_005F6CB0(Obj_005F6CB0* a1, int a2, int a3);

#endif  // GG_MATCH_CORE_TRIVIAL_TU165_METHODS_H
