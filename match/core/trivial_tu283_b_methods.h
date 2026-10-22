// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU283_B_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU283_B_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Gptr_00B72D0C;

// GLOBAL: GAMEMD 0xB72D0C
extern Gptr_00B72D0C* DAT_00B72D0C;

struct Gptr_00B72D0C
{
    char unknown_00[0x8];
    int unknown_08;   // +0x0008
    char unknown_0C[0x400];
    bool unknown_40C;   // +0x040C
};
GG_STATIC_ASSERT(offsetof(Gptr_00B72D0C, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Gptr_00B72D0C, unknown_40C) == 0x40C);


// FUNCTION: GAMEMD 0x774070
int __cdecl FUN_00774070();

#endif  // GG_MATCH_CORE_TRIVIAL_TU283_B_METHODS_H
