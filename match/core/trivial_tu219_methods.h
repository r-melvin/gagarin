// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU219_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU219_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006B8AE0;

struct Obj_006B8AE0
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x6B8AE0
    void FUN_006B8AE0();
};
GG_STATIC_ASSERT(offsetof(Obj_006B8AE0, unknown_00) == 0x0);


// FUNCTION: GAMEMD 0x6BA220
void __cdecl FUN_006BA220();
// FUNCTION: GAMEMD 0x6BA680
bool __stdcall FUN_006BA680(int a1, int a2, int a3);

#endif  // GG_MATCH_CORE_TRIVIAL_TU219_METHODS_H
