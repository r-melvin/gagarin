// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Pipe COL pointer at 0x7E6214 -> 0x7FFDB8 / TD 0x81BF80 names .?AVPipe@@. The vtable
// words at 0x7E6218 are 0x4AEC80, 0x631D30, 0x477740, 0x631CC0, and
// 0x631D10. The destructor 0x631C80 reads and clears the two links at +4/+8;
// 0x631CC0 and 0x631D30 confirm their use. The five-slot check is conditional
// on VC6's unresolved SEARCH_LIBRARY default for its vector-deleting alias.
#ifndef GG_MATCH_LAYOUT_PIPE_H
#define GG_MATCH_LAYOUT_PIPE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class Pipe
{
public:
    Pipe* ChainTo;   // +0x04
    Pipe* ChainFrom; // +0x08

    // The compiler emits the retail scalar-deleting entry at 0x4AEC80 and
    // ordinary destructor body at 0x631C80 from this virtual destructor.
    virtual ~Pipe();

    // Vtable slot +0x04; follows ChainTo through the same slot.
    // FUNCTION: GAMEMD 0x631D30
    virtual int FUN_00631D30();
    // Vtable slot +0x08; tail-dispatches to slot +0x04.
    // FUNCTION: GAMEMD 0x477740
    virtual int FUN_00477740();
    // Vtable slot +0x0C.
    // FUNCTION: GAMEMD 0x631CC0
    // Descriptive method name; original spelling/signature is unestablished.
    virtual void SetChainTo(Pipe* next);
    // Vtable slot +0x10.
    // FUNCTION: GAMEMD 0x631D10
    virtual int FUN_00631D10(int first, int second);
};

GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(offsetof(Pipe, ChainTo) == 0x04);
GG_STATIC_ASSERT(offsetof(Pipe, ChainFrom) == 0x08);
GG_STATIC_ASSERT(sizeof(Pipe) == 0x0C);
GG_STATIC_ASSERT(sizeof(int (Pipe::*)()) == 4);

// VTABLE: GAMEMD 0x7E6218 -- five observed slots; slot 0 resolves through
// the recorded VC6 weak deleting-destructor default (conditional check).

#endif // GG_MATCH_LAYOUT_PIPE_H
