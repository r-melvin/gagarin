// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   WaypointPathClass list editing, read off retail gamemd.exe v1.001
//   (vtable 0x7F6E70). The layout is movement/waypoint_path_class_methods.h.
//   Address index: 0x763AF0 set, 0x763B30 remove, 0x763BE0 clear.

#include <new.h>
#include "waypoint_path_class_methods.h"
#include "../core/vector_class_operations.h"

// FUNCTION: GAMEMD 0x763AF0
// Overwrites the point at an in-range index.
void WaypointPathClass::SetWaypoint(int idx, const WaypointClass* pWaypoint)
{
    if (idx >= 0 && idx < Waypoints.Count) {
        new (&Waypoints.Items[idx]) WaypointClass(*pWaypoint);
    }
}

// FUNCTION: GAMEMD 0x763B30
// Removes the point at an in-range index; the loop point is forgotten when it was that point
// or the last one.
void WaypointPathClass::RemoveWaypoint(int idx)
{
    if (idx >= 0 && idx < Waypoints.Count) {
        if (idx == CurrentWaypointIndex || idx == Waypoints.Count - 1) {
            CurrentWaypointIndex = -1;
        }
        Waypoints.Delete(idx);
    }
}

// FUNCTION: GAMEMD 0x763BE0
// Empties the point list and forgets the loop point.
void WaypointPathClass::ClearWaypoints()
{
    Waypoints.Clear();
    CurrentWaypointIndex = -1;
}
