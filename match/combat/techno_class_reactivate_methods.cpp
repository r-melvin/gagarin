// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x70FBE0.

#include "techno_class_reactivate_methods.h"

// FUNCTION: GAMEMD 0x70FBE0
//
// Reset through the +0x3D0 virtual first. If this object is a FootClass
// (AbstractFlags bit 2), power its locomotor back on through the COM slot at
// +0x58 — the null check and E_POINTER report are the smart-pointer dereference
// inlined. Then, if it was deactivated and its type names an ActivateSound,
// play that sound at the object's own location; finally clear Deactivated.
//
// Two phrasings matter. The Deactivated test and the sound-index test are one
// `&&` condition: split into nested `if`s VC6 loads the GetTechnoType() vtable
// pointer into EAX where retail has EDX (and shifts the coordinate-copy
// registers with it) — a pure register-naming diff at 76.5%. And the vtable
// pointer is re-read at every virtual call rather than held in a local;
// GetTechnoType() is called twice (once to test, once to fetch), as retail does.
// These casts express the binary's zero-offset AbstractClass/ObjectClass views.
// The shared spine models public inheritance; these casts do not establish
// any additional hierarchy.
void TechnoReactivate::Reactivate()
{
    (this->*(*(ReactVtbl**)this)->At_3D0)();

    if (this != 0 && (((AbstractClass*)(void*)this)->Flags.IsFoot))
    {
        FootClass* foot = (FootClass*)this;
        if (foot->Locomotor == 0)
            FUN_007DC720(0x80004003);
        LOCO_CALL0((ILocomotion*)foot->Locomotor, 0x58);
    }

    if (this->Deactivated
        && (this->*(*(ReactVtbl**)this)->GetTechnoType)()->ActivateSound != -1)
    {
        CoordStruct crd = ((ObjectClass*)(void*)this)->Location;
        VocClass_PlayAt((this->*(*(ReactVtbl**)this)->GetTechnoType)()->ActivateSound, &crd, 0);
    }

    this->Deactivated = 0;
}
