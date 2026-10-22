// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU151_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU151_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005CB3E0;
struct Obj_005CB3F0;
struct Obj_005CB430;

// GLOBAL: GAMEMD 0xA8B258
extern bool DAT_00A8B258;

// FUNCTION: GAMEMD 0x5D5D20 (declaration)
void FUN_005D5D20(Obj_005CB3E0*, int);

struct Obj_005CB3E0
{
    int unknown_00;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Obj_005CB3E0, unknown_00) == 0x0);

struct Obj_005CB3F0
{
    // FUNCTION: GAMEMD 0x5CB3F0
    bool FUN_005CB3F0();
};

struct Obj_005CB430
{
    // FUNCTION: GAMEMD 0x5CB430
    bool FUN_005CB430();
};


// FUNCTION: GAMEMD 0x5CB3E0
void FUN_005CB3E0(Obj_005CB3E0* a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU151_METHODS_H
