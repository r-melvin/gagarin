// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU234_B_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU234_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_006E8750;
struct Obj_006E8750;

// FUNCTION: GAMEMD 0x410BE0 (declaration)
void FUN_00410BE0(Obj_006E8750*, int, Arg1_006E8750*);

struct Arg1_006E8750
{
    // FUNCTION: GAMEMD 0x4A1D50
    void FUN_004A1D50(int);
};

struct Obj_006E8750
{
    char unknown_00[0x98];
    int unknown_98;   // +0x0098
    int unknown_9C;   // +0x009C
};
GG_STATIC_ASSERT(offsetof(Obj_006E8750, unknown_98) == 0x98);
GG_STATIC_ASSERT(offsetof(Obj_006E8750, unknown_9C) == 0x9C);

// FUNCTION: GAMEMD 0x6E8750
void FUN_006E8750(Obj_006E8750* a1, int a2, Arg1_006E8750* a3);

#endif  // GG_MATCH_CORE_TRIVIAL_TU234_B_METHODS_H
