// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_AI_TRIVIAL_TU236_METHODS_H
#define GG_MATCH_AI_TRIVIAL_TU236_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006F20A0;
struct Obj_006F20B0;
struct Obj_006F20C0;

struct Obj_006F20A0
{
    // FUNCTION: GAMEMD 0x6F20A0
    int FUN_006F20A0() const;
};

struct Obj_006F20B0
{
    // FUNCTION: GAMEMD 0x6F20B0
    int FUN_006F20B0() const;
};

struct Obj_006F20C0
{
    char unknown_00[0x98];
    int unknown_98;   // +0x0098
    // FUNCTION: GAMEMD 0x6F20C0
    int FUN_006F20C0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_006F20C0, unknown_98) == 0x98);


// FUNCTION: GAMEMD 0x6F25D0
void __cdecl FUN_006F25D0();

#endif  // GG_MATCH_AI_TRIVIAL_TU236_METHODS_H
