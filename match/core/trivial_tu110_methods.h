// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU110_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU110_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0054A140;
struct Obj_0054A150;
struct Obj_0054A160;

struct Obj_0054A140
{
    // FUNCTION: GAMEMD 0x54A140
    int FUN_0054A140() const;
};

struct Obj_0054A150
{
    // FUNCTION: GAMEMD 0x54A150
    int FUN_0054A150() const;
};

struct Obj_0054A160
{
    char unknown_00[0x294];
    int unknown_294;   // +0x0294
    // FUNCTION: GAMEMD 0x54A160
    int FUN_0054A160() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0054A160, unknown_294) == 0x294);


// FUNCTION: GAMEMD 0x544DF0
void __cdecl FUN_00544DF0();
// FUNCTION: GAMEMD 0x544FF0
bool __cdecl FUN_00544FF0();
// FUNCTION: GAMEMD 0x547CE0
void __cdecl FUN_00547CE0();

#endif  // GG_MATCH_CORE_TRIVIAL_TU110_METHODS_H
