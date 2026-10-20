// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes diffed against retail gamemd.exe v1.001 at 0x451750.

#include "side_slot_dispatch_methods.h"

// FUNCTION: GAMEMD 0x451750
//
// Pick one of three byte flags out of the owner's record for `index` — the
// second when `a`, the third when `b`, the first otherwise — and hand it on
// only if it is set. Retail still tests the pointer for null even though every
// arm produces the address of a member, so the selection is written through a
// pointer variable rather than folded into the call.
void Obj_00451750::FUN_00451750(int index, bool a, bool b, int extra)
{
    char* slot;

    if (a) {
        slot = &this->Owner->Slots[index].At_10;
    } else if (b) {
        slot = &this->Owner->Slots[index].At_20;
    } else {
        slot = &this->Owner->Slots[index].At_00;
    }

    if (slot != 0 && *slot != 0) {
        this->FUN_00451890(slot, index, a, b, extra);
    }
}
