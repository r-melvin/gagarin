// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5F5F00 / 0x5F6B60 /
//   0x5F6B90 via the local Ghidra disassembly. Offsets and vtable slots
//   confirmed numerically (see the header).
//
// ObjectClass height/level leaves. Functions ordered ascending by retail
// address.

#include "object_class_level_methods.h"

// FUNCTION: GAMEMD 0x5F5F00  ObjectClass::GetCellLevel (__thiscall)
// The cell's own terrain level, raised by a bridge deck when the object is on
// one. Retail materialises the bridge bonus with the VC6 borrow idiom
// (`NEG CL; SBB ECX,ECX; AND ECX,4`), which is what `OnBridge ? 4 : 0` emits.
int ObjectClass::GetCellLevel() const
{
    CellClass* cell = static_cast<const ObjectLevelVtablePrefix*>(
        PrimaryVTable())->GetCell(this);
    return cell->Level + (OnBridge ? 4 : 0);
}

// FUNCTION: GAMEMD 0x5F6B60  ObjectClass::IsOnFloor (__thiscall)
// An off-map object is neither on the floor nor in the air.
bool ObjectClass::IsOnFloor() const
{
    if (IsOnMap) {
        if (static_cast<const ObjectLevelVtablePrefix*>(
                PrimaryVTable())->GetHeight(this) < FlightLevel * 2)
            return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5F6B90  ObjectClass::IsInAir (__thiscall)
// The exact complement of IsOnFloor above the same boundary — retail differs
// from it by a single flipped condition code (JGE vs JL).
bool ObjectClass::IsInAir() const
{
    if (IsOnMap) {
        if (static_cast<const ObjectLevelVtablePrefix*>(
                PrimaryVTable())->GetHeight(this) >= FlightLevel * 2)
            return true;
    }
    return false;
}
