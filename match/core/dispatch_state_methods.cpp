// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4025B0, 0x402600 and
//   0x402650.

#include "dispatch_state_methods.h"

// FUNCTION: GAMEMD 0x402440
//
// The 0x4025B0 body with a value stored at +0x0C before the first dispatch and
// bit 3 raised after the last. The store lands between the dispatch-table load
// and the call, which is scheduling; the source order is what it looks like.
// Written out longhand rather than shared, per the family rule.
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

    *(volatile int*)&this->Flags |= 8;
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
        // Volatile even though the encoding it produces is the same narrowed
        // `OR AL,0x1`: without it the value lingers in EAX and VC6 reuses that
        // register for the following dispatch-table load, where retail takes
        // EDX.
        *(volatile int*)&this->Flags |= 1;
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
        // Both flag updates are volatile. Plain, VC6 hoists the dispatch-table
        // load between the clear and its store and picks its own registers;
        // volatile pins each read-modify-write as its own load/modify/store
        // pair, which is what retail has. The differing widths are *not*
        // selected here - the clear comes out `AND ECX,0xFFFFFFFE` and the set
        // `OR AL,0x4` from the same spelling, because they land in different
        // registers and only the EAX form has a byte opcode.
        *(volatile int*)&this->Flags &= ~1;

        DISPATCH_004025B0(this, 0x14);

        *(volatile int*)&this->Flags |= 4;
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

        // Both volatile, same as the sibling. Plain, VC6 folds the pair into
        // one load with `AND AL,0xFB; OR AL,0x1` between it and a single
        // store; retail keeps two load/modify/store pairs, and the widths
        // (`AND AL,0xFB` then `OR ECX,0x1`) again fall out of the registers.
        *(volatile int*)&this->Flags &= ~4;
        *(volatile int*)&this->Flags |= 1;
    }

    DISPATCH_004025B0(this, 0x2C);
}
