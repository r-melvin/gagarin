// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4C2BD0  EBolt::SetOwner (__thiscall)

#include "ebolt_class_methods.h"

// FUNCTION: GAMEMD 0x4C2BD0  (__thiscall)
// Latch the firing unit and its weapon slot, but only when the candidate owner
// is a live, non-limbo UnitClass (WhatAmI() == AbstractType::Unit).
void EBolt::SetOwner(EBoltOwner* pOwner, int idxWeapon)
{
    if (pOwner)
    {
        if (pOwner->WhatAmI() == 1 && pOwner->IsAlive && !pOwner->InLimbo)
        {
            Owner = pOwner;
            WeaponSlot = idxWeapon;
        }
    }
}
