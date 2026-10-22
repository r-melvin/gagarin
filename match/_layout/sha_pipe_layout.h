// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
// Retail 0x4741F0/0x474320/0x474430/0x476D80 construct this 0x80-byte
// stack view. RTTI identifies its bound vtable 0x7E4D78 as SHAPipe -> Pipe.
// Pipe destructor 0x631C80 confirms links at +4/+8; Result 0x69E9E0
// forwards the state at +0x0C. Original declarations/constructor are unknown.
// This data-only view has no implicit cleanup; native methods are bound at
// their call sites. sizeof below describes the compiled view, not ownership.
#ifndef GG_MATCH_LAYOUT_SHA_PIPE_LAYOUT_H
#define GG_MATCH_LAYOUT_SHA_PIPE_LAYOUT_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct SHAPipeLayout
{
    char* Vtable;
    void* ChainTo;
    void* ChainFrom;
    char IsCached;
    char unknown_0D[3];
    char FinalResult[0x14];
    unsigned int Acc[5];
    int Length;
    int PartialCount;
    char Partial[0x40];
};
GG_STATIC_ASSERT(offsetof(SHAPipeLayout, Vtable) == 0);
GG_STATIC_ASSERT(offsetof(SHAPipeLayout, ChainTo) == 4);
GG_STATIC_ASSERT(offsetof(SHAPipeLayout, ChainFrom) == 8);
GG_STATIC_ASSERT(offsetof(SHAPipeLayout, IsCached) == 0x0C);
GG_STATIC_ASSERT(offsetof(SHAPipeLayout, unknown_0D) == 0x0D);
GG_STATIC_ASSERT(offsetof(SHAPipeLayout, FinalResult) == 0x10);
GG_STATIC_ASSERT(offsetof(SHAPipeLayout, Acc) == 0x24);
GG_STATIC_ASSERT(offsetof(SHAPipeLayout, Length) == 0x38);
GG_STATIC_ASSERT(offsetof(SHAPipeLayout, PartialCount) == 0x3C);
GG_STATIC_ASSERT(offsetof(SHAPipeLayout, Partial) == 0x40);
GG_STATIC_ASSERT(sizeof(unsigned int) == 4);
GG_STATIC_ASSERT(sizeof(SHAPipeLayout) == 0x80);
#endif
