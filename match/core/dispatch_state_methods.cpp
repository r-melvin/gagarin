// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at 0x4025B0, 0x402600 and
//   0x402650.

#include "dispatch_state_methods.h"

// FUNCTION: GAMEMD 0x402440
//
// The 0x4025B0 body with a value stored at +0x0C before the first dispatch and
// bit 3 raised after the last. The store lands between the dispatch-table load
// and the call, which is scheduling; the source order is what it looks like.
// Written out longhand rather than shared, per the family rule. Flags is
// declared volatile (shared with the mixer thread; see the header), which
// gives retail's separate load/modify/store around the dispatches.
void __fastcall Obj_004025B0::FUN_00402440(int value)
{
    this->Recorded = value;

    DISPATCH_004025B0(this, 0x28);

    if (*(unsigned char*)&this->Flags & 5) {
        DISPATCH_004025B0(this, 0x10);
    }

    DISPATCH_004025B0(this, 0x2C);

    Handler_004025B0 handler = this->Handler;

    if (handler) {
        handler(this);
    }

    this->Pending = 0;

    this->Flags |= 8;
}

// FUNCTION: GAMEMD 0x402720
//
// The two refusals are HRESULT-shaped constants and each has its own epilogue,
// so they are separate early returns rather than a shared tail.
long Obj_004025B0::FUN_00402720()
{
    if (*(unsigned char*)&this->Flags & 5) {
        return 0x800F0000;
    }

    if (this->Pending == 0) {
        return 0x80070000;
    }

    FUN_00401080(this->Part);
    FUN_00402220(this);

    DISPATCH_004025B0(this, 0x28);

    long hr = DISPATCH_RESULT_004025B0(this, 0x0C);

    if (hr == 0) {
        this->Flags |= 1;
    }

    DISPATCH_004025B0(this, 0x2C);

    return hr;
}

// FUNCTION: GAMEMD 0x402550
//
// The 0x4025B0 body followed by the object's own teardown. Written out longhand
// rather than calling the sibling: retail inlines nothing here, it simply
// repeats the same sequence and then continues, so sharing would fold the two
// into one call the binary does not have.
void Obj_004025B0::FUN_00402550()
{
    DISPATCH_004025B0(this, 0x28);

    if (*(unsigned char*)&this->Flags & 5) {
        DISPATCH_004025B0(this, 0x10);
    }

    DISPATCH_004025B0(this, 0x2C);

    Handler_004025B0 handler = this->Handler;

    if (handler) {
        handler(this);
    }

    this->Pending = 0;

    FUN_004028B0(this);

    DISPATCH_004025B0(this, 0x08);

    FUN_007C8B3D(this);
}

// FUNCTION: GAMEMD 0x4025B0
//
// The only one of the three that continues past slot +0x2C, so its +0x2C call
// is an ordinary `CALL` rather than the siblings' tail `JMP`. The optional
// handler at +0xBC runs afterwards and the pending word is cleared last.
void Obj_004025B0::FUN_004025B0()
{
    DISPATCH_004025B0(this, 0x28);

    if (*(unsigned char*)&this->Flags & 5) {
        DISPATCH_004025B0(this, 0x10);
    }

    DISPATCH_004025B0(this, 0x2C);

    Handler_004025B0 handler = this->Handler;

    if (handler) {
        handler(this);
    }

    this->Pending = 0;
}

// FUNCTION: GAMEMD 0x402600
//
// Clear bit 0, run slot +0x14, set bit 2. The two flag updates are separate
// load/store pairs in retail, so they are separate statements here.
void Obj_004025B0::FUN_00402600()
{
    DISPATCH_004025B0(this, 0x28);

    if (*(unsigned char*)&this->Flags & 1) {
        this->Flags &= ~1;

        DISPATCH_004025B0(this, 0x14);

        this->Flags |= 4;
    }

    DISPATCH_004025B0(this, 0x2C);
}

// FUNCTION: GAMEMD 0x402650
//
// The inverse transition: run slot +0x18 first, then clear bit 2 and set bit 0.
void Obj_004025B0::FUN_00402650()
{
    DISPATCH_004025B0(this, 0x28);

    if (*(unsigned char*)&this->Flags & 4) {
        DISPATCH_004025B0(this, 0x18);

        // Two load/modify/store pairs: Flags is volatile (see the header).
        this->Flags &= ~4;
        this->Flags |= 1;
    }

    DISPATCH_004025B0(this, 0x2C);
}
