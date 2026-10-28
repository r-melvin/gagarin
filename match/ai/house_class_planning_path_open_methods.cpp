// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x5090F0.

#include "house_class_planning_path_open_methods.h"

// FUNCTION: GAMEMD 0x5090F0
//
// True when the currently selected planning path (if the selection is a valid
// slot) is still shorter than the rules limit and has no current waypoint set.
bool HouseClass::CanExtendSelectedPlanningPath()
{
    if (this->SelectedPathIndex < 0 || this->SelectedPathIndex >= 12) {
        return false;
    }
    WaypointPathClass* path = this->PlanningPaths[this->SelectedPathIndex];
    return path->Waypoints.Count < DAT_008871E0->unknown_090
        && path->CurrentWaypointIndex == -1;
}
