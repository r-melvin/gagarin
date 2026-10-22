// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp (every
//   offset reconfirmed against the user's binary in factory_class_methods.h).
//
// Translation unit: FactoryClass production accessors.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4C9C60   FactoryClass::HasProgressChanged  (__thiscall)
//   FUNCTION: GAMEMD 0x4CA120   FactoryClass::GetProgress         (__thiscall)
//   FUNCTION: GAMEMD 0x4CA130   FactoryClass::IsDone              (__thiscall)
//   FUNCTION: GAMEMD 0x4CA6B0   FactoryClass::IsQueued            (__thiscall)

#include "factory_class_methods.h"

// FUNCTION: GAMEMD 0x4C9C60  (__thiscall)
// Read IsDifferent (this+0x5D), clear it, return the prior value.
//   MOV AL,[ECX+0x5D]; MOV byte[ECX+0x5D],0; RET
bool FactoryClass::HasProgressChanged()
{
    bool changed = this->IsDifferent;
    this->IsDifferent = false;
    return changed;
}

// FUNCTION: GAMEMD 0x4CA120  (__thiscall)
// Return Production.Value (this+0x24).  MOV EAX,[ECX+0x24]; RET
int FactoryClass::GetProgress() const
{
    return this->Production.Value;
}

// FUNCTION: GAMEMD 0x4CA130  (__thiscall)
// Done when progress is complete (Production.Value == 54) and there is either a
// produced Object or a SpecialItem queued.
//   if (Object       && Production.Value == 54) return true;
//   if (SpecialItem != -1 && Production.Value == 54) return true;
//   return false;
bool FactoryClass::IsDone() const
{
    if (this->Object && this->Production.Value == 54)
        return true;
    if (this->SpecialItem != -1 && this->Production.Value == 54)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x4CA6B0  (__thiscall)
// Linear search of QueuedObjects for pType.  RET 4.
bool FactoryClass::IsQueued(TechnoTypeClass* pType) const
{
    for (int i = 0; i < this->QueuedObjects.Count; ++i) {
        if (pType == this->QueuedObjects.Items[i])
            return true;
    }
    return false;
}
