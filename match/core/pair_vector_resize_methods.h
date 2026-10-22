// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x41C500. The element size is 8 (`LEA EAX,[EBX*8]` for
//   the allocation and the two dword copies per iteration).
#ifndef GG_MATCH_CORE_PAIR_VECTOR_RESIZE_METHODS_H
#define GG_MATCH_CORE_PAIR_VECTOR_RESIZE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// 0x7C8E17 and 0x7C8B3D are `operator new` and `operator delete`; the calls are
// generated rather than written, so they are not declared here.

// The user-declared default constructor is load-bearing. `new Pair[n]` on a
// class that declares one makes VC6 emit its vector-constructor-iterator
// preamble — `DEC count` followed by a spill of the count — and then elide the
// loop itself because the constructor is empty. Retail has exactly that leftover
// pair at 0x41C52C/0x41C52F, and it is unreachable with a POD (which compiles
// the allocation to a bare `operator new` and no counter at all).
struct Pair_0041C500
{
    int Key;      // +0x0000
    int Value;    // +0x0004

    Pair_0041C500() {}
};
GG_STATIC_ASSERT(sizeof(Pair_0041C500) == 8);

// A key/value vector with a separate sorted flag at +0xC and a cached lookup
// slot at +0x10 that any growth invalidates.
struct PairVector_0041C500
{
    Pair_0041C500* Items;   // +0x0000
    int Count;              // +0x0004
    int Capacity;           // +0x0008
    char Sorted;            // +0x000C
    char _pad00D[0x3];      // +0x000D
    int  Cached;            // +0x0010

    // FUNCTION: GAMEMD 0x41C500
    bool Grow(int extra);
};
GG_STATIC_ASSERT(offsetof(PairVector_0041C500, Capacity) == 0x8);
GG_STATIC_ASSERT(offsetof(PairVector_0041C500, Sorted) == 0xC);
GG_STATIC_ASSERT(offsetof(PairVector_0041C500, Cached) == 0x10);

#endif  // GG_MATCH_CORE_PAIR_VECTOR_RESIZE_METHODS_H
