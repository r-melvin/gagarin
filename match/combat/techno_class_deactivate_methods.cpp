// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x70FC90.

#include "techno_class_deactivate_methods.h"

// FUNCTION: GAMEMD 0x70FC90
//
// Power the object down. When the +0x418 flag is set and the probe agrees,
// an object sitting on this cell that is the probe's own answer means there
// is nothing to do. Otherwise go through the +0x3D0 and +0x150 virtuals, cut a
// FootClass's locomotor through its COM slot +0x5C (smart-pointer null check
// and E_POINTER inlined), play the type's deactivate sound at the object's
// location if it was not already off, and set Deactivated.
void TechnoDeactivate::Deactivate()
{
    if (this->IsTether && this->FUN_0065AD30(0)) {
        TechnoDeactivate* occupant = (this->*(*(DeactVtbl**)this)->GetCell)()->FUN_0047C520();
        if (occupant == (TechnoDeactivate*)this->FUN_0065AD30(0))
            return;
    }

    (this->*(*(DeactVtbl**)this)->At_3D0)();
    (this->*(*(DeactVtbl**)this)->At_150)();

    if (this != 0 && (((AbstractClass*)(void*)this)->Flags.IsFoot))
    {
        FootClass* foot = (FootClass*)this;
        if (foot->Locomotor == 0)
            FUN_007DC720(0x80004003);
        LOCO_CALL0_DEACT((ILocomotion*)foot->Locomotor, 0x5C);
    }

    if (!this->Deactivated
        && (this->*(*(DeactVtbl**)this)->GetTechnoType)()->DeactivateSound != -1)
    {
        CoordStruct crd = ((ObjectClass*)(void*)this)->Location;
        VocClass_PlayAt((this->*(*(DeactVtbl**)this)->GetTechnoType)()->DeactivateSound, &crd, 0);
    }

    this->Deactivated = 1;
}
