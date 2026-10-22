// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC13_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC13_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "small_misc12_methods.h"

// GLOBAL: GAMEMD 0x87E728
extern void* DAT_0087E728b;
void __fastcall FUN_004037C0b(void* self, int arg);   // GAMEMD 0x4037C0
void __cdecl FUN_00405040b();                         // GAMEMD 0x405040
void __cdecl FUN_00751080b();                         // GAMEMD 0x751080
void __cdecl FUN_00753510();                          // GAMEMD 0x753510
void __cdecl FUN_00753620();                          // GAMEMD 0x753620

// FUNCTION: GAMEMD 0x406F40
void __cdecl FUN_00406F40();

// A pair of shorts. The result comes back through a caller-supplied pointer
// rather than in EAX even though the type is four bytes: VC6 returns any class
// with a user-declared copy constructor in memory, and that is what the RET 8
// with a hidden first argument records.
struct ShortPair2
{
    short x;   // +0x0000
    short y;   // +0x0002

    // A user-declared *default* constructor is enough to make VC6 return the
    // type in memory rather than EAX, which is what the hidden first argument
    // and RET 8 record. The copy constructor is deliberately left implicit:
    // retail copies the result into the caller's slot with a single dword move,
    // and a user-declared one makes cl assign member-wise into the destination
    // instead, skipping the temporary altogether.
    ShortPair2() { }

    // FUNCTION: GAMEMD 0x42D510
    ShortPair2 FUN_0042D510(const ShortPair2* other) const;
};

// Three shorts per record, so the two reads at +0x80E and +0x810 are fields of
// the same entry rather than parallel arrays: the stride is six and they differ
// by two.
struct Rec3s { unsigned short a, b, c; };

struct Obj_00426DD0
{
    char   _pad000[0x80E];
    Rec3s  Records[1];   // +0x080E

    // FUNCTION: GAMEMD 0x426DD0
    int FUN_00426DD0(int index) const;
};
GG_STATIC_ASSERT(offsetof(Obj_00426DD0, Records) == 0x80E);

// A second instance of the release shape at 0x43AE50, on a different object.
struct Owned_0043AE80
{
    void*         Buffer;        // +0x0000
    int           Length;        // +0x0004
    unsigned char IsAllocated;   // +0x0008

    // FUNCTION: GAMEMD 0x43AE80
    void FUN_0043AE80();
};
GG_STATIC_ASSERT(offsetof(Owned_0043AE80, IsAllocated) == 0x8);

#endif  // GG_MATCH_CORE_SMALL_MISC13_METHODS_H
