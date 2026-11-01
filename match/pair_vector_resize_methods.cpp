// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x41C500.

#include "pair_vector_resize_methods.h"

// FUNCTION: GAMEMD 0x41C500
//
// Grow the vector by `extra` slots. Allocate, copy the live elements across
// field by field, free the old block, and invalidate the cached lookup slot.
// A negative request and a failed allocation both report false without touching
// anything.
//
// The allocation is `new Pair[total]`, not a raw allocator call. See the header:
// the array-new form is what produces retail's `DEC`/spill pair after the null
// check, which is the elided vector-constructor-iterator setup. Two other
// readings of those two instructions were tried and both are wrong — a dead
// store to the parameter's home slot and a dead store to a local are each
// removed by VC6, so neither can be their source.
//
// The copy is a whole-struct assignment through an explicit byte offset, and both
// halves of that matter. The struct assignment is what makes VC6 move the pair as
// two dwords sharing one address computation (`MOV [EAX+EDI],EBX` /
// `MOV [EAX+EDI+4],EDX`); assigning the two members separately emits the same
// instructions in a different order and with different registers (78.6%). The
// byte offset is what makes the index a plain register rather than a scaled one:
// retail computes `i * 8` once with `LEA EAX,[ECX*8]` and uses it as the base for
// both arrays.
//
// Count and Items are both re-read every iteration — retail's `MOV EBX,[ESI]` at
// 0x41C537 and `MOV EAX,[ESI+4]` at 0x41C551 are inside the loop — so neither is
// hoisted into a local.
bool PairVector_0041C500::Grow(int extra)
{
    Pair_0041C500* grown;
    int total;
    int i;

    if (extra < 0) goto fail;

    total = Capacity + extra;
    grown = new Pair_0041C500[total];
    if (grown == 0) goto fail;
    for (i = 0; i < Count; i++) {
        int off = i * 8;
        Pair_0041C500* src = (Pair_0041C500*)((char*)Items + off);
        *(Pair_0041C500*)((char*)grown + off) = *src;
    }

    delete[] Items;

    Items    = grown;
    Capacity = Capacity + extra;
    Cached   = 0;
    return true;

fail:
    return false;
}
