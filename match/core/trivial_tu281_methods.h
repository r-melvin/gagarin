// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU281_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU281_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00771890;

struct Obj_00771890
{
    int unknown_00;   // +0x0000
    // FUNCTION: GAMEMD 0x5CB6C0
    void FUN_005CB6C0();
    // FUNCTION: GAMEMD 0x771890
    void FUN_00771890();
};
GG_STATIC_ASSERT(offsetof(Obj_00771890, unknown_00) == 0x0);


// FUNCTION: GAMEMD 0x771780
void __cdecl FUN_00771780();
// FUNCTION: GAMEMD 0x771790
void __cdecl FUN_00771790();

#endif  // GG_MATCH_CORE_TRIVIAL_TU281_METHODS_H
