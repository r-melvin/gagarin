// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x502460.

#include "house_class_planning_methods.h"

// FUNCTION: GAMEMD 0x502460
//
// Locate a planning waypoint: walk the twelve planning paths (allocating any
// slot that is still empty, exactly as EnsurePlanningPathExists does) and
// search each path's node list for `wpt` by pointer identity.  On a hit the
// path slot and node index are written out and true is returned; otherwise the
// outputs are set to -1 / 0 and false is returned.
//
// The path pointer is re-read from this->PlanningPaths[i] around every
// GetWaypoint call (the call could reallocate it), which is what leaves the
// `MOV ECX,[ESI]` reloads in the inner loop.
bool HouseClass::GetPlanningWaypointProperties(WaypointClass* wpt, int* idxPath,
                                               unsigned char* idxWP)
{
    for (int i = 0; i < 12; i++) {
        if (this->PlanningPaths[i] == 0) {
            this->PlanningPaths[i] = new WaypointPathClass(i);
        }
        for (int j = 0; j < this->PlanningPaths[i]->Waypoints.Count; j++) {
            if (this->PlanningPaths[i]->GetWaypoint(j) == wpt) {
                *idxPath = i;
                *idxWP = (unsigned char)j;
                return true;
            }
        }
    }
    *idxPath = -1;
    *idxWP = 0;
    return false;
}
