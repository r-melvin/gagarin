// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_PLATFORM_TRIVIAL_TU047_METHODS_H
#define GG_MATCH_PLATFORM_TRIVIAL_TU047_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00476EA0;

struct Obj_00476EA0
{
    char unknown_00[0x40];
    unsigned char unknown_40;   // +0x0040
    // FUNCTION: GAMEMD 0x476EA0
    void FUN_00476EA0();
};
GG_STATIC_ASSERT(offsetof(Obj_00476EA0, unknown_40) == 0x40);



#endif  // GG_MATCH_PLATFORM_TRIVIAL_TU047_METHODS_H
