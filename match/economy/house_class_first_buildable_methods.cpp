// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5051E0.

#include "house_class_first_buildable_methods.h"

// FUNCTION: GAMEMD 0x5051E0
//
// First type in the list this house may build: owner bit for its parent
// country, required and forbidden house masks, AI base-planning side. A type
// carrying a super weapon is skipped when supers are allowed, unless it is a
// construction-yard type or its super cannot be disabled from the shell.
TechnoType_005051E0* House_005051E0::FirstBuildableFromArray(TypeVector_005051E0* items)
{
    unsigned int owner = 1 << HouseType_FindIndexOfName_005051E0(Type->ParentCountry);

    for (int i = 0; i < items->Count; i++) {
        TechnoType_005051E0* type = items->Items[i];
        if ((type->OwnerFlags & owner)
            && (type->RequiredHouses == 0xFFFFFFFF
                || (type->RequiredHouses & (1 << Type->ArrayIndex)))
            && (type->ForbiddenHouses == 0xFFFFFFFF
                || !(type->ForbiddenHouses & (1 << Type->ArrayIndex)))
            && (type->AIBasePlanningSide == -1
                || type->AIBasePlanningSide == Type->ArrayIndex2)) {
            if (DAT_00A8B263) {
                return type;
            }
            if (type->SuperWeapon == -1) {
                return type;
            }
            for (int j = 0; j < DAT_008871E0->BuildConstCount; j++) {
                if (DAT_008871E0->BuildConstItems[j] == type) {
                    return type;
                }
            }
            if (!SupersItems[type->SuperWeapon]->Type->DisableableFromShell) {
                return type;
            }
        }
    }
    return 0;
}
