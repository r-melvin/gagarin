// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU284_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU284_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_007754C0;

// GLOBAL: GAMEMD 0xB72F4C
extern int DAT_00B72F4C;

struct Obj_007754C0
{
    char unknown_00[0x5C];
    int unknown_5C;   // +0x005C
    // FUNCTION: GAMEMD 0x7754C0
    int FUN_007754C0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_007754C0, unknown_5C) == 0x5C);


// FUNCTION: GAMEMD 0x775B30
int __cdecl FUN_00775B30();
// FUNCTION: GAMEMD 0x775B40
int __stdcall FUN_00775B40(int a1, int a2, int a3, int a4);

#endif  // GG_MATCH_CORE_TRIVIAL_TU284_METHODS_H
