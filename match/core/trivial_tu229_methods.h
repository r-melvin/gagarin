// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU229_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU229_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_006D6170;
struct Obj_006D6170;
struct Obj_006DC450;
struct Obj_006DC460;

struct Arg1_006D6170
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006D6170, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Arg1_006D6170, unknown_04) == 0x4);

struct Obj_006D6170
{
    char unknown_00[0xD64];
    int unknown_D64;   // +0x0D64
    int unknown_D68;   // +0x0D68
    // FUNCTION: GAMEMD 0x6D6170
    Arg1_006D6170* FUN_006D6170(Arg1_006D6170* a1);
};
GG_STATIC_ASSERT(offsetof(Obj_006D6170, unknown_D64) == 0xD64);
GG_STATIC_ASSERT(offsetof(Obj_006D6170, unknown_D68) == 0xD68);

struct Obj_006DC450
{
    // FUNCTION: GAMEMD 0x6DC450
    int FUN_006DC450() const;
};

struct Obj_006DC460
{
    // FUNCTION: GAMEMD 0x6DC460
    int FUN_006DC460() const;
};


// FUNCTION: GAMEMD 0x6D1B00
void __cdecl FUN_006D1B00();
// FUNCTION: GAMEMD 0x6D2B50
void __stdcall FUN_006D2B50(int a1, int a2);
// FUNCTION: GAMEMD 0x6D8630
void __cdecl FUN_006D8630();
// FUNCTION: GAMEMD 0x6DA350
void __cdecl FUN_006DA350();
// FUNCTION: GAMEMD 0x6DA370
void __stdcall FUN_006DA370(int a1);

#endif  // GG_MATCH_CORE_TRIVIAL_TU229_METHODS_H
