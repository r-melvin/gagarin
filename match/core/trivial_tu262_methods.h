// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU262_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU262_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0074F310;
struct Obj_0074F320;
struct Obj_00750080;

struct Obj_0074F310
{
    // FUNCTION: GAMEMD 0x74F310
    int FUN_0074F310() const;
};

struct Obj_0074F320
{
    // FUNCTION: GAMEMD 0x74F320
    int FUN_0074F320() const;
};

struct Obj_00750080
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x750080
    void FUN_00750080(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00750080, unknown_00) == 0x0);



#endif  // GG_MATCH_CORE_TRIVIAL_TU262_METHODS_H
