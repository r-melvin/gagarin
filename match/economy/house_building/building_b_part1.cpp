// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// BuildingClass entries 0x44F5C0..0x4527D0 of the "building-b" cluster (views: building_b_views.h).

#include <new.h>
#include "building_b_views.h"
#include "../../_layout/building_class.h"
#include "../../_layout/house_class.h"

// FUNCTION: GAMEMD 0x44F5C0
bool BuildingClass::vf_40()
{
    if (EMPLockRemaining > 0)
        return false;
    if (vf_161())
        return true;
    if (Type->bools_16A4[0x16B9 - 0x16A4]) {
        if (!Owner->IsControlledByHuman())
            goto refuse;
        if (BuildingBGlobal_00A8B238 == 0)
            goto refuse;
        if (BuildingBGlobal_00A8B320 == 0)
            goto refuse;
        if (MindControlledBy == 0)
            goto allow;
refuse:
        return false;
    }
allow:
    return Type->UndeploysInto != 0;
}

// FUNCTION: GAMEMD 0x44F640
// CAPPED at 26.0% (13 of 50 instructions). Retail lays the equal-to-empty-coordinate path (the vf_18 copy) after
// the non-equal path, entered by a final `je`; cl keeps it first behind `jne` for every spelling tried
// (`==&&` then-block, `!=||` then-block, a `goto`, an if/else with one return).
HBCoord* BuildingBView::vf_45(HBCoord* out, int)
{
    HBCoord tmp;
    BuildingBTypeView* type = Type;
    if (type->CoordEC8.X != BuildingBEmptyCoord.X || type->CoordEC8.Y != BuildingBEmptyCoord.Y
        || type->CoordEC8.Z != BuildingBEmptyCoord.Z) {
        HBCoord loc = Location;
        *out = loc + type->CoordEC8;
    } else {
        *out = *vf_18(&tmp);
    }
    return out;
}

// FUNCTION: GAMEMD 0x4500A0
HBCoord* BuildingBView::vf_41(HBCoord* out)
{
    HBCoord tmp;
    HBCoord c = *vf_18(&tmp);
    *out = c + Type->CoordEBC;
    return out;
}

// FUNCTION: GAMEMD 0x451330
int BuildingBView::vf_180()
{
    if (!NoCrew && Type->unknown_CCD) {
        int rate;
        int side = Owner->SideIndex;
        if (side == 0)
            rate = BuildingBRules->unknown_14F8;
        else if (side == 1)
            rate = BuildingBRules->unknown_14FC;
        else if (side == 2)
            rate = BuildingBRules->unknown_1500;
        else
            return 0;
        if (rate != 0) {
            if (HasBeenCaptured)
                rate += rate;
            int n = Type->vf_46(Owner, 0) / rate;
            if (n < 1)
                return 1;
            if (n > 5)
                return 5;
            return n;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4513D0
int BuildingBView::vf_27()
{
    if (BState && ActuallyPlacedOnMap)
        return Type->vf_39();
    return Type->vf_48();
}

// FUNCTION: GAMEMD 0x452250
int BuildingClass::vf_321()
{
    return 0;
}

// FUNCTION: GAMEMD 0x452630
bool BuildingClass::vf_37()
{
    if (Health == 0)
        return false;
    if (!Type->bools_1570[0x157A - 0x1570])
        return false;
    if (vf_32())
        return false;
    return TechnoClass::vf_37();
}

// FUNCTION: GAMEMD 0x4526F0
// CAPPED at 48.0% (36 of 75 instructions; retail-only: 2 `add eax,imm` computing &Type->field after the load;
// compiled differs in block layout). Retail loads the occupant type once, before the elite branch, and keeps the
// elite/non-elite tests as `mov ecx,[eax+0xE20]; add eax,0xE20; test ecx,ecx`. Variants tried: the plain
// per-branch form kept here, a hoisted `type` local ahead of the branch, a local `elite` bool.
void BuildingBView::vf_254(int a)
{
    if (UpgradeLevel) {
        for (int i = 0; i < UpgradeLevel; i++) {
            if (Upgrades[i] && *Upgrades[i]->Func_7177C0(a))
                return;
        }
    }
    if (vf_256() && FiringOccupantIndex < Occupants.Count) {
        BuildingBOccupantView* occupant = Occupants.Items[FiringOccupantIndex];
        if (occupant->Veterancy.Func_750010()) {
            if (occupant->Type->unknown_E20 == 0)
                occupant->vf_254(0);
        } else {
            if (occupant->Type->unknown_E04 == 0)
                occupant->vf_254(0);
        }
        return;
    }
    Func_70E140(a);
}

// FUNCTION: GAMEMD 0x4527D0
bool BuildingClass::vf_255()
{
    if (Type->bools_C8C[0xCA1 - 0xC8C])
        return true;
    if (UpgradeLevel) {
        for (int i = 0; i < UpgradeLevel; i++) {
            if (Upgrades[i] && Upgrades[i]->bools_C8C[0xCA1 - 0xC8C])
                return true;
        }
    }
    return false;
}
