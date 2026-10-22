// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU224_B_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU224_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006C9900;

struct Obj_006C9900
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
    int unknown_0C;   // +0x000C
    int unknown_10;   // +0x0010
    int unknown_14;   // +0x0014
    // FUNCTION: GAMEMD 0x6C9900
    Obj_006C9900* FUN_006C9900();
};
GG_STATIC_ASSERT(offsetof(Obj_006C9900, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_006C9900, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_006C9900, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_006C9900, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_006C9900, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_006C9900, unknown_14) == 0x14);



#endif  // GG_MATCH_CORE_TRIVIAL_TU224_B_METHODS_H
