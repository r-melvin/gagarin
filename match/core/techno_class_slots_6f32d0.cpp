// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// TechnoClass bodies for primary-table (0x7F4960) slots 25, 186, 180 and 102
// (0x6F32D0..0x6F4A3E). Slot numbers come from the RTTI-located table; names
// are placeholders (techno_class.h).
#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/tag_class.h"

// GLOBAL: GAMEMD 0xA83D4C
extern HouseClass* CurrentPlayer;
// GLOBAL: GAMEMD 0xA8E7AC
extern int DAT_00A8E7AC;
// GLOBAL: GAMEMD 0xB0EA50
extern CellStruct DAT_00B0EA50;

// FUNCTION: GAMEMD 0x6F32D0
// Alive, out of limbo, in the playfield, not of kind 6, discovered by the
// current player, of a selectable type, and owned by the current player.
bool TechnoClass::vf_25()
{
    return Health > 0 && !InLimbo && IsInPlayfield && vf_11() != 6
        && DiscoveredByCurrentPlayer && vf_33()->Selectable
        && Owner->IsControlledByCurrentPlayer();
}

// FUNCTION: GAMEMD 0x6F3820
// -1, 0 or 1 for another techno, by this type's NavalTargeting mode and the
// other type's Underwater, SpeedType and two other flags. -1 when the other
// object is missing or not a techno.
int TechnoClass::vf_186(TechnoClass* other)
{
    if (other == 0 || !other->Flags.IsTechno) {
        return -1;
    }
    bool underwater = other->vf_33()->Underwater;
    bool flag_D97 = other->vf_33()->bools_D94[0xD97 - 0xD94];
    bool speed3 = other->vf_33()->SpeedType == 3;
    bool unnatural = other->vf_33()->Unnatural;

    switch (vf_33()->NavalTargeting) {
    case 0:
        if (underwater && other->CloakState != 0) {
            return -1;
        }
        break;
    case 1:
        return underwater != 0;
    case 2:
        return underwater ? 0 : -1;
    case 3:
        if (flag_D97 || unnatural) {
            return 1;
        }
        break;
    case 4:
        if (!speed3 && !flag_D97) {
            return 1;
        }
        break;
    case 5:
        return 0;
    case 6:
        return -1;
    case 7:
        return 0;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6F3950
int TechnoClass::vf_180()
{
    return vf_33()->Crewed != 0;
}

// FUNCTION: GAMEMD 0x6F4960
// Mark this object discovered by a house. Returns false when it already was
// or the base refuses; a computer house's discovery can switch a mission 14
// object to mission 15, and the current player's fires tag event 4 and flags
// the owner's power and radar for a recheck.
bool TechnoClass::vf_102(HouseClass* house)
{
    if (house == CurrentPlayer) {
        if (DiscoveredByCurrentPlayer) {
            return false;
        }
    } else {
        if (DiscoveredByComputer) {
            return false;
        }
        DiscoveredByComputer = true;
    }
    if (!ObjectClass::vf_102(house)) {
        return false;
    }
    if (!house->IsControlledByHuman() && vf_97() == 14) {
        vf_122(15, false);
    }
    if (house == CurrentPlayer) {
        DiscoveredByCurrentPlayer = true;
        Owner->RecheckPower = true;
        Owner->RecheckRadar = true;
        if (!IsOwnedByCurrentPlayer) {
            if (!DAT_00A8E7AC && AttachedTag) {
                AttachedTag->FUN_006E53A0(4, this, DAT_00B0EA50, false, 0);
            }
            Owner->DiscoveredByPlayer = true;
        }
    } else {
        DiscoveredByComputer = true;
    }
    return true;
}
