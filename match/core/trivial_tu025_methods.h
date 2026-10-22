// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU025_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU025_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00428C10;
struct Obj_00428E50;
struct Obj_00428E60;
struct Obj_00428E70;
struct Obj_00428E80;
struct Obj_00428E90;

struct Obj_00428C10
{
    char unknown_00[0x2C8];
    int unknown_2C8;   // +0x02C8
    // FUNCTION: GAMEMD 0x428C10
    int FUN_00428C10(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_00428C10, unknown_2C8) == 0x2C8);

struct Obj_00428E50
{
    // FUNCTION: GAMEMD 0x428E50
    int FUN_00428E50() const;
};

struct Obj_00428E60
{
    char unknown_00[0x294];
    int unknown_294;   // +0x0294
    // FUNCTION: GAMEMD 0x428E60
    int FUN_00428E60() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00428E60, unknown_294) == 0x294);

struct Obj_00428E70
{
    // FUNCTION: GAMEMD 0x428E70
    int FUN_00428E70() const;
};

struct Obj_00428E80
{
    // FUNCTION: GAMEMD 0x428E80
    bool FUN_00428E80(int a1, int a2) const;
};

struct Obj_00428E90
{
    // FUNCTION: GAMEMD 0x428E90
    int FUN_00428E90(int a1) const;
};



#endif  // GG_MATCH_CORE_TRIVIAL_TU025_METHODS_H
