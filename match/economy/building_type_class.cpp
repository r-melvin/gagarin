// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp BuildingTypeClass.h (consult-only, no LICENSE;
//   each offset/address reconfirmed against the user's binary).
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
//   LIBRARY:  GAMEMD 0x7C8B3D   operator delete / free (CRT; excluded from match)

#include "building_type_class.h"

// GLOBAL: GAMEMD 0x8192B8 / 0x819310 — foundation dimension lookup tables,
// indexed by the Foundation enum. Scaled index *4 in the disasm => int[].
extern int FoundationWidth[];   // GLOBAL 0x8192B8
extern int FoundationHeight[];  // GLOBAL 0x819310

// LIBRARY: GAMEMD 0x7C8B3D — CRT operator delete / free (push ptr; call; add esp,4).
extern "C" void __cdecl gamemd_free(void* block);

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
        + ((bIncludeBib && this->Bib) ? 1 : 0);
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x465AF0  (__thiscall)
// Release the cached build-up animation image if we own it.
// ---------------------------------------------------------------------------
void BuildingTypeClass::ClearBuildUp()
{
    if (this->FreeBuildup && this->Buildup)
    {
        gamemd_free(this->Buildup);
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
