// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x401000.

#include "triple_timer_init_methods.h"

// FUNCTION: GAMEMD 0x401000
void __fastcall FUN_00401000(Obj_00401000* self)
{
    // The sub-object addresses are written inline, not hoisted into locals:
    // retail materialises each `LEA` lazily at its first use (after the
    // preceding call) and only then holds it. Naming them up front puts both
    // LEAs in the prologue.
    FUN_00407100(&self->First, 0x4000);
    FUN_00407100(&self->Second, 0x64);
    FUN_00407100(&self->Third, 0x2000);

    FUN_004071A0(&self->Second, 0xA, 0x3E8, 0);
    FUN_004071A0(&self->First, 0x4000, 0x3E8, 0);
    FUN_004071A0(&self->Third, 0x4000, 0x3E8, 0);

    FUN_00407150(&self->First, 0x4000);
}

// FUNCTION: GAMEMD 0x4010C0
//
// Scale this object's three timers by another's. Each timer takes the whole
// part of its own 16.16 value times the whole part of the other's, but the
// three combine differently: the first shifts the product down by 14, the
// second divides it by 100 (the 0x51EB851F / SAR 5 magic sequence at
// 0x4010F4), and the third is an additive offset around 0x2000 rather than a
// product at all.
//
// PARTIAL (62.1%, 36/58). One instruction of delta, and it is an insertion
// rather than a difference: everything up to the `JNS` at 0x40116C is exact,
// then VC6 folds the two `LEA ECX,[ESI+0x50]` uses inside the negative branch
// into a single `ADD ESI,0x50`, because ESI is dead after that block. Retail
// recomputes the LEA at each use. Only that one block is affected — the high
// clamp and the shared tail each use the address once, so VC6 leaves their
// LEAs alone, which is what makes the fold profitable there and nowhere else.
// Four phrasings produce it identically (address inline, address hoisted into
// a local, the zero written through the offset variable, and the address
// spelled off a different member), so the choice is not reachable from source.
// See section 4.8, "callee-saved base bias".
//
// The third block's zero test is on the *offset*, not the sum: when the other
// object's whole part is exactly 0x2000 the timer is left alone and only reset.
// The clamp either side is asymmetric in retail — the low end is a sign test
// (`JNS`) and the high end an unsigned compare (`JBE`) — so the low guard is
// written against a signed value and the high one against an unsigned.
void __fastcall FUN_004010C0(Obj_00401000* self, Obj_00401000* other)
{
    FUN_00407150(&self->First,
                 (int)(((self->First.Value >> 16) * (other->First.Value >> 16))
                       >> 14));
    FUN_004071C0(&self->First);

    FUN_00407150(&self->Second,
                 (int)((self->Second.Value >> 16) * (other->Second.Value >> 16))
                     / 100);
    FUN_004071C0(&self->Second);

    unsigned int offset = (other->Third.Value >> 16) - 0x2000;
    if (offset != 0) {
        offset += self->Third.Value >> 16;
        if ((int)offset < 0) {
            FUN_00407150(&self->Third, 0);
            FUN_004071C0(&self->Third);
            return;
        }
        if (offset > 0x4000) {
            offset = 0x4000;
        }
        FUN_00407150(&self->Third, (int)offset);
    }
    FUN_004071C0(&self->Third);
}

