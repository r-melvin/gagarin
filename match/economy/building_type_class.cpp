// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp
//   (each offset/address reconfirmed against the user's binary).
//
// Translation unit: BuildingTypeClass foundation/build-up accessors.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x45EC90   BuildingTypeClass::GetFoundationWidth   (__thiscall)
//   FUNCTION: GAMEMD 0x45ECA0   BuildingTypeClass::GetFoundationHeight  (__thiscall)
//   FUNCTION: GAMEMD 0x465AF0   BuildingTypeClass::ClearBuildUp         (__thiscall)
//   FUNCTION: GAMEMD 0x465D40   BuildingTypeClass::IsVehicle            (__thiscall)
//   GLOBAL:   GAMEMD 0x8192B8   FoundationWidth   (int[] indexed by Foundation)
//   GLOBAL:   GAMEMD 0x819310   FoundationHeight  (int[] indexed by Foundation)
//   LIBRARY:  GAMEMD 0x7C8B3D   scalar operator delete (CRT; excluded from recovery)

#include "../_layout/building_type_class_layout.h"
#include <new.h>
#include "foundation_dimensions.h"

GG_STATIC_ASSERT(offsetof(BuildingTypeClass, Foundation) == 0xEF0);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, Buildup) == 0xE00);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, BuildupLoaded) == 0xE04);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, bools_1570) == 0x1570);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass, bools_1760) + 2 == 0x1762);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, UndeploysInto) == 0x408);

// Foundation enum dimensions, in cells. Native storage is writable .data.
// GLOBAL: GAMEMD 0x8192B8
int FoundationWidth[22] = {
    1, 2, 1, 2, 2, 3, 3, 3, 4, 3, 1, 3, 4, 1, 1, 2, 2, 5, 4, 3, 6, 0
};
// GLOBAL: GAMEMD 0x819310
int FoundationHeight[22] = {
    1, 1, 2, 2, 3, 2, 3, 5, 2, 3, 3, 1, 3, 4, 5, 6, 5, 3, 4, 4, 4, 0
};

// LIBRARY: GAMEMD 0x7C8B3D — scalar operator delete; also called by the
// compiler-generated deleting destructor at 0x4D03A0.

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x45EC90  (__thiscall)
// Foundation width = FoundationWidth[this->Foundation].
// ---------------------------------------------------------------------------
int BuildingTypeClass::GetFoundationWidth() const
{
    return FoundationWidth[this->Foundation];
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x45ECA0  (__thiscall)
// Foundation height, +1 for the bib row when requested and present.
// ---------------------------------------------------------------------------
int BuildingTypeClass::GetFoundationHeight(bool bIncludeBib) const
{
    return FoundationHeight[this->Foundation]
        + ((bIncludeBib && this->bools_1570[0]) ? 1 : 0);
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x465AF0  (__thiscall)
// Release the cached build-up animation image if we own it.
// ---------------------------------------------------------------------------
void BuildingTypeClass::ClearBuildUp()
{
    if (this->bools_1760[2] && this->Buildup)
    {
        ::operator delete(this->Buildup);
        this->Buildup = 0;
        this->BuildupLoaded = false;
    }
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x465D40  (__thiscall)
// A "vehicle" building: undeploys into a unit and occupies a 1x1 foundation.
// ---------------------------------------------------------------------------
bool BuildingTypeClass::IsVehicle() const
{
    return this->UndeploysInto != 0
        && FoundationWidth[this->Foundation] == 1
        && FoundationHeight[this->Foundation] == 1;
}
