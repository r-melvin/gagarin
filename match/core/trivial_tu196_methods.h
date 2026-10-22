// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU196_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU196_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_0065FB60;

// GLOBAL: GAMEMD 0x87F7E8
extern char DAT_0087F7E8[];

// FUNCTION: GAMEMD 0x6562D0 (declaration)
void FUN_006562D0(void*, int, Obj_0065FB60*);

struct Obj_0065FB60
{
};


// FUNCTION: GAMEMD 0x65FA60
void __cdecl FUN_0065FA60();
// FUNCTION: GAMEMD 0x65FB60
void FUN_0065FB60(Obj_0065FB60* a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU196_METHODS_H
