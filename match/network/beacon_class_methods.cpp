// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm at 0x4308B0).
//   Names cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4308B0  BeaconClass::VisibleToPlayer  (__thiscall)

#include "beacon_class_methods.h"

// FUNCTION: GAMEMD 0x4308B0  (__thiscall)
// Visible iff the beacon's bit-0 flag is set, the local player is allied with
// the beacon's owning house (by index), that house is allied back with the
// player, and the house's +0x1F5 flag is clear. Each link short-circuits to a
// false return; the trailing flag is reloaded through the Array global because
// the intervening alliance call may alias it.
bool BeaconClass::VisibleToPlayer() const
{
    if (this->Bitfield & 1) {
        if (HouseClass_CurrentPlayer->IsAlliedWith(this->HouseID)) {
            if (HouseClass_ArrayItems[this->HouseID]->IsAlliedWith(HouseClass_CurrentPlayer)) {
                if (HouseClass_ArrayItems[this->HouseID]->field_1F5 == 0)
                    return true;
            }
        }
    }
    return false;
}
