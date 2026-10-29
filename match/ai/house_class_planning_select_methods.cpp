// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001; planning-path offsets
//   (SelectedPathIndex +0x20C, PlanningPaths +0x210) read at 0x502290/0x5090A0.

#include "house_class_planning_select_methods.h"

// FUNCTION: GAMEMD 0x502290
//
// Make the waypoint at the same cell as `wp` the current waypoint of the
// selected planning path (allocating the slot if it is still empty).
bool HouseClass::SelectPlanningWaypoint(const WaypointClass* wp)
{
    int i = this->SelectedPathIndex;
    if (this->PlanningPaths[i] == 0) {
        this->PlanningPaths[i] = new WaypointPathClass(i);
    }
    return this->PlanningPaths[this->SelectedPathIndex]->SelectWaypointAt(wp);
}

// FUNCTION: GAMEMD 0x5090A0
//
// Index of the first planning path that has no waypoints yet, or -1 when all
// twelve are in use.
int HouseClass::FindEmptyPlanningPath()
{
    for (int i = 0; i < 12; i++) {
        WaypointPathClass* path = this->PlanningPaths[i];
        if (path == 0) {
            path = new WaypointPathClass();
        }
        if (path->Waypoints.Count == 0) {
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x5022F0
//
// True when no planning path other than the selected one has a waypoint on
// `cell`. Walks all twelve paths (allocating empty slots as the other
// planning walkers do), comparing each node reduced to a cell.
bool HouseClass::IsPlanningCellFreeOfOtherPaths(const CellStruct* cell)
{
    for (int i = 0; i < 12; i++) {
        if (this->PlanningPaths[i] == 0) {
            this->PlanningPaths[i] = new WaypointPathClass(i);
        }
        for (int j = 0; j < this->PlanningPaths[i]->Waypoints.Count; j++) {
            WaypointClass* wp = this->PlanningPaths[i]->GetWaypoint(j);
            CellStruct c;
            c.X = (short)(wp->X / 256);
            c.Y = (short)(wp->Y / 256);
            if (c.X == cell->X && c.Y == cell->Y && i != this->SelectedPathIndex) {
                return false;
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x502160
//
// Append `wp` to the selected planning path unless a different planning path
// already has a waypoint on the same cell.
void HouseClass::AddPlanningWaypoint(const WaypointClass* wp)
{
    CellStruct cell;
    cell.X = (short)(wp->X / 256);
    cell.Y = (short)(wp->Y / 256);
    for (int i = 0; i < 12; i++) {
        if (this->PlanningPaths[i] == 0) {
            this->PlanningPaths[i] = new WaypointPathClass(i);
        }
        for (int j = 0; j < this->PlanningPaths[i]->Waypoints.Count; j++) {
            WaypointClass* node = this->PlanningPaths[i]->GetWaypoint(j);
            CellStruct c;
            c.X = (short)(node->X / 256);
            c.Y = (short)(node->Y / 256);
            if (c.X == cell.X && c.Y == cell.Y && i != this->SelectedPathIndex) {
                return;
            }
        }
    }
    int sel = this->SelectedPathIndex;
    if (this->PlanningPaths[sel] == 0) {
        this->PlanningPaths[sel] = new WaypointPathClass(sel);
    }
    this->PlanningPaths[this->SelectedPathIndex]->AddWaypoint(wp);
}
