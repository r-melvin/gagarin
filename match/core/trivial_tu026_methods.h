// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU026_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU026_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004294A0;

// GLOBAL: GAMEMD 0x89A29C
extern int DAT_0089A29C;

struct Obj_004294A0
{
    // FUNCTION: GAMEMD 0x4294A0
    int FUN_004294A0(int a1) const;
};


// FUNCTION: GAMEMD 0x429200
void __cdecl FUN_00429200();

#endif  // GG_MATCH_CORE_TRIVIAL_TU026_METHODS_H
