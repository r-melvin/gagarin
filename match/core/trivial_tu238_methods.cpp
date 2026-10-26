// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Four TechnoTypeClass member bodies, independently checked at their entries.
// This retained filename is provisional grouping, not attested original TU ownership.
#include "../_layout/techno_type_class.h"
#include "../_layout/rules_class.h"

// GLOBAL: GAMEMD 0xA8B238
extern int DAT_00A8B238;

// FUNCTION: GAMEMD 0x711E90
bool TechnoTypeClass::vf_41()
{
    if (Weapon[0].WeaponType == 0 || PreventAttackMove != 0) {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x711EC0
int TechnoTypeClass::vf_28()
{
    if (bools_C8C[13] != 0) {
        if (DAT_00A8B238 == 0) {
            return OwnerFlags;
        }
        return 0x7FFFFFFF;
    }
    return OwnerFlags;
}

// FUNCTION: GAMEMD 0x712120
int TechnoTypeClass::vf_45()
{
    return RulesInstance->unknown_16CC;
}

// FUNCTION: GAMEMD 0x717800
int TechnoTypeClass::vf_47()
{
    if (FlightLevel == -1) {
        return RulesInstance->unknown_7B4;
    }
    return FlightLevel;
}
