// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU244_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU244_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0071FA40;
struct Obj_0071FA50;
struct Obj_0071FA60;
struct Obj_0071FA70;

struct Obj_0071FA40
{
    char unknown_00[0x54];
    int unknown_54;   // +0x0054
    // FUNCTION: GAMEMD 0x71FA40
    void FUN_0071FA40(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_0071FA40, unknown_54) == 0x54);

struct Obj_0071FA50
{
    // FUNCTION: GAMEMD 0x71FA50
    int FUN_0071FA50() const;
};

struct Obj_0071FA60
{
    // FUNCTION: GAMEMD 0x71FA60
    int FUN_0071FA60() const;
};

struct Obj_0071FA70
{
    char unknown_00[0x24];
    int unknown_24;   // +0x0024
    // FUNCTION: GAMEMD 0x71FA70
    int FUN_0071FA70() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0071FA70, unknown_24) == 0x24);



#endif  // GG_MATCH_CORE_TRIVIAL_TU244_METHODS_H
