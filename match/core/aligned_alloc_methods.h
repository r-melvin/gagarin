// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, the node size and the alignment arithmetic read numerically off
//   the user's retail gamemd.exe v1.001 via the local Ghidra CLI at 0x408D80.
//
// Allocate a 0x3C-byte descriptor and, under it, a buffer big enough to hold
// `size` bytes at an address aligned to `1 << shift`.
//
// The alignment is the textbook round-up: `(raw + align - 1) & -(align)`, with
// the mask built as `OR EAX,-1; SHL EAX,CL` rather than from the alignment
// value, so it is written `-1 << shift` and not `~(align - 1)`.
//
// A failed buffer allocation frees the descriptor - guarded against null even
// though it was just written through - and answers null.
#ifndef GG_MATCH_CORE_ALIGNED_ALLOC_METHODS_H
#define GG_MATCH_CORE_ALIGNED_ALLOC_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "intrusive_list_methods.h"

extern "C" void* __cdecl FUN_007C8E17(unsigned int size);
extern "C" void  __cdecl FUN_007C8B3D(void* block);
extern "C" void* __cdecl memset(void* destination, int value, unsigned int count);

// FUNCTION: GAMEMD 0x4072D0 — initialises the descriptor's link block.
void FUN_004072D0(void* descriptor);

struct Entry8b { int First; int Second; };

struct Aligned_00408D80
{
    ListNode Links;
    int unknown_0C;
    void* Raw;       // +0x0010
    int   Shift;     // +0x0014
    int   Aligned;   // +0x0018
    int   Size;      // +0x001C
    Entry8b Entries[2];
    void* unknown_30;
    int unknown_34;
    int unknown_38;
    // FUNCTION: GAMEMD 0x408E50
    Aligned_00408D80* FUN_00408E50();
};
GG_STATIC_ASSERT(offsetof(Aligned_00408D80, Links) == 0);
GG_STATIC_ASSERT(offsetof(Aligned_00408D80, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Aligned_00408D80, Entries) == 0x20);
GG_STATIC_ASSERT(offsetof(Aligned_00408D80, unknown_34) == 0x34);
GG_STATIC_ASSERT(sizeof(Aligned_00408D80) == 0x3C);
GG_STATIC_ASSERT(offsetof(Aligned_00408D80, Raw) == 0x10);
GG_STATIC_ASSERT(offsetof(Aligned_00408D80, Size) == 0x1C);

// FUNCTION: GAMEMD 0x408D80
Aligned_00408D80* FUN_00408D80(int size, int shift);

#endif  // GG_MATCH_CORE_ALIGNED_ALLOC_METHODS_H
