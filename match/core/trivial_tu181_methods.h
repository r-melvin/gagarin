// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU181_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU181_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0063F7C0;

// GLOBAL: GAMEMD 0x836D9C
extern char DAT_00836D9C[];
// GLOBAL: GAMEMD 0xAC4E74
extern int DAT_00AC4E74;
// GLOBAL: GAMEMD 0xAC4E78
extern char DAT_00AC4E78[];

// FUNCTION: GAMEMD 0x4A38D0 (declaration)
int FUN_004A38D0(void*, void*);
// FUNCTION: GAMEMD 0x652E90 (declaration)
void FUN_00652E90(Obj_0063F7C0*, int);

struct Obj_0063F7C0
{
};


// FUNCTION: GAMEMD 0x63F7C0
int FUN_0063F7C0(Obj_0063F7C0* a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU181_METHODS_H
