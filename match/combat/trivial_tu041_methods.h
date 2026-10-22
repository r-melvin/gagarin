// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_COMBAT_TRIVIAL_TU041_METHODS_H
#define GG_MATCH_COMBAT_TRIVIAL_TU041_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0046C820;
struct Obj_0046C850;
struct Obj_0046C860;
struct Obj_0046C870;
struct Obj_0046C880;

struct Obj_0046C820
{
    char unknown_00[0x2D8];
    int unknown_2D8;   // +0x02D8
    // FUNCTION: GAMEMD 0x46C820
    int FUN_0046C820(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_0046C820, unknown_2D8) == 0x2D8);

struct Obj_0046C850
{
    // FUNCTION: GAMEMD 0x46C850
    int FUN_0046C850() const;
};

struct Obj_0046C860
{
    // FUNCTION: GAMEMD 0x46C860
    int FUN_0046C860() const;
};

struct Obj_0046C870
{
    // FUNCTION: GAMEMD 0x46C870
    bool FUN_0046C870(int a1, int a2) const;
};

struct Obj_0046C880
{
    // FUNCTION: GAMEMD 0x46C880
    int FUN_0046C880(int a1) const;
};



#endif  // GG_MATCH_COMBAT_TRIVIAL_TU041_METHODS_H
