// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU073_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU073_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004C1E50;
struct Obj_004C1E50_20;
struct Obj_004C2C30;

struct Obj_004C1E50
{
    char unknown_00[0x20];
    Obj_004C1E50_20* unknown_20;   // +0x0020
    // FUNCTION: GAMEMD 0x4C1E50
    void FUN_004C1E50();
};
GG_STATIC_ASSERT(offsetof(Obj_004C1E50, unknown_20) == 0x20);

struct Obj_004C1E50_20
{
    char unknown_00[0x6DC];
    int unknown_6DC;   // +0x06DC
};
GG_STATIC_ASSERT(offsetof(Obj_004C1E50_20, unknown_6DC) == 0x6DC);

struct Obj_004C2C30
{
    // FUNCTION: GAMEMD 0x4C2C30
    Obj_004C2C30* FUN_004C2C30();
};



#endif  // GG_MATCH_CORE_TRIVIAL_TU073_METHODS_H
