// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x471C90 (name from the
//   YRpp method map, consult-only).

#include "capture_manager_can_capture_methods.h"

// FUNCTION: GAMEMD 0x471C90
//
// Whether this mind-controller may take `target`. Rejected: no target; a
// target owned by the same house as the controller; a type immune to
// psionics; a building that is bunker-linked; a target already mind
// controlled (either way); an iron-curtained target; a full controller that is
// not the single-slot kind; and a target busy constructing or selling.
//
// The house test is spelled `!(a != b)`: retail evaluates the target's house
// first, keeps it in EBP and compares `CMP EBP,EAX`. A plain `a == b` makes
// VC6 evaluate the right operand first and flips the compare operands; a
// named temporary keeps the order but swaps EBX/EBP between `this` and the
// temporary.
bool CaptureManagerClass::CanCapture(Techno_00471C90* target) const
{
    if (target == 0)
        return false;

    if (!((target->*target->Vtbl->GetOwningHouse)()
          != (((Techno_00471C90*)this->Owner)->*((Techno_00471C90*)this->Owner)->Vtbl->GetOwningHouse)()))
        return false;

    if ((target->*target->Vtbl->GetTechnoType)()->ImmuneToPsionics)
        return false;

    if (target->BunkerLinkedItem != 0) {
        if ((target->*target->Vtbl->WhatAmI)() == 1)
            return false;
    }

    if (target->IsMindControlled())
        return false;

    if (target->MindControlledByHouse != 0)
        return false;

    if ((target->*target->Vtbl->IsIronCurtained)())
        return false;

    if (!this->InfiniteMindControl) {
        if (this->ControlNodes.Count >= this->MaxControlNodes
            && this->MaxControlNodes != 1)
            return false;
    }

    int mission = target->CurrentMission;
    if (mission == 0x13 || mission == 0x12)
        return false;

    return true;
}
