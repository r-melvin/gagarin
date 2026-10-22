// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_PLATFORM_TRIVIAL_TU030_METHODS_H
#define GG_MATCH_PLATFORM_TRIVIAL_TU030_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00431F30;

struct Obj_00431F30
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
    char unknown_18[0xD];
    unsigned char unknown_25;   // +0x0025
    char unknown_26[0x3];
    unsigned char unknown_29;   // +0x0029
    // FUNCTION: GAMEMD 0x431F30
    unsigned char FUN_00431F30();
};
GG_STATIC_ASSERT(offsetof(Obj_00431F30, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_00431F30, unknown_25) == 0x25);
GG_STATIC_ASSERT(offsetof(Obj_00431F30, unknown_29) == 0x29);



#endif  // GG_MATCH_PLATFORM_TRIVIAL_TU030_METHODS_H
