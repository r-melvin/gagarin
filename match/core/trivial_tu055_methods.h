// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU055_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU055_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0048D1D0;

// FUNCTION: GAMEMD 0x48D080 (declaration)
void FUN_0048D080(Obj_0048D1D0*, int);

struct Obj_0048D1D0
{
};


// FUNCTION: GAMEMD 0x48C8A0
void __cdecl FUN_0048C8A0();
// FUNCTION: GAMEMD 0x48D1D0
bool FUN_0048D1D0(Obj_0048D1D0* a1, int a2);
// FUNCTION: GAMEMD 0x48DB70
void __cdecl FUN_0048DB70();

#endif  // GG_MATCH_CORE_TRIVIAL_TU055_METHODS_H
