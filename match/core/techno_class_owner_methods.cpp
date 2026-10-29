// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp. Each function is
//   ordered ascending by retail address.
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x70F7E0  TechnoClass::TargetingTimerFinished (__thiscall)
//   FUNCTION: GAMEMD 0x70F820  TechnoClass::GetOriginalOwner       (__thiscall)
//   FUNCTION: GAMEMD 0x734270  TechnoClass::ClearSidebarTabObject  (__thiscall)

#include "techno_class_owner_methods.h"

// Sidebar "tab object" globals @ 0x00B0FE5C / 0x00B0FE60. Declared-only so cl
// emits reloc-normalised absolute stores/compares.
extern TechnoClass* SidebarTabObjectA;   // 0x00B0FE5C
extern TechnoClass* SidebarTabObjectB;   // 0x00B0FE60

// FUNCTION: GAMEMD 0x70F7E0  (__thiscall)
// Inlines CDTimerClass::GetTimeLeft on TargetingTimer and reports whether it has
// expired. StartTime == -1 means "not running" -> the stored TimeLeft is the
// remaining value verbatim; otherwise subtract the elapsed frames, clamping the
// remainder at 0. The countdown is finished when the remainder is 0.
//
// The accessor is inlined with TimeLeft read once into a local and a return
// in each arm; the caller's `== 0` is then duplicated into each return, which
// is retail's two long-form tails (`xor ecx,ecx; test eax,eax; setz cl;
// mov al,cl`): one after the live SUB, one shared by the stopped and clamped
// paths.
bool TechnoClass::TargetingTimerFinished() const
{
    return this->TargetingTimer.GetTimeLeft() == 0;
}

// FUNCTION: GAMEMD 0x70F820  (__thiscall)
// The house that originally owned this object. When mind-controlled, the
// controlling unit's CaptureManager remembers the original owner; when held by
// a house's mind-control, OriginallyOwnedByHouse holds it; otherwise the live
// Owner is the original owner.
HouseClass* TechnoClass::GetOriginalOwner() const
{
    if (this->MindControlledBy != NULL)
        return ((CaptureManagerClass*)((TechnoClass*)this->MindControlledBy)->CaptureManager)->GetOriginalOwner(
            const_cast<TechnoClass*>(this));
    if (this->MindControlledByHouse != NULL)
        return (HouseClass*)this->OriginallyOwnedByHouse;
    return this->Owner;
}

