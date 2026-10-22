// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at the four addresses below.

#include "small_misc37_methods.h"

// FUNCTION: GAMEMD 0x4023F0
//
// `AND AL,0xFA` is the whole-word `&= ~5` narrowed by VC6 - the load and the
// store are both dwords, only the mask is a byte.
int Obj_004023F0::FUN_004023F0()
{
    // The three fields are volatile (this body runs on the mixer thread; see
    // the header), which keeps the Flags load after the Pending store.
    Pending = 0;
    Flags &= ~5;
    FlagsHigh = 0;

    FUN_00401000(Sub);

    Handler_004023F0 handler = Handler;

    if (handler) {
        return handler(this);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x405580
//
// PARTIAL: both flag writes are ordinary `|= 0x60`. On the detach path VC6
// hoists the owner re-read in between, where retail loads +0xB0 only after the
// flag store lands; the volatile writes that forced that order were removed as
// match steering.
void __fastcall FUN_00405580(Obj_00405580* self)
{
    // Retail tests the flag byte in place (`TEST byte ptr [ESI+0x18],0x20`)
    // rather than loading the word first, which is what the byte-width read
    // gives; `self->Flags & 0x20` on the int emits `MOV EAX,..; TEST AL,0x20`.
    if (*(unsigned char*)&self->Flags & 0x20) {
        return;
    }

    Owner_00405580* owner = self->Owner;

    if (owner && self == owner->Current) {
        FUN_004026A0(owner);

        self->Flags |= 0x60;

        FUN_004026B0(self->Owner);

        return;
    }

    self->Flags |= 0x60;
}

// FUNCTION: GAMEMD 0x406550
//
// Both resets act on the same sub-object, so its address is taken once; the
// second is a tail call, which is what the free-function form gives.
void __fastcall FUN_00406550(Obj_00406550* self)
{
    void* sub = self->Sub;

    FUN_00407150(sub);
    FUN_004071C0(sub);
}
