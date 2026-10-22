// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_COMBAT_TRIVIAL_TU226_METHODS_H
#define GG_MATCH_COMBAT_TRIVIAL_TU226_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006CE8F0;
struct Obj_006CE900;
struct Obj_006CEA10;

struct Obj_006CE8F0
{
    // FUNCTION: GAMEMD 0x6CE8F0
    int FUN_006CE8F0() const;
};

struct Obj_006CE900
{
    // FUNCTION: GAMEMD 0x6CE900
    int FUN_006CE900() const;
};

struct Obj_006CEA10
{
    char unknown_00[0x98];
    int unknown_98;   // +0x0098
    // FUNCTION: GAMEMD 0x6CEA10
    int FUN_006CEA10() const;
};
GG_STATIC_ASSERT(offsetof(Obj_006CEA10, unknown_98) == 0x98);



#endif  // GG_MATCH_COMBAT_TRIVIAL_TU226_METHODS_H
