// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU093_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU093_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004F3AD0;
struct Obj_004F3AE0;
struct Obj_004F3FF0;
struct Obj_004F4000;

struct Obj_004F3AD0
{
    // FUNCTION: GAMEMD 0x4F3AD0
    void FUN_004F3AD0(int a1);
};

struct Obj_004F3AE0
{
    // FUNCTION: GAMEMD 0x4F3AE0
    void FUN_004F3AE0(int a1);
};

struct Obj_004F3FF0
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x4F3FF0
    Obj_004F3FF0* FUN_004F3FF0();
};
GG_STATIC_ASSERT(offsetof(Obj_004F3FF0, unknown_08) == 0x8);

struct Obj_004F4000
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x4F4000
    Obj_004F4000* FUN_004F4000();
};
GG_STATIC_ASSERT(offsetof(Obj_004F4000, unknown_08) == 0x8);



#endif  // GG_MATCH_CORE_TRIVIAL_TU093_METHODS_H
