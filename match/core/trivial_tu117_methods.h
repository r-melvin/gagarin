// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU117_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU117_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_00554350;
struct Obj_00554350;

struct Arg1_00554350
{
    virtual void vf_0();
    virtual void vf_1(int, int, int);
};

struct Obj_00554350
{
    char unknown_00[0x60];
    int unknown_60;   // +0x0060
    // FUNCTION: GAMEMD 0x554350
    void FUN_00554350(Arg1_00554350* a1);
};
GG_STATIC_ASSERT(offsetof(Obj_00554350, unknown_60) == 0x60);



#endif  // GG_MATCH_CORE_TRIVIAL_TU117_METHODS_H
