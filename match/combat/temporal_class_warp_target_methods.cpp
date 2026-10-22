// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x71AE50. Name from
//   YRpp.

#include "temporal_class_warp_target_methods.h"

// FUNCTION: GAMEMD 0x71AE50
//
// Whether a techno may be temporal-warped. No target, a type without the
// +0xD3A flag, or a positive +0x160 virtual all refuse. A unit (WhatAmI == 1)
// whose first radio link is a building (WhatAmI == 6) of a type flagged at
// +0x16BD is refused when that building is the one standing on the unit's
// own cell — i.e. the unit is garrisoned inside it. Everything else warps.
bool TemporalClass_0071AE50::CanWarpTarget(Techno_0071AE50* target)
{
    if (target == 0)
        return false;

    if (!(target->*target->Vtbl->GetTechnoType)()->At_D3A)
        return false;

    if ((target->*target->Vtbl->At_160)())
        return false;

    if ((target->*target->Vtbl->WhatAmI)() == 1) {
        Techno_0071AE50* link = target->FUN_0065AD30(0);
        if (link != 0
            && (link->*link->Vtbl->WhatAmI)() == 6
            && link->Type->At_16BD)
        {
            CoordStruct_0071AE50 crd = target->Location;
            if (MapInstance_0071AE50->GetTargetCell(crd)->GetBuilding() == link)
                return false;
        }
    }

    return true;
}
