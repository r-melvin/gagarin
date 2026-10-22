// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU171_C_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU171_C_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0060A5A0;

// Import EnumChildWindows from USER32.dll (IAT slot 0x7E14E4)
extern "C" __declspec(dllimport) void __stdcall EnumChildWindows(Obj_0060A5A0*, int, int);

struct Obj_0060A5A0
{
    // FUNCTION: GAMEMD 0x60A5A0
    void FUN_0060A5A0();
};



#endif  // GG_MATCH_CORE_TRIVIAL_TU171_C_METHODS_H
