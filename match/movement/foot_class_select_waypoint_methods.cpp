// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the address below.
//   PlanningPathIdx +0x520, WaypointNearbyAccessibleCellDelta +0x524, WaypointCell +0x528
//   and WaypointIndex +0x686 are pinned in foot_class.h.

#include "../_layout/foot_class.h"
#include "../_layout/house_class.h"
#include "waypoint_path_class_methods.h"

#include "../_layout/player_ptr_00a83d4c.h"

// FUNCTION: GAMEMD 0x4DC810
// Selects waypoint `waypointIndex` of the local player's planning path `pathIdx` and
// remembers the cell it lies in; -1 clears the selection. The nearby-cell delta is reset.
void FootClass::FUN_004DC810(int pathIdx, signed char waypointIndex)
{
    CellStruct cell;
    if (pathIdx != -1) {
        PlanningPathIdx = pathIdx;
        WaypointIndex = waypointIndex;
        WaypointClass* waypoint = DAT_00A83D4C->PlanningPaths[pathIdx]->GetWaypoint(waypointIndex);
        cell.X = (short)(waypoint->X / 256);
        cell.Y = (short)(waypoint->Y / 256);
        WaypointCell = cell;
    } else {
        cell.X = 0;
        cell.Y = 0;
        PlanningPathIdx = -1;
        WaypointIndex = 0;
        WaypointCell = cell;
    }
    cell.X = 0;
    cell.Y = 0;
    WaypointNearbyAccessibleCellDelta = cell;
}
