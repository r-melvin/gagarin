// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. Imports read from the IAT
//   thunks at 0x7E11E8 and 0x7E11EC. Not bound by YRpp or the seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC28_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC28_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

// KERNEL32, dllimport so the calls go indirect through the IAT.
struct CRITICAL_SECTION_ { char opaque[24]; };
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION_*);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION_*);

// GLOBAL: GAMEMD 0x87E7F8 — the section guarding the worker below.
extern CRITICAL_SECTION_ DAT_0087E7F8;

struct Worker_00407F40 { void FUN_004025B0(); };   // GAMEMD 0x4025B0

struct Obj_00407F40
{
    char               _pad000[0x14];
    Worker_00407F40*   unknown_14;   // +0x0014
    char               _pad18[0x88 - 0x18];
    int                unknown_88;   // +0x0088

    // FUNCTION: GAMEMD 0x407F40
    void FUN_00407F40();
};
GG_STATIC_ASSERT(offsetof(Obj_00407F40, unknown_88) == 0x88);

// Assignment for the owned-buffer type. Note what it does *not* copy: the
// ownership flag is cleared and never taken from the source, so the target
// borrows the source's buffer rather than owning a copy of it.
struct Owned_0043AE10
{
    void*         Buffer;        // +0x0000
    int           Length;        // +0x0004
    unsigned char IsAllocated;   // +0x0008

    // FUNCTION: GAMEMD 0x43AE10
    Owned_0043AE10* FUN_0043AE10(const Owned_0043AE10* other);
};
GG_STATIC_ASSERT(offsetof(Owned_0043AE10, IsAllocated) == 0x8);

#endif  // GG_MATCH_CORE_SMALL_MISC28_METHODS_H
