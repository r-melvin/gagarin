// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x473750.

#include "target_snapshot_ctor_methods.h"

// FUNCTION: GAMEMD 0x473750
//
// Take a snapshot of a target. A null source leaves the snapshot in its cleared
// state — hence the early return before any of the source is read.
//
// PARTIAL: 83.0% by instruction comparison (44/53). Retail copies both
// 16-bit units at +0x14/+0x16 with one 32-bit load/store; this body preserves
// that width. Remaining instruction differences include prologue scheduling;
// complete byte identity is not established.
//
// Getting here needed the switch body duplicated. Written with 1, 6 and 0xF
// sharing one case body, VC6 emits a single call through slot +0x84 while retail
// has two — it tail-duplicates the body into the fall-through path so that path
// needs no jump. Splitting 0xF into its own case with its own copy, and sending
// the default past the shared tail with a goto, reproduces both call sites:
// 28.3% to 77.4%.
//
// The kind test is a switch, not a chain of comparisons: retail walks it with
// `DEC EAX; JZ` then `SUB EAX,5; JZ` then `SUB EAX,9; JNZ`, which is VC6's
// successive-subtract form for a small switch on 1, 6 and 0xF. Written as
// `kind == 1 || kind == 6` it would compare against each value instead.
Snapshot_00473750* Snapshot_00473750::Ctor(Owner_00473750* owner)
{
    int zero = 0;

    this->At_04 = zero;
    this->At_08 = zero;
    this->Kind = zero;
    this->At_14.A = (short)zero;
    this->At_14.B = (short)zero;
    this->At_18 = zero;
    this->At_1C = -1;
    this->Vptr = VTBL_007E4C04;

    if (owner == 0) {
        return this;
    }

    int kind = (owner->*owner->Vtbl->At_2C)();
    this->Kind = kind;

    Sub_00473750* sub;
    switch (kind) {
    case 1:
    case 6:
        sub = (owner->*owner->Vtbl->At_84)();
        break;
    case 0xF:
        sub = (owner->*owner->Vtbl->At_84)();
        break;
    default:
        goto after_kind;
    }
    this->At_10 = (sub->*sub->Vtbl->At_40)();
after_kind:

    this->At_1C = owner->Holder->Detail->At_B8;
    this->At_18 = owner->At_6C;

    void* scratch;
    Pair16_00473750* result = (owner->*owner->Vtbl->At_1B8)(&scratch);
    this->At_14 = *result;

    return this;
}
