// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the seven addresses below.

#include "small_misc38_methods.h"

// FUNCTION: GAMEMD 0x41C3F0
void __fastcall FUN_0041C3F0(Triple_0041C3F0* self)
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
bool AnimFile_00426750::FUN_00426750(Delegate_00426750* delegate)
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

// FUNCTION: GAMEMD 0x4266D0
//
// The destructor. Same three-step teardown as 0x426790 with the vtable
// bracketing a destructor does: this class's goes in before any member work and
// the base's replaces it at the end. The primed flag is read *before* the first
// vtable store, which is why it is held in a local.
//
// Written out longhand rather than calling 0x426790, per the family rule -
// retail repeats the body rather than calling it.
void AnimFile_00426750::FUN_004266D0()
{
    char primed = Primed;

    Vtable = &VT_007E3584;

    if (primed) {
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

    Vtable = &VT_007E35A8;
}

// FUNCTION: GAMEMD 0x426790
//
// Teardown in three steps: retire the delegate through its slot +0x34 and drop
// the primed flag, destroy the sub-object at +0xE0C through its own deleting
// destructor, and free the buffer at +0xE10. The delegate pointer is cleared
// unconditionally, before the sub-object work, while each of the other two
// pointers is cleared inside its own guard.
void AnimFile_00426750::FUN_00426790()
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
void __fastcall FUN_0043A670(Obj_0043A670* self)
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

// FUNCTION: GAMEMD 0x473A30
//
// The CCFileClass(const char*) constructor (0x4739F0, in
// match/platform/ccfile_class.cpp) with the argument routed through 0x7B5440
// first.
// +0x68 is written twice - once with the other field initialisers and again
// after the mapping call - and retail keeps both.
//
// MATCHED 100% (19/19). The historic 63.2% residual was two misplaced
// instructions: retail loads the argument into ECX *before* the three field
// stores and puts the second +0x68 write *after* the result is pushed, and we
// did the opposite in both cases. The cause was the two `*(volatile int*)&`
// casts on the +0x68 writes. They were added on the assumption that cl would
// otherwise treat the first write as dead; it does not - the intervening
// `FUN_007B5440` call may alias the member, so both stores survive as plain
// assignments - and the volatile lvalues were what pinned the ECX load and the
// second store on the wrong side of their neighbours. Deleting both qualifiers
// is worth 63.2% -> 100%; nothing else in the body changed. Under the old
// spelling, hoisting the argument into a named local and marking the other two
// initialisers volatile as well both left it at 63.2%.
Obj_004739F0* Obj_004739F0::FUN_00473A30(int value)
{
    FUN_0047AA30(this);
    Member.FUN_0043AD00(0, 0);

    Reset64 = 0;
    Vtable  = &VT_007E16B0;

    Reset68 = 0;

    int mapped = FUN_007B5440(value);

    Reset68 = 0;

    FUN_0047AE10(mapped);

    return this;
}
