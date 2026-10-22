// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU046_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU046_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00473CD0;

struct Obj_00473CD0
{
    char unknown_00[0x58];
    int unknown_58;   // +0x0058
    // FUNCTION: GAMEMD 0x431F30
    bool FUN_00431F30();
    // FUNCTION: GAMEMD 0x473CD0
    unsigned char FUN_00473CD0();
};
GG_STATIC_ASSERT(offsetof(Obj_00473CD0, unknown_58) == 0x58);



#endif  // GG_MATCH_CORE_TRIVIAL_TU046_METHODS_H
