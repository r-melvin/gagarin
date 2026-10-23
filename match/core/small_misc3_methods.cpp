// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc3_methods.h"

// FUNCTION: GAMEMD 0x402170
// Dispatch slot 8, then release the object. Freeing `this` is what makes this a
// destroy helper rather than a destructor.
void Obj_00402100::FUN_00402170()
{
    DISPATCH_CALL(this, 8);

    FUN_007C8B3D(this);
}

// FUNCTION: GAMEMD 0x407480
ListNode* FUN_00407480(ListNode* self)
{
    ListNode* node = self->Next;

    return (node != node->Owner) ? node : 0;
}

// FUNCTION: GAMEMD 0x432C10
void Obj_00432C00::FUN_00432C10(int value)
{
    if (unknown_20) {
        unknown_20->FUN_006C9D30(value);
    }
}

// FUNCTION: GAMEMD 0x432C30
// The pause flag is narrowed to a byte before the push, so the argument is a
// bool widened at the call rather than a full int.
void Obj_00432C00::FUN_00432C30(int pause)
{
    BinkPause(Bink, pause & 0xFF);
}

// FUNCTION: GAMEMD 0x433020
// A zero return from BinkWait means the frame is not ready; the flag records
// that we stalled.
void Obj_00432C00::FUN_00433020()
{
    if (BinkWait(Bink) == 0) {
        unknown_2D = 1;
    }
}

