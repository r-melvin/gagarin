// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU171_D_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU171_D_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0060AF40;

// Import EnumChildWindows from USER32.dll (IAT slot 0x7E14E4)
extern "C" __declspec(dllimport) void __stdcall EnumChildWindows(Obj_0060AF40*, int, int);

struct Obj_0060AF40
{
    // FUNCTION: GAMEMD 0x60AF40
    void FUN_0060AF40();
};



#endif  // GG_MATCH_CORE_TRIVIAL_TU171_D_METHODS_H
