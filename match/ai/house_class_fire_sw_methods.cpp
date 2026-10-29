// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4FAE50.

#include "house_class_fire_sw_methods.h"

// FUNCTION: GAMEMD 0x4FAE50
//
// Fire this house's superweapon `index` at `cell`. A PostClick weapon first
// copies its partner's stored map cell, then the weapon is click-fired (the
// "is the local player" flag decides the fluff), the partner is de-readied and
// its pre-click animation stopped, and every house is told about the launch.
bool HouseClass::Fire_SW(int index, const CellStruct& cell)
{
    SuperClass* sw = this->SupersItems[index];
    SuperClass* partner = 0;
    if (sw->Type->PostClick) {
        partner = this->SupersItems[sw->Type->PreDependent];
        if (partner != 0) {
            sw->ChronoMapCoords = partner->ChronoMapCoords;
        }
    }
    sw->ClickFire(this == CurrentPlayer, cell);
    if (sw->Type->PostClick && partner != 0) {
        partner->SetReadiness(false);
        partner->StopPreclickAnim(this == CurrentPlayer);
    }
    for (int i = HouseArrayCount - 1; i >= 0; i--) {
        HouseClass* house = HouseArrayItems[i];
        if (house != 0) {
            house->FUN_004FAF00(sw, cell);
        }
    }
    return true;
}
