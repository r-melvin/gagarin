// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_MAP_TRIVIAL_TU067_METHODS_H
#define GG_MATCH_MAP_TRIVIAL_TU067_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../ui/input_controls/ui_display_chain.h"

struct Obj_004AEB30;
struct Obj_004AEBA0;

struct Obj_004AEB30
{
    char unknown_00[0x119C];
    bool unknown_119C;   // +0x119C
    char unknown_119D[0x3];
    int unknown_11A0;   // +0x11A0
    // FUNCTION: GAMEMD 0x4AEB30
    void FUN_004AEB30(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_004AEB30, unknown_119C) == 0x119C);
GG_STATIC_ASSERT(offsetof(Obj_004AEB30, unknown_11A0) == 0x11A0);

struct Obj_004AEBA0
{
    // FUNCTION: GAMEMD 0x4AEBA0
    int FUN_004AEBA0() const;
};


// FUNCTION: GAMEMD 0x4A8D40
void __cdecl FUN_004A8D40();
// FUNCTION: GAMEMD 0x4A8EA0
void __cdecl FUN_004A8EA0();

#endif  // GG_MATCH_MAP_TRIVIAL_TU067_METHODS_H
