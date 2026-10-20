// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x6F0A70 / 0x6F2040 /
//   0x6F2070 (Ghidra disasm).  Structure cross-checked against YRpp
//   TeamTypeClass.h / TeamClass.h (consult-only, no LICENSE; each offset,
//   global and call target reconfirmed against the user's binary).
//
// Translation unit: TeamTypeClass house/taskforce/instance helpers.
//   FUNCTION: GAMEMD 0x6F0A70   TeamTypeClass::DestroyAllInstances  (__thiscall)
//   FUNCTION: GAMEMD 0x6F2040   TeamTypeClass::ProcessAllTaskforces (static)
//   FUNCTION: GAMEMD 0x6F2070   TeamTypeClass::GetHouse             (__thiscall)
//   GLOBAL:   GAMEMD 0xA8ECA0   TeamTypeClass::Array
//   GLOBAL:   GAMEMD 0x8B40E8   TeamClass::Array
//   CALLEE:   GAMEMD 0x6F1FA0   TeamTypeClass::ProcessTaskForce
//   CALLEE:   GAMEMD 0x510F60   IsCountryIndex / 0x510ED0 FindHouseByCountryIndex

#include "team_type_class_house_methods.h"

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6F0A70  TeamTypeClass::DestroyAllInstances (__thiscall)
//
// Remove every live TeamClass spawned from this TeamTypeClass.  Walks the global
// TeamClass::Array; each team whose Type == this is removed (vtable+0x20, flag 1)
// and the index stepped back so the shifted array slot is re-examined.  Count is
// re-read from the global each pass because the remove call mutates the array.
// ---------------------------------------------------------------------------
void TeamTypeClass::DestroyAllInstances()
{
    for (int i = 0; i < TeamInstanceArray.Count; i++) {
        TeamClass* team = ((TeamClass**)TeamInstanceArray.Items)[i];
        if (this == team->Type) {
            if (team) {
                team->Remove(1);
            }
            i--;
        }
    }
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6F2040  TeamTypeClass::ProcessAllTaskforces (static)
//
// Run one taskforce-processing tick for every TeamTypeClass in the global type
// array.  The per-element call prevents the compiler from hoisting Items/Count,
// so both are re-read from the global on each iteration.
// ---------------------------------------------------------------------------
void TeamTypeClass::ProcessAllTaskforces()
{
    for (int i = 0; i < TeamTypeArray.Count; i++) {
        ((TeamTypeClass**)TeamTypeArray.Items)[i]->ProcessTaskForce();
    }
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6F2070  TeamTypeClass::GetHouse (__thiscall)
//
// Resolve the team's owning house.  A cached Owner pointer is returned verbatim;
// otherwise the team's country index is validated and mapped to a HouseClass*
// (returning null when the index names no real country).
// ---------------------------------------------------------------------------
HouseClass* TeamTypeClass::GetHouse() const
{
    if (this->Owner) {
        return this->Owner;
    }
    if (IsCountryIndex(this->idxHouse)) {
        return FindHouseByCountryIndex(this->idxHouse);
    }
    return 0;
}
