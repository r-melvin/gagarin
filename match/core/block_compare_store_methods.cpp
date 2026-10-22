// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x402800.

#include <string.h>
#include "block_compare_store_methods.h"

#pragma intrinsic(memcmp, memcpy)

//
// Store a 32-byte block only if it differs from the one already held, and
// report whether it changed.
//
// PARTIAL: direct flag stores and return; no volatile reload for scheduling.
// FUNCTION: GAMEMD 0x402800
int __fastcall FUN_00402800(Obj_00402800* self, const int* incoming)
{
    // The zero is a named variable, not a literal: retail materialises it
    // once with `XOR EBP,EBP` *before* the compare and uses that register for
    // both the store and the return. Two literal zeroes give an immediate
    // store and a separate `XOR EAX,EAX` on the way out.
    //
    // The memcmp operands are the incoming block first. VC6 loads the first
    // argument into ESI and the second into EDI, and retail has the object's
    // own block in EDI (`MOV EDI,EBX` at 0x402811), so the object is the
    // second argument here even though it is the one being written.
    int unchanged = 0;

    if (memcmp(incoming, self->Block, sizeof(self->Block)) == 0) {
        self->Changed = unchanged;
        return unchanged;
    }

    self->Changed = 1;
    memcpy(self->Block, incoming, sizeof(self->Block));
    return self->Changed;
}
