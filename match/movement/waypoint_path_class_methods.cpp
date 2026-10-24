// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe (Ghidra disasm). Names cross-checked
//   against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x763980  WaypointPathClass::GetWaypoint      (__thiscall)
//   FUNCTION: GAMEMD 0x763BA0  WaypointPathClass::GetWaypointAfter (__thiscall)

#include "waypoint_path_class_methods.h"

// FUNCTION: GAMEMD 0x763980  (__thiscall)
// Bounds-checked element accessor: return &Waypoints[idx], or null when idx is
// out of [0, Count). The element address is `Items + idx*0xC`.
WaypointClass* WaypointPathClass::GetWaypoint(int idx) const
{
    if (idx >= 0 && idx < Waypoints.Count)
        return &Waypoints.Items[idx];
    return 0;
}

// FUNCTION: GAMEMD 0x763BA0  (__thiscall)
// Given a node pointer, return the node that follows it in the path. The index
// is recovered via the vector's GetItemIndex virtual (slot 0x14); if the next
// index would run off the end and a CurrentWaypointIndex is set (!= -1), wrap to
// CurrentWaypointIndex. Returns null when the resulting index is out of range.
WaypointClass* WaypointPathClass::GetWaypointAfter(WaypointClass* pWaypoint) const
{
    int index = Waypoints.Slot5(pWaypoint) + 1;
    if (CurrentWaypointIndex != -1 && index == Waypoints.Count)
        index = CurrentWaypointIndex;
    if (index >= 0 && index < Waypoints.Count)
        return &Waypoints.Items[index];
    return 0;
}
