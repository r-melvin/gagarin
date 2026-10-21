// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// RTTI TD 0x81BF98 / COL 0x7FCCC8 identifies SHAPipe -> Pipe at offset zero.
// Retail table 0x7E4D78 has five slots: 477750,631D30,477740,631CC0,69E9B0.
// Only the two method bodies below are bound here. Native deleting-wrapper
// call relocation closure is unresolved; no native constructor or table is
// instantiated. Existing automatic storage stays in SHAPipeLayout.
// Fields describe the instruction-confirmed 0x80-byte stack view, not a
// recovered original constructor, allocation extent or complete source class.
#ifndef GG_MATCH_LAYOUT_SHA_PIPE_H
#define GG_MATCH_LAYOUT_SHA_PIPE_H
#include "pipe.h"

class SHAPipe : public Pipe
{
public:
    unsigned char IsCached;
    char unknown_0D[3];
    char FinalResult[0x14];
    unsigned int Acc[5];
    int Length;
    int PartialCount;
    char Partial[0x40];

    // FUNCTION: GAMEMD 0x69E9B0 -- observed slot-4 override; argument ABI views.
    virtual int FUN_00631D10(int first, int second);
    // FUNCTION: GAMEMD 0x69E9E0 -- nonvirtual forwarding call view.
    void Result(void* out);
};
GG_STATIC_ASSERT(offsetof(SHAPipe, IsCached) == 0x0C);
GG_STATIC_ASSERT(offsetof(SHAPipe, unknown_0D) == 0x0D);
GG_STATIC_ASSERT(offsetof(SHAPipe, FinalResult) == 0x10);
GG_STATIC_ASSERT(offsetof(SHAPipe, Acc) == 0x24);
GG_STATIC_ASSERT(offsetof(SHAPipe, Length) == 0x38);
GG_STATIC_ASSERT(offsetof(SHAPipe, PartialCount) == 0x3C);
GG_STATIC_ASSERT(offsetof(SHAPipe, Partial) == 0x40);
GG_STATIC_ASSERT(sizeof(unsigned int) == 4);
GG_STATIC_ASSERT(sizeof(SHAPipe) == 0x80);
#endif
