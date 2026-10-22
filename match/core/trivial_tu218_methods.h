// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU218_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU218_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006B7C40;
struct Obj_006B8120;
struct Obj_006B8130;

struct Obj_006B7C40
{
    char unknown_00[0x68];
    int unknown_68;   // +0x0068
    int unknown_6C;   // +0x006C
    // FUNCTION: GAMEMD 0x6B7C40
    unsigned char FUN_006B7C40();
};
GG_STATIC_ASSERT(offsetof(Obj_006B7C40, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(Obj_006B7C40, unknown_6C) == 0x6C);

struct Obj_006B8120
{
    // FUNCTION: GAMEMD 0x6B8120
    int FUN_006B8120() const;
};

struct Obj_006B8130
{
    // FUNCTION: GAMEMD 0x6B8130
    int FUN_006B8130() const;
};



#endif  // GG_MATCH_CORE_TRIVIAL_TU218_METHODS_H
