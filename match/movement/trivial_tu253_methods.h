// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_MOVEMENT_TRIVIAL_TU253_METHODS_H
#define GG_MATCH_MOVEMENT_TRIVIAL_TU253_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_00728A50;
struct Arg1_007291D0;
struct Arg1_0072A1E0;
struct Obj_00728A50;
struct Obj_007291D0;
struct Obj_0072A1E0;
struct Obj_0072A200;

struct Arg1_00728A50
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
};
GG_STATIC_ASSERT(offsetof(Arg1_00728A50, unknown_14) == 0x14);

struct Arg1_007291D0
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
};
GG_STATIC_ASSERT(offsetof(Arg1_007291D0, unknown_14) == 0x14);

struct Arg1_0072A1E0
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
};
GG_STATIC_ASSERT(offsetof(Arg1_0072A1E0, unknown_14) == 0x14);

struct Obj_00728A50
{
    // FUNCTION: GAMEMD 0x728A50
    bool FUN_00728A50(Arg1_00728A50* a1) const;
};

struct Obj_007291D0
{
    // FUNCTION: GAMEMD 0x7291D0
    int FUN_007291D0(Arg1_007291D0* a1, unsigned char a2);
};

struct Obj_0072A1E0
{
    // FUNCTION: GAMEMD 0x72A1E0
    int FUN_0072A1E0(Arg1_0072A1E0* a1);
};

struct Obj_0072A200
{
    // FUNCTION: GAMEMD 0x72A200
    int FUN_0072A200() const;
};



#endif  // GG_MATCH_MOVEMENT_TRIVIAL_TU253_METHODS_H
