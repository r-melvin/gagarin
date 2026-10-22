// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_MOVEMENT_TRIVIAL_TU098_METHODS_H
#define GG_MATCH_MOVEMENT_TRIVIAL_TU098_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_00517560;
struct Obj_00517560;

struct Arg1_00517560
{
    bool unknown_00;   // +0x0000
    bool unknown_01;   // +0x0001
    bool unknown_02;   // +0x0002
};
GG_STATIC_ASSERT(offsetof(Arg1_00517560, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Arg1_00517560, unknown_01) == 0x1);
GG_STATIC_ASSERT(offsetof(Arg1_00517560, unknown_02) == 0x2);

struct Obj_00517560
{
    bool unknown_00;   // +0x0000
    bool unknown_01;   // +0x0001
    bool unknown_02;   // +0x0002
    // FUNCTION: GAMEMD 0x517560
    int FUN_00517560(Arg1_00517560* a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00517560, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_00517560, unknown_01) == 0x1);
GG_STATIC_ASSERT(offsetof(Obj_00517560, unknown_02) == 0x2);

#endif  // GG_MATCH_MOVEMENT_TRIVIAL_TU098_METHODS_H
