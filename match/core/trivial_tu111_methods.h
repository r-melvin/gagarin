// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU111_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU111_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_0054AE50;
struct Arg1_0054D0D0;
struct Arg1_0054DF70;
struct Obj_0054AE50;
struct Obj_0054D0D0;
struct Obj_0054DF70;
struct Obj_0054DF90;

struct Arg1_0054AE50
{
    char unknown_00[0x48];
    unsigned char unknown_48;   // +0x0048
};
GG_STATIC_ASSERT(offsetof(Arg1_0054AE50, unknown_48) == 0x48);

struct Arg1_0054D0D0
{
    char unknown_00[0x4C];
    int unknown_4C;   // +0x004C
};
GG_STATIC_ASSERT(offsetof(Arg1_0054D0D0, unknown_4C) == 0x4C);

struct Arg1_0054DF70
{
    char unknown_00[0x7C];
    int unknown_7C;   // +0x007C
};
GG_STATIC_ASSERT(offsetof(Arg1_0054DF70, unknown_7C) == 0x7C);

struct Obj_0054AE50
{
    // FUNCTION: GAMEMD 0x54AE50
    unsigned char FUN_0054AE50(Arg1_0054AE50* a1) const;
};

struct Obj_0054D0D0
{
    // FUNCTION: GAMEMD 0x54D0D0
    bool FUN_0054D0D0(Arg1_0054D0D0* a1);
};

struct Obj_0054DF70
{
    // FUNCTION: GAMEMD 0x54DF70
    bool FUN_0054DF70(Arg1_0054DF70* a1) const;
};

struct Obj_0054DF90
{
    // FUNCTION: GAMEMD 0x54DF90
    int FUN_0054DF90() const;
};


// FUNCTION: GAMEMD 0x54D0C0
void __cdecl FUN_0054D0C0();

#endif  // GG_MATCH_CORE_TRIVIAL_TU111_METHODS_H
