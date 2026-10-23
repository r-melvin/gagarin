// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x44E7B0.
//   LIBRARY: GAMEMD 0x7C5F00  __ftol  (CRT double->long; the (int) cast; reloc)

#include "building_class_power_output_methods.h"

// FUNCTION: GAMEMD 0x44E7B0  BuildingClass::GetPowerOutput (__thiscall)
// Base output is the type's PowerBonus, read before the warp-out test. A
// building being warped out produces nothing. Otherwise the extra bonus is
// added when the instance flag is set, once more per passenger when the type
// is one of the two absorbing kinds and actually has a positive extra bonus,
// and each fitted upgrade's own PowerBonus is added when the building is
// upgraded at all. A positive total is finally scaled by the health ratio;
// anything else, or an unpowered building, reports zero.
int BuildingClass::GetPowerOutput()
{
    int output = this->Type->PowerBonus;

    if (this->vf_117())
        return 0;

    if (this->HasExtraPowerBonus)
        output += this->Type->ExtraPowerBonus;

    // Register naming is sensitive here: the multiply's destination must be
    // the bonus (`MOV EAX,[EAX+0xEE8]` reusing the dying type pointer, then
    // `IMUL EAX,ECX` with the passenger count in ECX). A flat
    // `&& bonus > 0 && n > 0` condition with the product in the body, in any
    // operand order and with or without locals, gives the bonus ECX and the
    // count EAX (93.8%). Splitting the count test into its own nested `if`
    // with the count bound first and the bonus re-read second is what makes
    // the bonus the destination operand.
    BuildingTypeClass* type = this->Type;
    if ((type->bools_16A4[0x16AE - 0x16A4] || type->bools_16A4[0x16AF - 0x16A4]) && type->ExtraPowerBonus > 0)
    {
        int n = this->Passengers.NumPassengers;
        if (n > 0)
        {
            int b = type->ExtraPowerBonus;
            output += b * n;
        }
    }

    if (this->UpgradeLevel)
    {
        for (int i = 0; i < 3; i++)
        {
            if (this->Upgrades[i])
                output += this->Upgrades[i]->PowerBonus;
        }
    }

    if (output > 0 && this->HasPower)
        return (int)(this->GetHealthPercentage() * output);

    return 0;
}
