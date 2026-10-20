// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp or the
//   seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC24_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC24_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void* __cdecl FUN_007C8E17(unsigned int size);   // operator new

// The adopt-or-allocate constructor for the owned-buffer type whose release is
// at 0x43AE50 and whose size-only constructor is at 0x43ADC0. A caller-supplied
// buffer is adopted and not owned; allocation happens only when none is given
// *and* the size is positive.
struct Owned_0043AD00
{
    void*         Buffer;        // +0x0000
    int           Length;        // +0x0004
    unsigned char IsAllocated;   // +0x0008

    // FUNCTION: GAMEMD 0x43AD00
    Owned_0043AD00* FUN_0043AD00(void* buffer, int size);
};
GG_STATIC_ASSERT(offsetof(Owned_0043AD00, IsAllocated) == 0x8);

// GLOBAL: GAMEMD 0xA8E9AC / 0xA8E9B8 — an array of records and its count. Both
// are re-read on every iteration rather than hoisted.
struct Rec_00422B80 { char _pad000[0xCC]; void* atCC; char _padD0[0x195 - 0xD0]; unsigned char at195; };
extern Rec_00422B80** DAT_00A8E9AC;
extern int            DAT_00A8E9B8;

// FUNCTION: GAMEMD 0x422B80 — clear a flag on every record pointing at `key`.
void __fastcall FUN_00422B80(void* key);

#endif  // GG_MATCH_CORE_SMALL_MISC24_METHODS_H
