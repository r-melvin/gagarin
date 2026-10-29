// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x459470.

#include "building_class_clear_bunker_methods.h"

// FUNCTION: GAMEMD 0x459470  BuildingClass::ClearBunker (__thiscall)
//
// Tear the bunker link down: the two garrison animations are destroyed, the
// bunker-exit sound plays at the building's own coordinates when the rules
// name one, the two "bunker cleared" animations play in their healthy or
// damaged spelling according to the building's health ratio, and then both
// back-links are cleared and the building is sent through its mission slot.
void BuildingClass::ClearBunker()
{
    DestroyNthAnim(10);
    DestroyNthAnim(11);

    if (BunkerLinkedItem != 0)
    {
        if (RulesInstance->BunkerWallsDownSound != -1)
        {
            Coord_00459470 coords = Location;
            VocClass_PlayAt_00459470(RulesInstance->BunkerWallsDownSound, &coords, 0);
        }

        const char* name;
        int damaged;

        if (GetHealthPercentage() <= RulesInstance->ConditionYellow)
        {
            damaged = 1;
            name = Type->BuildingAnim[12].Damaged;
        }
        else
        {
            damaged = 0;
            name = Type->BuildingAnim[12].Anim;
        }

        if (name != 0 && *name != 0)
            PlayAnim(name, 12, damaged, 0, 0);

        if (GetHealthPercentage() <= RulesInstance->ConditionYellow)
        {
            damaged = 1;
            name = Type->BuildingAnim[13].Damaged;
        }
        else
        {
            damaged = 0;
            name = Type->BuildingAnim[13].Anim;
        }

        if (name != 0 && *name != 0)
            PlayAnim(name, 13, damaged, 0, 0);

        vf_157(3);
        BunkerLinkedItem->BunkerLinkedItem = 0;
        BunkerLinkedItem = 0;
        TankBunkerState = 0;
        vf_122(5, 0);
    }
}
