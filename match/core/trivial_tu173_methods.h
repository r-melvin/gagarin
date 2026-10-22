// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU173_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU173_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00629710;
struct Obj_0062AF50;
struct Obj_0062AF60;

struct Obj_00629710
{
    char unknown_00[0x4C];
    int unknown_4C;   // +0x004C
    int unknown_50;   // +0x0050
    // FUNCTION: GAMEMD 0x629710
    void FUN_00629710();
};
GG_STATIC_ASSERT(offsetof(Obj_00629710, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_00629710, unknown_50) == 0x50);

struct Obj_0062AF50
{
    // FUNCTION: GAMEMD 0x62AF50
    int FUN_0062AF50() const;
};

struct Obj_0062AF60
{
    // FUNCTION: GAMEMD 0x62AF60
    int FUN_0062AF60() const;
};



#endif  // GG_MATCH_CORE_TRIVIAL_TU173_METHODS_H
