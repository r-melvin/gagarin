// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU260_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU260_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0074A960;
struct Obj_0074AB10;
struct Obj_0074AB20;
struct Obj_0074AB30;
struct Obj_0074AB40;

struct Obj_0074A960
{
    // FUNCTION: GAMEMD 0x74A960
    int FUN_0074A960() const;
};

struct Obj_0074AB10
{
    // FUNCTION: GAMEMD 0x74AB10
    int FUN_0074AB10() const;
};

struct Obj_0074AB20
{
    // FUNCTION: GAMEMD 0x74AB20
    int FUN_0074AB20() const;
};

struct Obj_0074AB30
{
    char unknown_00[0x104];
    int unknown_104;   // +0x0104
    // FUNCTION: GAMEMD 0x74AB30
    int FUN_0074AB30() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0074AB30, unknown_104) == 0x104);

struct Obj_0074AB40
{
    // FUNCTION: GAMEMD 0x74AB40
    int FUN_0074AB40(int a1) const;
};



#endif  // GG_MATCH_CORE_TRIVIAL_TU260_METHODS_H
