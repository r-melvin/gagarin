// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_NETWORK_TRIVIAL_TU029_METHODS_H
#define GG_MATCH_NETWORK_TRIVIAL_TU029_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00430610;

struct Obj_00430610
{
    char unknown_00[0xC];
    unsigned char unknown_0C;   // +0x000C
    // FUNCTION: GAMEMD 0x430610
    void FUN_00430610();
};
GG_STATIC_ASSERT(offsetof(Obj_00430610, unknown_0C) == 0xC);


// FUNCTION: GAMEMD 0x430580
void __stdcall FUN_00430580(int a1, int a2, int a3, int a4, int a5, int a6, int a7);
// FUNCTION: GAMEMD 0x430600
void __cdecl FUN_00430600();

#endif  // GG_MATCH_NETWORK_TRIVIAL_TU029_METHODS_H
