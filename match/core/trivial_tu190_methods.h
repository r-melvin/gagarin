// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU190_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU190_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0065B3A0;
struct Obj_0065B3C0;
struct Obj_0065B4B0;

struct Obj_0065B3A0
{
    // FUNCTION: GAMEMD 0x65B3A0
    int FUN_0065B3A0() const;
};

struct Obj_0065B3C0
{
    // FUNCTION: GAMEMD 0x65B3C0
    int FUN_0065B3C0() const;
};

struct Obj_0065B4B0
{
    char unknown_00[0x44];
    int unknown_44;   // +0x0044
    // FUNCTION: GAMEMD 0x65B4B0
    int FUN_0065B4B0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0065B4B0, unknown_44) == 0x44);



#endif  // GG_MATCH_CORE_TRIVIAL_TU190_METHODS_H
