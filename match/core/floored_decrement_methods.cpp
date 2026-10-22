// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at 0x408230.

#include "floored_decrement_methods.h"

// FUNCTION: GAMEMD 0x402860
//
// The two counter bumps are separate load/inc/store trios, and BOTH run through
// one shared named local. That is the whole lever: retail reuses EAX for the
// second trio, and a compound `+= 1` on each member makes cl take a second
// register (ECX) for it, which is 84.2% instead of 100%. Binding the loaded
// value to a name and reusing the same name for the second counter puts both
// trios in one register, as retail has them. PARTIAL: with ordinary member
// accesses cl batches both loads, increments and stores, where retail keeps
// two separate trios; that difference is accepted.
void __fastcall FUN_00402860(Owner_00402860* self, Member_00402860* member)
{
    member->Owner = self;

    // One shared local so both trios use one register, as retail does.
    int n = self->Attached;
    self->Attached = n + 1;
    n = self->Pending;
    self->Pending = n + 1;

    FUN_00407420(self->Link, member);

    int pending = self->Pending;

    self->Pending = pending - 1;

    if (pending - 1 < 0) {
        self->Pending = 0;
    }
}

// FUNCTION: GAMEMD 0x4028B0
//
// Same shape as its sibling at 0x402860, and the same lever: both counter
// trios through one shared named local. With a compound assignment on each
// member instead, cl takes a second register for the second trio: 86.4%.
// PARTIAL with ordinary member accesses (no volatile); see 0x402860.
void __fastcall FUN_004028B0(Member_00402860* self)
{
    Owner_00402860* owner = self->Owner;

    FUN_00407450(self);

    int n = owner->Attached;
    owner->Attached = n - 1;
    n = owner->Pending;
    owner->Pending = n + 1;

    FUN_00407450(self);

    int pending = owner->Pending;

    owner->Pending = pending - 1;

    if (pending - 1 < 0) {
        owner->Pending = 0;
    }
}

// FUNCTION: GAMEMD 0x4034B0
//
// BLOCK-ORDER DELTA (status partial, 33.3%). Everything through the second test
// is exact - the capacity compare, the allocation, the null test - and so is the
// body. What differs is where the two tails sit: retail emits the shared
// `return 0` *between* the tests and the body, and VC6 puts the body first and
// the zero block last, which inverts both branches with it. Three shapes tried:
// a result variable initialised to null, nested guards with the body inside,
// and the combined-condition early return below. All land on 33.3% or worse.
// Same signature as the 0x456FB0 delta, where VC6 likewise refused to lay the
// secondary tail first.
// Lift pass (2026-09-18): three more shapes rejected - two separate early
// returns before the allocation (17.9%), the combined condition with an
// explicit `else { member = 0; }` (33.3%), and an explicit `goto fail;` /
// `goto attach;` layout that spells retail's block order literally in the
// source (33.3%, byte-identical stream to the combined form). cl 8804 always sinks the
// constant-zero tail past the body; the only residual is that placement (plus
// the `JNZ body` / `JE tail` polarity it forces).
// Lift pass 3 (2026-09-18): the shared-named-local bump lever that took
// 0x402860, 0x4028B0 and 0x403530 does not reach this one - both
// counter trios through one local is still 33.3%. The bumps here were already in retail's
// registers; the residual really is only the block order.
// Lift pass 2 (2026-09-18): re-tried the null-initialised result returned by
// name from both guards (`return member;` twice) - 17.9%, worse again. This is
// the banked 8447-vs-8804 "sunk constant-return tail" class; the combined
// condition below stays as the best-measured form at 33.3% (12/36, the only
// mnemonic delta being the JNE/JE polarity the sinking forces).
Member_00402860* __fastcall FUN_004034B0(Pool_00402860* self)
{
    // Both refusals share one `POP EDI; XOR EAX,EAX; POP ESI; RET` that sits
    // *between* the tests and the body, so they are one early return written as
    // a combined condition rather than two nested guards - nesting puts the
    // body first and the zero block last (33.3%).
    Member_00402860* member;

    if (self->Attached >= self->Capacity
        || (member = FUN_00402040(self)) == 0) {
        return 0;
    }

    member->Owner = (Owner_00402860*)self;

    self->Attached += 1;
    self->Pending += 1;

    FUN_00407420(self->Link, member);

    int pending = self->Pending;

    self->Pending = pending - 1;

    if (pending - 1 < 0) {
        self->Pending = 0;
    }

    return member;
}

// FUNCTION: GAMEMD 0x403530
//
// The loop form of 0x4034B0. Two source-shape findings:
//
//   * The loop is `while (1) { if (!(capacity test)) break; ... if (!(--count
//     != 0)) break; }` with one shared return after it, the negation wrapping
//     each whole test. Retail's loop is un-rotated: one copy of the capacity
//     test at the top and `DEC EBP; JNZ 0x403539` as the back edge, with all
//     three exits converging on a single `MOV EAX,EDI` epilogue. Written with
//     `return made` at each exit and a `goto top` back edge, cl 8804 rotates
//     it and duplicates the `MOV/MOV/CMP/JL` head (57.1%); a plain `while` with
//     two breaks is 54.8%; a structured `do { ... } while (--count != 0);` with
//     early returns is 57.1% and byte-identical to the goto form.
//
//   * Both counter bumps through one shared named local, the same lever as
//     0x402860 and 0x4028B0 above — without it cl takes EDX for the second
//     trio where retail reuses ECX, and the loop form sits at 92.1%.
//
// PARTIAL (86.8%): the capacity compare and bumps are ordinary member
// accesses. The earlier volatile reads that restored the `XOR EDI,EDI`
// position and the separate trios were removed as match steering.
int __fastcall FUN_00403530(Pool_00402860* self, int count)
{
    int made = 0;

    while (1) {
        if (!(self->Attached < self->Capacity)) {
            break;
        }

        Member_00402860* member = FUN_00402040(self);

        if (member == 0) {
            break;
        }

        member->Owner = (Owner_00402860*)self;

        int n = self->Attached;
        self->Attached = n + 1;
        n = self->Pending;
        self->Pending = n + 1;

        FUN_00407420(self->Link, member);

        int pending = self->Pending;

        self->Pending = pending - 1;

        if (pending - 1 < 0) {
            self->Pending = 0;
        }

        made++;

        if (!(--count != 0)) {
            break;
        }
    }

    return made;
}

// FUNCTION: GAMEMD 0x408230
//
// Tick every entry's counter down, never below zero. See the header for why the
// decrement is written twice.
void __cdecl FUN_00408230()
{
    if (DAT_0087E81C == 0) {
        return;
    }

    ListNode* node = (&DAT_0087E810)->FUN_004073C0();

    if (node == 0) {
        return;
    }

    do {
        Counted_00408230* entry = (Counted_00408230*)node;

        int counter = entry->Counter;

        entry->Counter = counter - 1;

        if (counter - 1 < 0) {
            entry->Counter = 0;
        }

        node = (node)->FUN_004073E0();
    } while (node);
}
