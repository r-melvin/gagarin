// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC15_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC15_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void* __cdecl FUN_007C8E17(unsigned int size);   // operator new

// The constructor is __thiscall: retail pushes both arguments and leaves
// only the new object in ECX.
struct Made_0041CB20 { char* FUN_00413D20(void* owner, int arg); };   // GAMEMD 0x413D20

// The allocate-and-construct helper: 0x6D8 bytes.
struct Obj_0041CB20
{
    // FUNCTION: GAMEMD 0x41CB20
    char* FUN_0041CB20(int arg);
};

struct Inner_00459840 { char _pad[0xEA4]; int atEA4; int atEA8; int atEAC; };

struct Obj_00459840
{
    char             _pad000[0x520];
    Inner_00459840*  unknown_520;   // +0x0520
    char             _pad524[0x6F4 - 0x524];
    int              unknown_6F4;   // +0x06F4

    // FUNCTION: GAMEMD 0x459840
    int FUN_00459840() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00459840, unknown_520) == 0x520);
GG_STATIC_ASSERT(offsetof(Obj_00459840, unknown_6F4) == 0x6F4);

#endif  // GG_MATCH_CORE_SMALL_MISC15_METHODS_H
