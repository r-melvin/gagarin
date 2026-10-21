// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// RTTI TD 0x81BFB0 names .?AVStraw@@; its one-entry CHD has no additional
// base. The primary vtable at 0x7E61F0 has three slots: 0x4AEC10, 0x6C9890,
// and 0x6C98E0. The word at 0x7E61FC is the next table's COL pointer, proving
// the three-slot boundary. Slot 0 resolves conditionally through VC6's
// unresolved SEARCH_LIBRARY default for ??_EStraw; this is not final-link proof.
// Entry-origin instructions at 0x6C9850/0x6C9890/0x6C98E0 establish links at
// +4/+8 and the ABI views below. The 0x0C size is this observed prefix view.
#ifndef GG_MATCH_LAYOUT_STRAW_H
#define GG_MATCH_LAYOUT_STRAW_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class Straw
{
public:
    Straw* ChainTo;   // +0x04
    Straw* ChainFrom; // +0x08

    // The compiler emits scalar deleting destructor 0x4AEC10 and the
    // ordinary destructor body at 0x6C9850 from this virtual destructor.
    virtual ~Straw();

    // Slot +0x04; descriptively named for its observed link mutation.
    // FUNCTION: GAMEMD 0x6C9890
    virtual void SetChainTo(Straw* next);

    // Slot +0x08. The name and high-level argument types are not recovered;
    // these int parameters are the observed two-word stack ABI view.
    // FUNCTION: GAMEMD 0x6C98E0
    virtual int FUN_006C98E0(int first, int second);
};

GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(offsetof(Straw, ChainTo) == 0x04);
GG_STATIC_ASSERT(offsetof(Straw, ChainFrom) == 0x08);
GG_STATIC_ASSERT(sizeof(Straw) == 0x0C);
GG_STATIC_ASSERT(sizeof(int (Straw::*)()) == 4);

// VTABLE: GAMEMD 0x7E61F0 -- three slots; slot 0 uses the recorded weak default.

#endif // GG_MATCH_LAYOUT_STRAW_H
