// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at 0x402190 and 0x404140.

#include "paired_object_methods.h"

// FUNCTION: GAMEMD 0x402190
//
// Bring an instance up: install the three hooks, clear the pairing block and
// the counters, seed +0x94 from the global at 0x87DE30, and arm the first
// timer group.
//
// The zeroes all come from one register (EDI), so they are written as a
// variable rather than as sixteen literals.
void Obj_00402190::FUN_00402190()
{
    int zero = 0;

    this->Hook15C = FUN_004022C0;
    this->Hook160 = FUN_00402330;
    this->Hook164 = FUN_004023F0;

    this->Peer        = 0;
    this->Hook_B4     = 0;
    this->field_B8    = zero;
    this->field_BC    = zero;
    this->PeerBackRef = 0;

    this->field_0C = 1;
    this->field_A8 = zero;
    this->field_A4 = zero;
    this->field_A0 = zero;

    this->field_94 = DAT_0087DE30;
    this->field_90 = 0;
    this->field_98 = 0;
    this->field_9C = 0;

    FUN_00401000(&this->TimersA);

    this->Current = 0;
}

// FUNCTION: GAMEMD 0x402220
//
// Recompute the second timer group from the first and from every group this
// instance is currently linked to, then clear the running bit on each source
// it consumed.
//
// Only the first two sources get their running bit cleared — the object's own
// group and the one at +0x90. The other four are read-only here.
//
// The two group addresses split on the section 4.6 rule. The target is used
// nine times and retail computes it in the prologue, so it is a local. The
// object's own group is used twice and retail computes it *after* the first
// call (`LEA EBX,[ESI+0x10]` at 0x402239), so it is written inline — naming it
// in a local puts its LEA in the prologue alongside the target's and swaps the
// two argument registers on the call that follows.
void Obj_00402190::FUN_00402220()
{
    Ctx_00402220* context = this->Context;
    Obj_00401000* target  = &this->TimersB;

    FUN_00401000(target);
    FUN_004010C0(target, &this->TimersA);
    FUN_00401170(&this->TimersA);

    if (this->field_90 != 0) {
        FUN_004010C0(target, this->field_90);
        FUN_00401170(this->field_90);
    }
    if (this->field_94 != 0) {
        FUN_004010C0(target, this->field_94);
    }
    if (this->field_98 != 0) {
        FUN_004010C0(target, this->field_98);
    }
    if (this->field_9C != 0) {
        FUN_004010C0(target, this->field_9C);
    }

    FUN_004010C0(target, &context->Timers);

    if (context->At_E8 != 0) {
        FUN_004010C0(target, context->At_E8);
    }
}

// FUNCTION: GAMEMD 0x402330
//
// Advance one step: spend a tick of the countdown at +0xA8, resolve the queued
// entry to its record, publish the record's two values, then run the optional
// callback and the dispatch-table slot.
//
// The zero case is written as the `else`, not the `if`. Retail's fallthrough is
// the counting path and the `Current = 0` store sits out of line at 0x4023B0;
// testing for zero first puts that one store inline and the whole body behind a
// jump.
//
// The countdown treats -1 as "runs forever" and is otherwise decremented, so
// the guard is a comparison against -1 rather than against zero.
//
// Retail reloads +0xA8 for each of the three uses: field_A8 is declared
// volatile (this hook runs on the mixer thread; see the header).
//
// The two branches read the entry differently and retail keeps that asymmetry:
// the record branch clears the entry through the pointer it already holds in
// EDI, while the no-record branch re-reads `[ESI+0x168]`. Written with the
// local on both sides VC6 keeps EDI in both and drops the reload.
int __fastcall FUN_00402330(Obj_00402190* self)
{
    if (self->field_A8 != 0) {
        if (self->field_A8 != -1) {
            self->field_A8 = self->field_A8 - 1;
        }

        Item_00402330* item = self->Current;
        if (item != 0) {
            Rec_00402330* record = FUN_00408520(item);
            self->field_16C = record;

            if (record != 0) {
                self->field_170 = record->At_0C;
                int value = record->At_10;
                self->field_174 = value;
                self->field_178 = value;
                item->At_00 = 0;
            } else {
                self->field_170 = self->Current->At_00;
                int value = self->Current->At_04;
                self->field_174 = value;
                self->field_178 = value;
            }
        }
    } else {
        self->Current = 0;
    }

    if (self->Hook_B4 != 0) {
        self->Hook_B4(self);
    }
    if (self->Current != 0) {
        self->VTable_D4[9](self);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4024A0
//
// The seed is stored before +0x90 in source order; VC6 then loads it ahead
// of the +0x90 store as retail does.
//
// Re-run the bring-up, but only when bit 3 of +0xA4 asks for it. The bit is
// cleared first and then +0xA4 is zeroed wholesale a few stores later, so the
// initial clear is a dead store, and retail keeps it because +0xA4 is
// declared volatile (shared with the mixer thread; see the header).
//
// This is 0x402190's body behind a flag test, and the two are written out
// separately rather than shared.
void Obj_00402190::FUN_004024A0()
{
    if (this->field_A4 & 8) {
        this->field_A4 = this->field_A4 & ~8;

        int zero = 0;

        this->Hook15C = FUN_004022C0;
        this->Hook160 = FUN_00402330;
        this->Hook164 = FUN_004023F0;

        this->Peer        = 0;
        this->Hook_B4     = 0;
        this->field_B8    = zero;
        this->field_BC    = zero;
        this->PeerBackRef = 0;

        this->field_0C = 1;
        this->field_A8 = zero;
        this->field_A4 = zero;
        this->field_A0 = zero;

        this->field_94 = DAT_0087DE30;
        this->field_90 = 0;
        this->field_98 = 0;
        this->field_9C = 0;

        FUN_00401000(&this->TimersA);

        this->Current = 0;
    }
}

// FUNCTION: GAMEMD 0x404140
//
// Break the pairing, but only from the side that currently owns it: the peer's
// back-reference has to point at this object, otherwise the pair has already
// been re-formed elsewhere and nothing is touched.
//
// Every one of the seven clears re-reads `this->Peer` in retail rather than
// holding it, so the member is written out at each store instead of being
// hoisted into a local.
void Obj_00402190::FUN_00404140()
{
    Obj_00402190* peer = this->Peer;

    if (peer != 0 && this == peer->PeerBackRef) {
        if (this->TimersA.First.Flags2 & 2) {
            FUN_004025B0(peer);
        }
        FUN_004026F0(this->Peer);

        this->Peer->PeerBackRef = 0;
        this->Peer->field_BC    = 0;
        this->Peer->Hook_B4     = 0;
        this->Peer->field_B8    = 0;
        this->Peer->field_90    = 0;
        this->Peer->field_98    = 0;
        this->Peer->field_9C    = 0;
        this->Peer = 0;
    }
}
