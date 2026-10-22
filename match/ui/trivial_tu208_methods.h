// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_UI_TRIVIAL_TU208_METHODS_H
#define GG_MATCH_UI_TRIVIAL_TU208_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0069E060;

struct Obj_0069E060
{
    char unknown_00[0x34];
    unsigned char unknown_34;   // +0x0034
    // FUNCTION: GAMEMD 0x69E060
    unsigned char FUN_0069E060() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0069E060, unknown_34) == 0x34);



#endif  // GG_MATCH_UI_TRIVIAL_TU208_METHODS_H
