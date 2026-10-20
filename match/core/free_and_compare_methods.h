// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets and callees read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x4084C0 / 0x4085A0 / 0x410A40. None is
//   bound by YRpp or the seed map.
//
// A teardown, a zeroing initialiser and a name comparison.
#ifndef GG_MATCH_CORE_FREE_AND_COMPARE_METHODS_H
#define GG_MATCH_CORE_FREE_AND_COMPARE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The deallocator, __cdecl with one pointer argument. Same one the other
// teardowns in this tree use.
extern "C" void __cdecl FUN_007C8B3D(void* block);

// __cdecl, two pointer arguments, `ADD ESP,8` after — and its result feeds
// `NEG/SBB/INC`, the materialisation of `== 0`. That is strcmp.
extern "C" int __cdecl FUN_007C8D20(const char* a, const char* b);

struct Obj_00408400
{
    void* unknown_00;   // +0x0000  owned buffer, freed if set

    // FUNCTION: GAMEMD 0x4084C0
    void FUN_004084C0();
};

// Thirty-two bytes cleared with `REP STOSD` of eight dwords.
struct Obj_00408500
{
    int unknown[8];   // +0x0000 .. +0x001C

    // FUNCTION: GAMEMD 0x4085A0
    void FUN_004085A0();
};
GG_STATIC_ASSERT(sizeof(Obj_00408500) == 32);

struct Obj_00410A00
{
    char _pad00[0x24];
    char Name[1];      // +0x0024  inline string; only its address is taken

    // FUNCTION: GAMEMD 0x410A40
    bool FUN_00410A40(const char* other) const;
};
GG_STATIC_ASSERT(offsetof(Obj_00410A00, Name) == 0x24);

#endif  // GG_MATCH_CORE_FREE_AND_COMPARE_METHODS_H
