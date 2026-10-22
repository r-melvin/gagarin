// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU102_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU102_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0052F610;

// GLOBAL: GAMEMD 0x8263A8
extern char DAT_008263A8[];
// GLOBAL: GAMEMD 0xA83D10
extern char DAT_00A83D10[];

// FUNCTION: GAMEMD 0x721210 (declaration)
void FUN_00721210(void*, int, void*);
// FUNCTION: GAMEMD 0x75A7D0 (declaration)
void FUN_0075A7D0(int);

struct Obj_0052F610
{
    // FUNCTION: GAMEMD 0x52F610
    void FUN_0052F610();
    // FUNCTION: GAMEMD 0x75A790
    void FUN_0075A790();
};


// FUNCTION: GAMEMD 0x52D610
void __cdecl FUN_0052D610();
// FUNCTION: GAMEMD 0x52D620
void __cdecl FUN_0052D620();
// FUNCTION: GAMEMD 0x52D630
void __cdecl FUN_0052D630();
// FUNCTION: GAMEMD 0x532140
void __cdecl FUN_00532140();
// FUNCTION: GAMEMD 0x5355C0
void FUN_005355C0(int a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU102_METHODS_H
