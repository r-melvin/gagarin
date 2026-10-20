// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Bodies and
//   member offsets derived directly from the disassembly; signatures
//   cross-checked against YRpp ObjectClass.h (consult-only, no LICENSE).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x5F5B4C   ObjectClass::ReplaceTag          (__thiscall)
//   FUNCTION: GAMEMD 0x5F5B50   ObjectClass::AttachTrigger       (__thiscall)
//   FUNCTION: GAMEMD 0x5F5C80   ObjectClass::SetHealthPercentage (__thiscall)
//   FUNCTION: GAMEMD 0x5F5CD0   ObjectClass::IsRedHP             (__thiscall)
//   GLOBAL:   GAMEMD 0x008871E0 RulesClass::Instance  (RulesClass*)
//   LIBRARY:  GAMEMD 0x007C5F00 __ftol  (CRT float->long; reloc-normalised)

#include "object_class_methods.h"

// FUNCTION: GAMEMD 0x5F5B4C  (__thiscall)
// ReplaceTag shares AttachTrigger's body byte-for-byte: the retail entry at
// 0x5F5B4C is four `NOP` alignment bytes that fall through into the single
// shared body at 0x5F5B50 (verified: 0x5F5B4C = `90 90 90 90`, then the
// AttachTrigger instructions). YRpp types it `void`, but the emitted code sets
// AL and `RET 4` exactly as AttachTrigger does, so the source is identical.
//
// Detach any currently-attached tag (decrementing its ref-count) and, if a new
// tag is supplied, attach it (incrementing its ref-count); returns whether a
// tag is now attached.
bool ObjectAccessors::ReplaceTag(ObjTag* pTag)
{
    if (this->AttachedTag)
    {
        --((ObjTag*)this->AttachedTag)->RefCount;
        this->AttachedTag = 0;
    }
    if (pTag)
    {
        this->AttachedTag = pTag;
        ++pTag->RefCount;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5F5B50  (__thiscall)
// See ReplaceTag: identical logic.
bool ObjectAccessors::AttachTrigger(ObjTag* pTag)
{
    if (this->AttachedTag)
    {
        --((ObjTag*)this->AttachedTag)->RefCount;
        this->AttachedTag = 0;
    }
    if (pTag)
    {
        this->AttachedTag = pTag;
        ++pTag->RefCount;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5F5C80  (__thiscall)
// Set Health from a fraction of full Strength. percentage<=0 zeroes Health;
// otherwise Health = (int)(GetType()->Strength * percentage), floored to a
// minimum of 1 so a positive percentage never reads as dead.
void ObjectAccessors::SetHealthPercentage(double percentage)
{
    if (percentage > 0.0)
    {
        this->Health =
            (int)((*(ObjGetTypeFunc*)(*(char**)this + 0x88))(this)->Strength * percentage);
        if (this->Health == 0)
            this->Health = 1;
    }
    else
    {
        this->Health = 0;
    }
}

// FUNCTION: GAMEMD 0x5F5CD0  (__thiscall)
// True when the object is in the "red" health band: its health fraction
// (Health / GetType()->Strength) is at or below Rules->ConditionRed and it is
// still alive (Health > 0).
bool ObjectAccessors::IsRedHP() const
{
    return (double)this->Health
                 / (double)((*(ObjGetTypeFunc*)(*(char**)this + 0x88))(this)->Strength)
               <= RulesClassInstance->ConditionRed
           && this->Health > 0;
}
