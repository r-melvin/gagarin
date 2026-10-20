// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's own retail gamemd.exe v1.001 with
//   the local Ghidra CLI at 0x4D2E40 and its five siblings. The element size is
//   8 (`LEA EAX,[EBX*8]` for the allocation and two dword copies per iteration);
//   Items at +0, Count at +4, Capacity at +8 and the cached lookup slot at
//   +0x10 all come straight off the member accesses.
//
// Six more instances of the key/value vector Grow already matched at 0x41C500.
//
// All six are byte-for-byte identical to that one apart from the two call
// displacements (`operator new` and `operator delete`), so the body is the same
// one, lifted unchanged. Finding them was the point: the family fell out of
// grouping the unmatched functions by (size, masked prefix, masked suffix), and
// the group turned out to be a generalisation of a function solved earlier as a
// one-off.
#ifndef GG_MATCH_CORE_PAIR_VECTOR_GROW_SWEEP_H
#define GG_MATCH_CORE_PAIR_VECTOR_GROW_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The user-declared default constructor is load-bearing. `new Pair[n]` on a
// class that declares one makes VC6 emit its vector-constructor-iterator
// preamble -- `DEC count` followed by a spill of the count -- and then elide the
// loop itself because the constructor is empty. Retail has exactly that leftover
// pair, and it is unreachable with a POD.
struct GrowPair
{
    int Key;      // +0x0000
    int Value;    // +0x0004

    GrowPair() {}
};
GG_STATIC_ASSERT(sizeof(GrowPair) == 8);

struct GrowPairVector
{
    GrowPair* Items;     // +0x0000
    int       Count;     // +0x0004
    int       Capacity;  // +0x0008
    char      Sorted;    // +0x000C
    char      _pad00D[3];// +0x000D
    int       Cached;    // +0x0010

    bool Grow_4D2E40(int extra);   // FUNCTION: GAMEMD 0x4D2E40
    bool Grow_52B570(int extra);   // FUNCTION: GAMEMD 0x52B570
    bool Grow_538B80(int extra);   // FUNCTION: GAMEMD 0x538B80
    bool Grow_5AD930(int extra);   // FUNCTION: GAMEMD 0x5AD930
    bool Grow_6525A0(int extra);   // FUNCTION: GAMEMD 0x6525A0
    bool Grow_710750(int extra);   // FUNCTION: GAMEMD 0x710750
};
GG_STATIC_ASSERT(offsetof(GrowPairVector, Count) == 0x4);
GG_STATIC_ASSERT(offsetof(GrowPairVector, Capacity) == 0x8);
GG_STATIC_ASSERT(offsetof(GrowPairVector, Sorted) == 0xC);
GG_STATIC_ASSERT(offsetof(GrowPairVector, Cached) == 0x10);

#endif  // GG_MATCH_CORE_PAIR_VECTOR_GROW_SWEEP_H
