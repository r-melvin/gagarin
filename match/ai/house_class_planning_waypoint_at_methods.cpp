// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x5023B0.

#include "house_class_planning_waypoint_at_methods.h"

// FUNCTION: GAMEMD 0x5023B0
//
// Find the planning waypoint sitting on `cell`: walk the twelve planning
// paths (allocating any slot that is still empty, exactly as
// GetPlanningWaypointProperties 0x502460 does) and return the first node
// whose coordinate, reduced to a cell, equals the argument; null if none.
//
// Two phrasings carry the match. The outer loop is a `do`/`while` on an
// explicit index: retail keeps `i` in a spill slot, walks the slot pointer in
// EBX and exits through `CMP ESI,0xC; JGE end; JMP top` rather than a
// bottom-tested `JL`, which a plain `for` never produces. The compare builds
// a CellStruct temporary first (both `CDQ; AND EDX,0xFF; ADD; SAR 8` runs
// before either 16-bit compare, with the node parked in ESI); testing X and
// then Y straight off the node interleaves them and drops the node into ECX.
WaypointClass* HouseClass::GetPlanningWaypointAt(const CellStruct* cell)
{
    int i = 0;
    do {
        if (this->PlanningPaths[i] == 0) {
            this->PlanningPaths[i] = new WaypointPathClass(i);
        }
        for (int j = 0; j < this->PlanningPaths[i]->WaypointCount; j++) {
            WaypointClass* wp = this->PlanningPaths[i]->GetWaypoint(j);
            CellStruct c;
            c.X = (short)(wp->X / 256);
            c.Y = (short)(wp->Y / 256);
            if (c.X == cell->X && c.Y == cell->Y) {
                return wp;
            }
        }
        i++;
    } while (i < 12);
    return 0;
}
