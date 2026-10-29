// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Each offset
//   and constant reconfirmed numerically from the disassembly; YRpp
//   consulted for names only.
//
// Translation unit: three independent HouseClass leaves.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4F9750   HouseClass::GetWeedStoragePercentage  (__thiscall)
//   FUNCTION: GAMEMD 0x4FCDC0   HouseClass::ForceEnd                  (__thiscall)
//   FUNCTION: GAMEMD 0x504740   HouseClass::EnsurePlanningPathExists  (__thiscall)
//   GLOBAL:   GAMEMD 0x008871E0 RulesClass*  (RulesGlobalPtr)
//   GLOBAL:   GAMEMD 0x00A8ED84 int          (Unsorted::CurrentFrame)
//   GLOBAL:   GAMEMD 0x007E1748 float 0.0f   (FCOMP comparand)
//   GLOBAL:   GAMEMD 0x007E2800 double 0.0   (empty-store percentage)
//   FUNCTION: GAMEMD 0x6C9650   StorageClass::GetTotalAmount  (callee, reloc)
//   FUNCTION: GAMEMD 0x4FC9E0   HouseClass::Win               (callee, reloc)
//   FUNCTION: GAMEMD 0x763810   WaypointPathClass::ctor       (callee, reloc)

#include "house_class_misc_methods.h"

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x4F9750  (__thiscall)
//
// Weed-store fill ratio. If the total stored weed amount is exactly 0, the
// percentage is 0.0; otherwise it is amount / Rules->WeedStorageAmount, where
// the divisor is loaded as an int (FIDIV).
//   LEA ESI,[ECX+0x314] -> &OwnedWeed; GetTotalAmount(); FCOMP 0.0f;
//   if (==0) FLD 0.0 / else GetTotalAmount() FIDIV [Rules+0x17D0].
// ---------------------------------------------------------------------------
double HouseClass::GetWeedStoragePercentage()
{
    if (this->OwnedWeed.GetTotalAmount() == 0.0f)
        return 0.0;
    return this->OwnedWeed.GetTotalAmount() / RulesGlobalPtr->WeedStorageAmount;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x4FCDC0  (__thiscall)
//
// If neither the loser nor winner flag is set, declare this house the winner
// (Win(false)); otherwise stamp the end-of-game frame once.
//   if (!IsLoser && !IsWinner) { Win(false); return; }
//   if (BorrowedTime.StartTime == -1) BorrowedTime.StartTime = CurrentFrame;
// ---------------------------------------------------------------------------
void HouseClass::ForceEnd()
{
    if (!this->IsLoser && !this->IsWinner)
    {
        this->Win(false);
        return;
    }

    if (this->BorrowedTime.StartTime == -1)
        this->BorrowedTime.StartTime = CurrentFrame;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x504740  (__thiscall)
//
// Lazily allocate the planning WaypointPath in slot `index`, returning it.
//   if (PlanningPaths[index] == 0)
//       PlanningPaths[index] = new WaypointPathClass(index);
//   return PlanningPaths[index];
// ---------------------------------------------------------------------------
WaypointPathClass* HouseClass::EnsurePlanningPathExists(int index)
{
    WaypointPathClass* path = this->PlanningPaths[index];
    if (path == 0)
        path = this->PlanningPaths[index] = new WaypointPathClass(index);
    return path;
}
