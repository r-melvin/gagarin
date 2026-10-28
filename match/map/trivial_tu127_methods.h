// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_MAP_TRIVIAL_TU127_METHODS_H
#define GG_MATCH_MAP_TRIVIAL_TU127_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00561900;
struct Obj_005638C0;

// GLOBAL: GAMEMD 0xABDC50
extern char DAT_00ABDC50[];

// FUNCTION: GAMEMD 0x47BB60 (declaration)
void FUN_0047BB60(void*, int);

struct Obj_00561900
{
    // FUNCTION: GAMEMD 0x561900
    void FUN_00561900();
    // FUNCTION: GAMEMD 0x561910
    void FUN_00561910();
};

struct Obj_005638C0
{
    // FUNCTION: GAMEMD 0x5638C0
    void FUN_005638C0();
    // FUNCTION: GAMEMD 0x5638D0
    void FUN_005638D0();
};


// FUNCTION: GAMEMD 0x56C200
int __cdecl FUN_0056C200();
// FUNCTION: GAMEMD 0x56C500
void __cdecl FUN_0056C500();

#endif  // GG_MATCH_MAP_TRIVIAL_TU127_METHODS_H
