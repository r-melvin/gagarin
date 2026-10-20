// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp TechnoClass.h / HouseClass.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6339B0  TechnoClass::GetControllingHouse (__thiscall)

#include "techno_class_house.h"

HouseClass* HouseClass::CurrentPlayer = NULL;

// FUNCTION: GAMEMD 0x6339B0  (__thiscall)
// Returns the controlling house's ArrayIndex. The Owner's index by default, but
// substituted with CurrentPlayer's index when the Owner is the local human
// player. Retail loads Owner (+0x21C), pre-computes Owner->ArrayIndex (+0x30)
// into ESI, then short-circuits IsControlledByCurrentPlayer() && CurrentPlayer.
int TechnoClass::GetControllingHouse() const
{
    HouseClass* owner = this->Owner;
    int id = owner->ArrayIndex;
    if (owner->IsControlledByCurrentPlayer() && HouseClass::CurrentPlayer != NULL)
        return HouseClass::CurrentPlayer->ArrayIndex;
    return id;
}
