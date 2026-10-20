// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x402800.

#include <string.h>
#include "block_compare_store_methods.h"

#pragma intrinsic(memcmp, memcpy)

// FUNCTION: GAMEMD 0x402800
//
// Store a 32-byte block only if it differs from the one already held, and
// report whether it changed.
//
// PARTIAL (66.7%, 20/30). Two deltas, both one instruction.
//
// Scheduling: on the copy path retail sets up the REP MOVSD registers first and
// then slots the flag store and its reload into the gap before the `rep`; VC6
// emits the store and reload first and the setup immediately ahead of the `rep`.
// Same instructions, different order.
//
// Register materialisation: on the equal path retail returns the zero with
// `MOV EAX,EBP`, reusing the register it stored from, where VC6 emits
// `XOR EAX,EAX`. Both are two bytes, so nothing forces either. The zero *is* in
// EBP on both sides — the named variable earns the register (see below) — VC6
// just declines to read it back. Same family as the register-naming class in
// section 4.8.
//
// The equal path still writes the flag — it clears it — so the caller can read
// the flag rather than the return value. Retail returns the flag by re-reading
// the member it just wrote (`MOV EAX,[EAX+0x19C]` at 0x40283B) rather than
// reusing the constant, and it does that read *before* the REP MOVSD; that
// falls out of returning the member rather than the literal.
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

    // Retail re-reads the flag it has just written (`MOV EAX,[EAX+0x19C]` at
    // 0x40283B) and does so *before* the REP MOVSD. Written as a plain
    // `return self->Changed;` VC6 forwards the stored constant and the read
    // disappears, so the reload is spelled through a volatile lvalue. Only
    // this path needs it — the equal path above returns the same register it
    // stored, with no reload, which is why the member itself is not volatile.
    self->Changed = 1;
    int changed = *(volatile int*)&self->Changed;
    memcpy(self->Block, incoming, sizeof(self->Block));
    return changed;
}
