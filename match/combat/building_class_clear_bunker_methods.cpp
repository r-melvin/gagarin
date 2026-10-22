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
void Building_00459470::ClearBunker()
{
    DestroyNthAnim(10);
    DestroyNthAnim(11);

    if (BunkerLinkedItem != 0)
    {
        if (RulesInstance->BunkerSound != -1)
        {
            Coord_00459470 coords = Location;
            VocClass_PlayAt_00459470(RulesInstance->BunkerSound, &coords, 0);
        }

        const char* name;
        int damaged;

        if (GetHealthPercentage() <= RulesInstance->ConditionYellow)
        {
            damaged = 1;
            name = Type->Anims[12].NameDamaged;
        }
        else
        {
            damaged = 0;
            name = Type->Anims[12].NameNormal;
        }

        if (name != 0 && *name != 0)
            PlayAnim(name, 12, damaged, 0, 0);

        if (GetHealthPercentage() <= RulesInstance->ConditionYellow)
        {
            damaged = 1;
            name = Type->Anims[13].NameDamaged;
        }
        else
        {
            damaged = 0;
            name = Type->Anims[13].NameNormal;
        }

        if (name != 0 && *name != 0)
            PlayAnim(name, 13, damaged, 0, 0);

        (this->*static_cast<Vtbl_00459470*>(
            PrimaryVTable())->At_274)(3);
        BunkerLinkedItem->BunkerLinkedItem = 0;
        BunkerLinkedItem = 0;
        unknown_718 = 0;
        (this->*static_cast<Vtbl_00459470*>(
            PrimaryVTable())->At_1E8)(5, 0);
    }
}
