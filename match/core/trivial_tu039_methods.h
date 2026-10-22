// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU039_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU039_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0045B1B0;
struct Obj_0045C2F0;
struct Obj_00465D80;

struct Obj_0045B1B0
{
    // FUNCTION: GAMEMD 0x45B1B0
    void FUN_0045B1B0();
    // FUNCTION: GAMEMD 0x45B1C0
    void FUN_0045B1C0();
};

struct Obj_0045C2F0
{
    // FUNCTION: GAMEMD 0x45C2F0
    void FUN_0045C2F0();
    // FUNCTION: GAMEMD 0x45C300
    void FUN_0045C300();
};

struct Obj_00465D80
{
    // FUNCTION: GAMEMD 0x465D80
    Obj_00465D80* FUN_00465D80();
};


// FUNCTION: GAMEMD 0x45EC80
void __cdecl FUN_0045EC80();

#endif  // GG_MATCH_CORE_TRIVIAL_TU039_METHODS_H
