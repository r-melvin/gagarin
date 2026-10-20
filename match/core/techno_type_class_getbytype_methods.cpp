// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). The switch
//   jump-table @0x48DD10 and discriminator byte-table @0x48DD24 were decoded to
//   recover the (AbstractType -> array) mapping; cross-checked against YRpp
//   TechnoTypeClass.h / GeneralDefinitions.h (consult-only, reconfirmed here).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x48DCD0  TechnoTypeClass::GetByTypeAndIndex (__fastcall)

#include "techno_type_class_getbytype_methods.h"

// FUNCTION: GAMEMD 0x48DCD0  (__fastcall)
// Dispatch on AbstractType (in ECX) and index (in EDX). Retail compiles this as
// a dense byte-indexed jump table: LEA EAX,[abs-1]; CMP EAX,0x27; JA default;
// then a 40-entry byte-table selects one of five jump targets.
//   abs 1 / 40       -> UnitTypeClass::Array
//   abs 6 / 7        -> BuildingTypeClass::Array
//   abs 15 / 16      -> InfantryTypeClass::Array
//   abs 2 / 3        -> AircraftTypeClass::Array
// The case blocks are written in retail physical-emit order (Unit, Building,
// Infantry, Aircraft) so the jump table and block addresses line up byte-exact.
TechnoTypeClass* __fastcall TechnoTypeClass::GetByTypeAndIndex(AbstractType abs, int index)
{
    switch (abs)
    {
    case AbstractType_Unit:
    case AbstractType_UnitType:
        return UnitTypeClass_ArrayItems[index];

    case AbstractType_Building:
    case AbstractType_BuildingType:
        return BuildingTypeClass_ArrayItems[index];

    case AbstractType_Infantry:
    case AbstractType_InfantryType:
        return InfantryTypeClass_ArrayItems[index];

    case AbstractType_Aircraft:
    case AbstractType_AircraftType:
        return AircraftTypeClass_ArrayItems[index];

    default:
        return 0;
    }
}
