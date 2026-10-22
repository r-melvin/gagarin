// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_NETWORK_TRIVIAL_TU164_METHODS_H
#define GG_MATCH_NETWORK_TRIVIAL_TU164_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005F3520;
struct Obj_005F3530;

struct Obj_005F3520
{
    // FUNCTION: GAMEMD 0x5F3520
    int FUN_005F3520(int a1) const;
};

struct Obj_005F3530
{
    // FUNCTION: GAMEMD 0x5F3530
    int FUN_005F3530(int a1) const;
};


// FUNCTION: GAMEMD 0x5F3440
int __stdcall FUN_005F3440(int a1);

#endif  // GG_MATCH_NETWORK_TRIVIAL_TU164_METHODS_H
