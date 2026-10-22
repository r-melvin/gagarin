// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp or the
//   seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC19_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC19_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

struct Obj_00433C00
{
    char  _pad00[0x18];
    void* unknown_18;   // +0x0018
    void* unknown_1C;   // +0x001C

    // FUNCTION: GAMEMD 0x433C00
    void FUN_00433C00();
};
GG_STATIC_ASSERT(offsetof(Obj_00433C00, unknown_1C) == 0x1C);

// A pair of doubles. Zeroed means "unset", and the reset value is 100.0 written
// as two dword stores.
struct Pair2d
{
    double x;   // +0x0000
    double y;   // +0x0008

    // FUNCTION: GAMEMD 0x41C460
    void FUN_0041C460();
};
GG_STATIC_ASSERT(offsetof(Pair2d, y) == 0x8);

struct Triple3i
{
    int a, b, c;

    // FUNCTION: GAMEMD 0x459F60
    int FUN_00459F60(const Triple3i* other) const;
};

#endif  // GG_MATCH_CORE_SMALL_MISC19_METHODS_H
