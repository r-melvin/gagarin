// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x6F1870 / 0x6F18A0 /
//   0x6F18E0 (Ghidra disasm).  Structure cross-checked against YRpp
//   (each offset
//   and call target reconfirmed against the user's binary).
//
// Translation unit: TeamTypeClass waypoint/group accessors.
//   FUNCTION: GAMEMD 0x6F1870   TeamTypeClass::GetGroup             (__thiscall)
//   FUNCTION: GAMEMD 0x6F18A0   TeamTypeClass::GetWaypoint          (__thiscall)
//   FUNCTION: GAMEMD 0x6F18E0   TeamTypeClass::GetTransportWaypoint (__thiscall)
//   GLOBAL:   GAMEMD 0xA8B230   WaypointLocator pointer
//   GLOBAL:   GAMEMD 0xB0E9C8   DefaultWaypointCell (CellStruct)
//
// Match status (reccmp diff_retail.py vs retail, reloc-normalised): see report.

#include "team_type_class_methods.h"

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6F1870  TeamTypeClass::GetGroup (__thiscall)
//
// Return the team's group number.  -2 ("none") and any non-(-1) value are
// returned verbatim; the -1 sentinel means "inherit the task force's group",
// so when a TaskForce is set its group (+0x98) is returned instead.
// ---------------------------------------------------------------------------
int TeamTypeClass::GetGroup() const
{
    int group = this->Group;
    if (group != -2 && group == -1 && this->TaskForce != 0) {
        group = this->TaskForce->Group;
    }
    return group;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6F18A0  TeamTypeClass::GetWaypoint (__thiscall)
//
// Fill *buffer with the team's rally waypoint cell.  An unset waypoint (-1)
// yields the default (zero) cell; otherwise the global waypoint locator maps the
// index to a CellStruct.  Returns buffer.
// ---------------------------------------------------------------------------
CellStruct* TeamTypeClass::GetWaypoint(CellStruct* buffer) const
{
    CellStruct local;

    if (this->Waypoint == -1) {
        *buffer = DefaultWaypointCell;
        return buffer;
    }
    *buffer = *WaypointLocatorPtr->GetCoords(&local, this->Waypoint);
    return buffer;
}

// ---------------------------------------------------------------------------
// FUNCTION: GAMEMD 0x6F18E0  TeamTypeClass::GetTransportWaypoint (__thiscall)
//
// As GetWaypoint, for the team's transport-loadout waypoint (TransportWaypoint).
// ---------------------------------------------------------------------------
CellStruct* TeamTypeClass::GetTransportWaypoint(CellStruct* buffer) const
{
    CellStruct local;

    if (this->TransportWaypoint == -1) {
        *buffer = DefaultWaypointCell;
        return buffer;
    }
    *buffer = *WaypointLocatorPtr->GetCoords(&local, this->TransportWaypoint);
    return buffer;
}
