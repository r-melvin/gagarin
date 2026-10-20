// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5F6CD0 (name from
//   the YRpp method map, consult-only).

#include "object_class_crushable_methods.h"

// FUNCTION: GAMEMD 0x5F6CD0  ObjectClass::IsCrushable (__thiscall, ret 0x4)
//
// May `crusher` run this object over? Two routes say yes. An omni-crusher
// flattens any techno (other than a building) whose type is not
// omni-crush-resistant. Otherwise the object's type must be crushable and the
// object itself not flagged uncrushable. Both routes also require the crusher's
// house not to be allied with the object and the +0x160 predicate to be false.
bool ObjectClass::IsCrushable(ObjectClass* crusher)
{
    if (crusher != 0
        && (crusher->*static_cast<const Vtbl_005F6CD0*>(
                crusher->_vtable_IPersistStream)->GetTechnoType)()->OmniCrusher
        && IsTechno_005F6CD0(this)
        && !(this->*static_cast<const Vtbl_005F6CD0*>(
                _vtable_IPersistStream)->GetTechnoType)()->OmniCrushResistant
        && (this->*static_cast<const Vtbl_005F6CD0*>(
                _vtable_IPersistStream)->WhatAmI)() != 6
        && !CrushTechno(crusher)->Owner->IsAlliedWith(this)
        && !(this->*static_cast<const Vtbl_005F6CD0*>(
                _vtable_IPersistStream)->At_160)()) {
        return true;
    }

    if ((this->*static_cast<const Vtbl_005F6CD0*>(
                _vtable_IPersistStream)->GetType)()->Crushable
        && IsTechno_005F6CD0(this)
        && !CrushTechno(this)->Uncrushable
        && !CrushTechno(crusher)->Owner->IsAlliedWith(this)
        && !(this->*static_cast<const Vtbl_005F6CD0*>(
                _vtable_IPersistStream)->At_160)()) {
        return true;
    }

    return false;
}
