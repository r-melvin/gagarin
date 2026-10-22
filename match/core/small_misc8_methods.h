// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp or the
//   seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC8_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC8_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

void __fastcall FUN_004091C0(void* self, int arg);   // GAMEMD 0x4091C0

struct Obj_004092F0
{
    char _pad00[0x8];
    int  unknown_08;   // +0x0008

    // FUNCTION: GAMEMD 0x4092F0
    int FUN_004092F0();
};
GG_STATIC_ASSERT(offsetof(Obj_004092F0, unknown_08) == 0x8);

// __fastcall: the second argument arrives in DL, zeroed at both call sites.
struct Obj_005B40B0;
Obj_005B40B0* __fastcall FUN_005B40B0(void* self, unsigned char flag);   // GAMEMD 0x5B40B0
// GLOBAL: GAMEMD 0x817FE4 / 0x817FD8 — the two receivers.
extern char DAT_00817FE4[];
extern char DAT_00817FD8[];
// GLOBAL: GAMEMD 0x889F5C / 0x889F60 — where the results land.
extern Obj_005B40B0* DAT_00889F5C;
extern Obj_005B40B0* DAT_00889F60;

// FUNCTION: GAMEMD 0x41CAF0
void __cdecl FUN_0041CAF0();

// Zero-argument virtual at +0x2C returning an int type tag.
struct Obj_00459F40;
typedef int (__fastcall* WhatAmIFn)(Obj_00459F40*);
#define WHAT_AM_I(o) ((*(WhatAmIFn*)(*(char**)(o) + 0x2c))(o))

struct Obj_00459F40
{
    // FUNCTION: GAMEMD 0x459F40
    Obj_00459F40* FUN_00459F40();
};

#endif  // GG_MATCH_CORE_SMALL_MISC8_METHODS_H
