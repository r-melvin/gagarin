// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the seven addresses below.

#include "small_misc38_methods.h"

// FUNCTION: GAMEMD 0x41C3F0
void FUN_0041C3F0(Triple_0041C3F0* self)
{
    if (self->X == 0.0 && self->Y == 0.0 && self->Z == 0.0) {
        self->X = 100.0;
    }
}

// FUNCTION: GAMEMD 0x426750
//
// The delegate is stored before it is checked, so a null one is still recorded.
// The empty case is the trailing block: retail's `JZ` at 0x42675F jumps forward
// past everything, so the guard is written positively.
// The second call re-reads the member rather than reusing the argument, which
// is what retail's `MOV ECX,[ESI+0x84]` at 0x42676A is.
bool AnimFile_00426750::vf_1(Delegate_00426750* delegate)
{
    Delegate = delegate;

    if (delegate != 0) {
        if (!delegate->vt_018()) {
            Delegate->vt_01C(1);
            Primed = 1;
        }

        return FUN_004267F0();
    }

    return false;
}

// Teardown in three steps: retire the delegate through its slot +0x34 and drop
// the primed flag, destroy the sub-object at +0xE0C through its own deleting
// destructor, and free the buffer at +0xE10. The delegate pointer is cleared
// unconditionally, before the sub-object work, while each of the other two
// pointers is cleared inside its own guard.

// FUNCTION: GAMEMD 0x426790
void AnimFile_00426750::vf_2()
{
    if (Primed) {
        Delegate->vt_034();

        Primed = 0;
    }

    SubObject_00426790* sub = Sub;

    Delegate = 0;

    if (sub) {
        sub->vt_000(1);

        Sub = 0;
    }

    void* buffer = Buffer;

    if (buffer) {
        FUN_007C8B3D(buffer);

        Buffer = 0;
    }

    Retired = 0;
}

// The destructor: the 0x426790 teardown, expanded in place. Defined inline so /Ob2 expands it into the
// scalar deleting destructor 0x4272A0 (compiler output beside the constructor). Retail also keeps an
// unreferenced out-of-line copy at 0x4266D0 that one translation unit cannot emit alongside the inlined
// one, so that address is not reproduced.
inline AnimFile_00426750::~AnimFile_00426750()
{
    if (Primed) {
        Delegate->vt_034();

        Primed = 0;
    }

    SubObject_00426790* sub = Sub;

    Delegate = 0;

    if (sub) {
        sub->vt_000(1);

        Sub = 0;
    }

    void* buffer = Buffer;

    if (buffer) {
        FUN_007C8B3D(buffer);

        Buffer = 0;
    }

    Retired = 0;
}

// FUNCTION: GAMEMD 0x43A670
//
// The slot is cleared on every pass, including the ones where it was already
// null - retail's `MOV [EAX+ESI*4-4],0` sits after the increment, which is the
// strength-reduced form of an unconditional `Items[i] = 0`, not something
// inside the guard.
void FUN_0043A670(Obj_0043A670* self)
{
    int count = self->Count;

    for (int i = 0; i < count; i++) {
        Item_0043A670* item = self->Items[i];

        if (item) {
            item->vt_020(1);
        }

        self->Items[i] = 0;
    }

    self->Sub.vt_00C();
}

// FUNCTION: GAMEMD 0x43A6B0
//
// The 0x43A670 release with two values recorded afterwards. Written out
// longhand rather than sharing a helper, per the family rule.
void Obj_0043A670::FUN_0043A6B0(int first, int second)
{
    int count = Count;

    for (int i = 0; i < count; i++) {
        Item_0043A670* item = Items[i];

        if (item) {
            item->vt_020(1);
        }

        Items[i] = 0;
    }

    Sub.vt_00C();

    field_1C = first;
    field_20 = second;
}



//
// Constructor: the base's vtable goes in first, then the delegate, flags and the
// 256 three-byte slots are cleared, the two trailing words are set to -1, and
// this class's vtable replaces the base's.
// FUNCTION: GAMEMD 0x426670
AnimFile_00426750::AnimFile_00426750()
    : Delegate(0), Retired(0), Primed(0), Sub(0), Buffer(0), Mark1(-1), Mark2(-1)
{
}

// SYNTHETIC: GAMEMD 0x427270 -- Animate::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x4272A0 -- AnimFile::`scalar deleting destructor'

// FUNCTION: GAMEMD 0x426E00
//
// Fails while the file is not open. Moving to a frame other than the current
// one records it, seeks the delegate to that frame's position and reads the
// frame's bytes (header, packed length and data) into the buffer; the read must
// return the full size.
bool AnimFile_00426750::FUN_00426E00(int frame)
{
    if (Retired) {
        if (Mark2 != frame) {
            Mark2 = frame;

            Delegate->vt_028((frame << 16) + 0xB00, 0);

            int size = Frames[frame].unknown_02 + Frames[frame].Value * 2 + 8;

            if (Delegate->vt_024(Buffer, size) != size) {
                return false;
            }
        }

        return true;
    }

    return false;
}
