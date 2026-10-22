// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU209_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU209_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_006A4250;
struct Arg1_006A4280;
struct Obj_006A3EA0;
struct Obj_006A4250;
struct Obj_006A4280;
struct Obj_006A42A0;

struct Arg1_006A4250
{
    char unknown_00[0x48];
    int unknown_48;   // +0x0048
};
GG_STATIC_ASSERT(offsetof(Arg1_006A4250, unknown_48) == 0x48);

struct Arg1_006A4280
{
    char unknown_00[0x50];
    int unknown_50;   // +0x0050
};
GG_STATIC_ASSERT(offsetof(Arg1_006A4280, unknown_50) == 0x50);

struct Obj_006A3EA0
{
    // FUNCTION: GAMEMD 0x6A3EA0
    int FUN_006A3EA0(int a1) const;
};

struct Obj_006A4250
{
    // FUNCTION: GAMEMD 0x6A4250
    int FUN_006A4250(Arg1_006A4250* a1) const;
};

struct Obj_006A4280
{
    // FUNCTION: GAMEMD 0x6A4280
    bool FUN_006A4280(Arg1_006A4280* a1) const;
};

struct Obj_006A42A0
{
    // FUNCTION: GAMEMD 0x6A42A0
    int FUN_006A42A0() const;
};


// FUNCTION: GAMEMD 0x6A3DA0
void __cdecl FUN_006A3DA0();

#endif  // GG_MATCH_CORE_TRIVIAL_TU209_METHODS_H
