// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_UI_TRIVIAL_TU065_METHODS_H
#define GG_MATCH_UI_TRIVIAL_TU065_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004A5950;

struct Obj_004A5950
{
    char unknown_00[0xB4];
    int unknown_B4;   // +0x00B4
    // FUNCTION: GAMEMD 0x4A5950
    int FUN_004A5950() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004A5950, unknown_B4) == 0xB4);


// FUNCTION: GAMEMD 0x4A5090
void __cdecl FUN_004A5090();

#endif  // GG_MATCH_UI_TRIVIAL_TU065_METHODS_H
