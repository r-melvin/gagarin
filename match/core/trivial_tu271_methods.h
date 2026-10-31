// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU271_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU271_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00764FA0;
struct Obj_00764FA0_C;

struct Obj_00764FA0
{
    char unknown_00[0xC];
    Obj_00764FA0_C* unknown_0C;   // +0x000C
    char unknown_10[0x20];
    int unknown_30;   // +0x0030
    // FUNCTION: GAMEMD 0x764FA0
    unsigned char FUN_00764FA0();
};
GG_STATIC_ASSERT(offsetof(Obj_00764FA0, unknown_0C) == 0xC);
GG_STATIC_ASSERT(offsetof(Obj_00764FA0, unknown_30) == 0x30);

struct Obj_00764FA0_C
{
    // FUNCTION: GAMEMD 0x76BFA0
    int FUN_0076BFA0();
};



#endif  // GG_MATCH_CORE_TRIVIAL_TU271_METHODS_H
