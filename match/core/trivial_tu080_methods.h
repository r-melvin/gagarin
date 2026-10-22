// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU080_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU080_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_004CA580;
struct Obj_004CA750;
struct Obj_004CA760;

struct Obj_004CA580
{
    char unknown_00[0x58];
    int unknown_58;   // +0x0058
    // FUNCTION: GAMEMD 0x4CA580
    int FUN_004CA580(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_004CA580, unknown_58) == 0x58);

struct Obj_004CA750
{
    // FUNCTION: GAMEMD 0x4CA750
    int FUN_004CA750() const;
};

struct Obj_004CA760
{
    // FUNCTION: GAMEMD 0x4CA760
    int FUN_004CA760() const;
};


// FUNCTION: GAMEMD 0x4CAEF0
void __cdecl FUN_004CAEF0();
// FUNCTION: GAMEMD 0x4CAF00
void __cdecl FUN_004CAF00();
// FUNCTION: GAMEMD 0x4CAF10
void __cdecl FUN_004CAF10();

#endif  // GG_MATCH_CORE_TRIVIAL_TU080_METHODS_H
