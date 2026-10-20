// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Bytes matched against retail gamemd.exe v1.001 at 0x4109C0.

#include "deregistering_dtor_methods.h"

// FUNCTION: GAMEMD 0x4109C0
//
// Destructor: install this class's four vtables, remove the object from the
// global list, then run the base destructor.
//
// The lookup takes the address of a local copy of `this` rather than `this`
// itself — retail allocates a dword with `PUSH ECX`, stores `this` into it and
// passes its address. That is what RA1's `ID(T const &)` looks like once T is a
// pointer type.
//
// The removal has two comparisons against the count, one before the decrement and
// one after, because the guard and the shift loop's own pre-test are separate.
// The decremented count is stored whichever way the second comparison goes —
// retail schedules that store between the compare and the branch.
void Obj_004109C0::Dtor()
{
    this->Vptr0 = VTBL_007E2000;
    this->Vptr1 = VTBL_007E1FE4;
    this->Vptr2 = VTBL_007E1FDC;
    this->Vptr3 = VTBL_007E1FD4;

    Obj_004109C0* self = this;
    int index = (DAT_00A8E968.*DAT_00A8E968.Vptr->ID)(&self);

    if (index != -1 && index < DAT_00A8E968.Count) {
        DAT_00A8E968.Count = DAT_00A8E968.Count - 1;
        for (int i = index; i < DAT_00A8E968.Count; i++) {
            DAT_00A8E968.Items[i] = DAT_00A8E968.Items[i + 1];
        }
    }

    this->BaseDtor();
}
