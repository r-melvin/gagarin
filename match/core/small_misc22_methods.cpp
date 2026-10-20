// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc22_methods.h"

// ALLOCATION DELTA (status partial, 83.3% - 15/18). Every instruction matches
// except which register holds the byte offset and which holds the cursor:
// retail computes the product into ECX with the base in ESI, we do the reverse.
// Three phrasings tried - the offset inline, hoisted into a named local, and
// added to the cursor as a separate statement - all give the same assignment.
//
// Ten expression forms were measured against a labelled control in one compile
// and every one is BYTE-IDENTICAL to it (83.3%): the cursor initialised from
// `base + stride * count` in one initialiser; the product named and added; the
// product named ahead of the cursor's declaration; the factors written the
// other way round; `cursor = cursor + stride * count`; the subscript form
// `&base[stride * count]`; the product re-derived at the use site through the
// named cursor; both factors bound to their own locals first; and an `end`
// pointer named separately. Per the fifteenth batch, identical bytes across
// every spelling retire the expression level here: which register accumulates
// is not source-selectable.
//
// FRONT END (batch thirty-nine): REFUTED for this body. It is as procedural as
// anything in the tree -- a `__stdcall` free function walking raw memory through
// a function pointer, no receiver, no vtable, no allocation -- so it is the
// natural first candidate for a C translation unit. The identical body compiled
// as `.c` in three spellings scores 83.3%, exactly the C++ number. The front end
// is not the lever for this residual.
//
// FUNCTION: GAMEMD 0x40AFD0
// Same guard shape as the forward walk: the decremented count is tested as its
// own value so the branch reuses DEC's flags.
void __stdcall FUN_0040AFD0(char* base, int stride, int count, ElemFn2 fn)
{
    // PERMUTER FINDING (score 0 at candidate 625, base 20). The lever is that
    // the walk mutates the *parameter* in place; every one of the ten spellings
    // measured above kept a separate `cursor` local, and all ten were
    // byte-identical because the extra local is what pins the product into ESI
    // and the base into ECX. Walking `base` itself gives retail's assignment
    // (product into ECX, cursor in ESI) with no other change.
    base += stride * count;

    if (--count < 0) {
        return;
    }

    for (int i = count; i >= 0; i--) {
        base -= stride;

        fn(base);
    }
}

// FUNCTION: GAMEMD 0x432690
// Everything is cleared except the two fields that start "unset" rather than
// zero: -1 at +0x28 and 1 at +0x2C.
Obj_00432690* Obj_00432690::FUN_00432690(int arg)
{
    // Volatile so the argument load stays where retail has it - immediately
    // before the push - rather than being hoisted above the field writes.
    *(volatile unsigned char*)&unknown_00 = 0;
    *(volatile int*)&unknown_04 = 0;
    *(volatile int*)&unknown_0C = 0;
    *(volatile int*)&unknown_20 = 0;
    *(volatile unsigned char*)&unknown_2D = 0;

    unknown_28 = -1;
    unknown_2C = 1;

    FUN_00432750(arg);

    return this;
}

// PROLOGUE DELTA (status partial, 72.2% - 13/18). The seven field stores and
// the call are byte-exact; the four prologue instructions differ in which
// register holds which argument and where the zeroing XOR sits. Retail loads
// the call's argument into EDX and pushes it before the first field store; we
// load it into EAX, store the field first, then zero EAX and push from ECX.
// The volatile pattern that fixed the sibling at 0x432690 makes this one worse
// (33.3%), so it is left plain.
//
// FUNCTION: GAMEMD 0x4326C0
Obj_00432690* Obj_00432690::FUN_004326C0(int arg, int extra)
{
    unknown_0C = extra;

    unknown_00 = 0;
    unknown_04 = 0;
    unknown_20 = 0;
    unknown_28 = -1;
    unknown_2C = 1;
    unknown_2D = 0;

    FUN_00432750(arg);

    return this;
}
