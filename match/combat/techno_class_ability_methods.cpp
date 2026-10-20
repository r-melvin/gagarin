// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x70D0D0.

#include "techno_class_ability_methods.h"

// FUNCTION: GAMEMD 0x70D0D0
//
// Does this object currently enjoy the given veteran/elite ability? Nothing
// below veteran rank has any. A veteran has the ability when its type grants it
// at the veteran tier; an elite has it when the type grants it at either tier
// (elite is a superset). The type is fetched through the GetTechnoType virtual
// only once a rank test has passed.
bool Techno_0070D0D0::HasAbility(int ability)
{
    VeterancyStruct* vet = &this->Veterancy;

    if (FUN_0074FF90(vet) || FUN_00750010(vet)) {
        TechnoType_0070D0D0* type = (this->*(*(Vtbl_0070D0D0**)this)->At_084)();

        if (FUN_0074FF90(vet) && type->VeteranAbilities[ability]) {
            return true;
        }
        if (FUN_00750010(vet)
            && (type->VeteranAbilities[ability] || type->EliteAbilities[ability])) {
            return true;
        }
    }
    return false;
}
