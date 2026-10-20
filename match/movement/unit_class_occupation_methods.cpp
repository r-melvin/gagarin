// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp UnitClass.h / Interfaces.h (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x740E80  UnitClass::APCOpenDoor             (__thiscall)
//   FUNCTION: GAMEMD 0x7441B0  UnitClass::MarkAllOccupationBits   (__thiscall)
//   FUNCTION: GAMEMD 0x744210  UnitClass::UnmarkAllOccupationBits (__thiscall)

#include "unit_class_occupation_methods.h"

// FUNCTION: GAMEMD 0x740E80  (__thiscall)
// If the unit is not in motion (per its locomotor) and the door-pending flag is
// clear, begin the door transition by handing the unit type's door-open angle to
// the unload timer. The locomotor is a COM smart pointer, so the dereference
// carries the inlined NULL-guard that raises E_POINTER.
void UnitClass::APCOpenDoor()
{
    ILocomotionPtr* loco = reinterpret_cast<ILocomotionPtr*>(&this->Locomotor);
    if (!(*loco)->Is_Moving() && !this->unknown_bool_6AF)
    {
        reinterpret_cast<DoorTimer*>(&this->UnloadTimer)->Start(
            *reinterpret_cast<double*>(reinterpret_cast<char*>(this->Type) + 0x3C8));
    }
}

// FUNCTION: GAMEMD 0x7441B0  (__thiscall)
// Set the "Units" occupation bit (0x20) for the cell the coordinate maps to.
// When the coordinate sits at or below the cell floor and the cell is a bridge
// cell, the bit goes into the alternate (on-bridge) occupation set instead.
void UnitClass::MarkAllOccupationBits(CoordStruct const& coords)
{
    OccCellClass* cell = MapInstance->GetTargetCell(coords);
    if (MapInstance->GetCellFloorHeight(coords) + BridgeCellHeight <= coords.Z
        && (cell->Flags & 0x100))
    {
        cell->AltOccupationFlags |= 0x20;
        return;
    }
    cell->OccupationFlags |= 0x20;
}

// FUNCTION: GAMEMD 0x744210  (__thiscall)
// Clear the "Units" occupation bit (0x20) the mirror of MarkAllOccupationBits;
// unlike the mark path the unmark always clears the alternate set on the
// at-or-below-floor branch with no bridge-flag test.
void UnitClass::UnmarkAllOccupationBits(CoordStruct const& coords)
{
    OccCellClass* cell = MapInstance->GetTargetCell(coords);
    if (MapInstance->GetCellFloorHeight(coords) + BridgeCellHeight <= coords.Z)
    {
        cell->AltOccupationFlags &= ~0x20;
        return;
    }
    cell->OccupationFlags &= ~0x20;
}
