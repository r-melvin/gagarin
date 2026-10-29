// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Bodies and
//   member offsets derived directly from the disassembly; signatures
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x47C4D0  CellClass::FindObjectOfType (__thiscall)
//   FUNCTION: GAMEMD 0x47C520  CellClass::GetBuilding      (__thiscall)
//   FUNCTION: GAMEMD 0x47C550  CellClass::GetTerrain       (__thiscall)
//   GLOBAL:   GAMEMD 0x00A8E9A0 CellOccupiersValid (byte; reloc-normalised)

#include "cell_class_query_methods.h"

// AbstractType discriminants returned by WhatAmI() (YRpp).
#define ABS_BUILDING 6     // CMP EAX,0x06
#define ABS_TERRAIN  0x24  // CMP EAX,0x24

// Read the occupier's WhatAmI() through its primary vtable slot +0x2C.
// `MOV EAX,[obj]; MOV ECX,obj; CALL [EAX+0x2C]`.
#define WHAT_AM_I(obj) ((*(WhatAmIFunc*)(*(char**)(obj) + 0x2c))(obj))

// FUNCTION: GAMEMD 0x483480  CellClass::RevealCellObjects (__thiscall)
// Walk the ground occupier list and let each object reveal itself (virtual slot
// +0xFC). Nothing is read back, so the loop is a plain forward walk.
void CellClass::RevealCellObjects()
{
    for (ObjectClass* object = (ObjectClass*)FirstObject; object != 0; object = (ObjectClass*)object->NextObject) {
        (*(RevealFunc*)(*(char**)object + 0xFC))(object);
    }
}

// FUNCTION: GAMEMD 0x484F20  CellClass::GetTunnel (__thiscall)
// The tunnel index is a signed short, so both ends are checked: negative means
// "no tunnel here", and the upper bound guards a stale index against the live
// array count.
TunnelClass* CellClass::GetTunnel() const
{
    if (TubeIndex >= 0 && TubeIndex < TunnelArrayCount)
        return TunnelArrayItems[TubeIndex];

    return 0;
}

// FUNCTION: GAMEMD 0x47C4D0  (__thiscall)
// Walk the selected occupier list, returning the first object whose runtime
// AbstractType equals the requested discriminant.
ObjectClass* CellClass::FindObjectOfType(int abs, bool alt) const
{
    if (CellOccupiersValid) {
        ObjectClass* obj = (ObjectClass*)(alt ? this->AltObject : this->FirstObject);
        for (; obj; obj = (ObjectClass*)obj->NextObject) {
            if (WHAT_AM_I(obj) == abs) {
                return obj;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x47C520  (__thiscall)
// First building occupying the cell (ground list only).
BuildingClass* CellClass::GetBuilding() const
{
    if (CellOccupiersValid) {
        for (ObjectClass* obj = (ObjectClass*)this->FirstObject; obj;
             obj = (ObjectClass*)obj->NextObject) {
            if (WHAT_AM_I(obj) == ABS_BUILDING) {
                return (BuildingClass*)obj;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x47C550  (__thiscall)
// First terrain object occupying the cell; `alt` selects the on-bridge list.
TerrainClass* CellClass::GetTerrain(bool alt) const
{
    if (CellOccupiersValid) {
        ObjectClass* obj = (ObjectClass*)(alt ? this->AltObject : this->FirstObject);
        for (; obj; obj = (ObjectClass*)obj->NextObject) {
            if (WHAT_AM_I(obj) == ABS_TERRAIN) {
                return (TerrainClass*)obj;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x47C5A0  CellClass::GetSomeObject (__thiscall, ret 0x8)
// Three-stage lookup: an occupier of AbstractType 2, then whatever
// FindObjectAt turns up, then an occupier of AbstractType 0x24 (terrain).
//
// The two occupier scans are written differently on purpose, because retail
// compiles them differently. The first breaks out and re-tests afterwards —
// retail re-checks the pointer at 0x47C60E even though the break guarantees it
// non-null, which is the merge point of the break and fall-through paths. The
// second returns straight from inside the loop, and retail has no such re-test.
ObjectClass* CellClass::GetSomeObject(int a, int b)
{
    ObjectClass* object = 0;

    if (CellOccupiersValid) {
        for (object = (ObjectClass*)FirstObject; object != 0; object = (ObjectClass*)object->NextObject) {
            if (WHAT_AM_I(object) == 2)
                break;
        }

        if (object != 0)
            return object;
    }

    ObjectClass* found = FindObjectAt(a, b, false);
    if (found != 0)
        return found;

    if (CellOccupiersValid) {
        for (object = (ObjectClass*)FirstObject; object != 0; object = (ObjectClass*)object->NextObject) {
            if (WHAT_AM_I(object) == ABS_TERRAIN)
                return object;
        }
    }

    return 0;
}
