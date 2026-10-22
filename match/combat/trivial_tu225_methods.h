// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_COMBAT_TRIVIAL_TU225_METHODS_H
#define GG_MATCH_COMBAT_TRIVIAL_TU225_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006CC2A0;
struct Obj_006CC2A0_28;
struct Obj_006CE200;
struct Obj_006CE210;

struct Obj_006CC2A0
{
    char unknown_00[0x28];
    Obj_006CC2A0_28* unknown_28;   // +0x0028
    // FUNCTION: GAMEMD 0x6CC2A0
    unsigned char FUN_006CC2A0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_006CC2A0, unknown_28) == 0x28);

struct Obj_006CC2A0_28
{
    char unknown_00[0xE6];
    unsigned char unknown_E6;   // +0x00E6
};
GG_STATIC_ASSERT(offsetof(Obj_006CC2A0_28, unknown_E6) == 0xE6);

struct Obj_006CE200
{
    // FUNCTION: GAMEMD 0x6CE200
    int FUN_006CE200() const;
};

struct Obj_006CE210
{
    // FUNCTION: GAMEMD 0x6CE210
    int FUN_006CE210() const;
};


// FUNCTION: GAMEMD 0x6CDE80
void __stdcall FUN_006CDE80(int a1, int a2);

#endif  // GG_MATCH_COMBAT_TRIVIAL_TU225_METHODS_H
