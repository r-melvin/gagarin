// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_MOVEMENT_TRIVIAL_TU131_METHODS_H
#define GG_MATCH_MOVEMENT_TRIVIAL_TU131_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005AE590;

struct Obj_005AE590
{
    // FUNCTION: GAMEMD 0x5AE590 (decl)
    void FUN_005AE590(int a1);
};


// FUNCTION: GAMEMD 0x5AE4F0
int __stdcall FUN_005AE4F0(int a1);
// FUNCTION: GAMEMD 0x5AE570
void __stdcall FUN_005AE570(int a1);
// FUNCTION: GAMEMD 0x5AE580
void __stdcall FUN_005AE580(int a1);

#endif  // GG_MATCH_MOVEMENT_TRIVIAL_TU131_METHODS_H
