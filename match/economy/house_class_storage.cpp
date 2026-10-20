// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm).
//   Names cross-checked against YRpp HouseClass.h (consult-only, no LICENSE;
//   each offset/address reconfirmed against the user's binary).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x42F380   BaseClass::FailedToPlaceNode      (__thiscall)
//   FUNCTION: GAMEMD 0x4F6E70   HouseClass::GetStoragePercentage  (__thiscall)
//   GLOBAL:   GAMEMD 0x7E2800   double 0.0   (empty-store return constant)
//   LIBRARY:  GAMEMD 0x7C5F00   __ftol       (CRT float->long; excluded)

#include "house_class_storage.h"

// FUNCTION: GAMEMD 0x42F380   BaseClass::FailedToPlaceNode  (__thiscall)
// `this` is unused; the body operates only on Node. When Node is null EAX
// already holds it (== 0), so the null path returns 0 with no extra zeroing.
int BaseClass::FailedToPlaceNode(BaseNodeClass* Node)
{
    if (Node == NULL) {
        return 0;
    }
    return ++Node->Attempts;
}

// FUNCTION: GAMEMD 0x4F6E70   HouseClass::GetStoragePercentage  (__thiscall)
// (int)OwnedTiberium.GetTotalAmount() == 0  -> ftol + TEST EAX (empty store
// returns 0.0); otherwise the float total / int TotalStorage emits FIDIV.
double HouseClass::GetStoragePercentage()
{
    if ((int)this->OwnedTiberium.GetTotalAmount() == 0) {
        return 0.0;
    }
    return this->OwnedTiberium.GetTotalAmount() / this->TotalStorage;
}
