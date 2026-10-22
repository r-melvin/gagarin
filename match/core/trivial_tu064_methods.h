// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU064_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU064_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004A3630;
struct Obj_004A3640;
struct Obj_004A3C00;

struct Obj_004A3630
{
    char unknown_00[0x18000];
    int unknown_18000;   // +0x18000
    // FUNCTION: GAMEMD 0x4A3630
    Obj_004A3630* FUN_004A3630();
};
GG_STATIC_ASSERT(offsetof(Obj_004A3630, unknown_18000) == 0x18000);

struct Obj_004A3640
{
    char unknown_00[0x18000];
    int unknown_18000;   // +0x18000
    // FUNCTION: GAMEMD 0x4A3640
    void FUN_004A3640();
};
GG_STATIC_ASSERT(offsetof(Obj_004A3640, unknown_18000) == 0x18000);

struct Obj_004A3C00
{
    unsigned char unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x4A3C00
    void FUN_004A3C00();
};
GG_STATIC_ASSERT(offsetof(Obj_004A3C00, unknown_00) == 0x0);


// FUNCTION: GAMEMD 0x4A3650
void __cdecl FUN_004A3650();
// FUNCTION: GAMEMD 0x4A3B30
int __cdecl FUN_004A3B30();

#endif  // GG_MATCH_CORE_TRIVIAL_TU064_METHODS_H
