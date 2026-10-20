// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x689D30.

#include "scenario_class_start_points_methods.h"

// FUNCTION: GAMEMD 0x689D30
//
// Read the scenario header's start position, map size and starting-point
// counts, then the numbered waypoints that hold the multiplayer start
// cells. Every field keeps its current value as the INI default, and the
// waypoint table is cleared first so an absent entry reads back as zero.
//
// PARTIAL (8.0% by position; 99 of 100 instructions, two kinds apart). The
// -1 preset, the clear loop, all six header reads, the per-waypoint key
// built with sprintf and the hidden-pointer waypoint read with the current
// entry as its default are all in retail's order and form, and the
// increment is spelled `next = i + 1; ... i = next;` so it comes out as the
// LEA-plus-move pair. The residual is two materialised constants: retail
// holds the clear loop's two zeros in separate registers filled among the
// prologue pushes (where cl uses one, filled late) and tests the starting
// point count in a register where cl compares against memory. Tried: the
// clear as a whole-struct assignment (turns into REP MOVSD, structurally
// wrong), as two named zero locals, and the count bound before and after
// the co-op read. Same materialised-constant class as the NearByLocation
// sites.
bool Scenario_00689D30::ReadStartPoints(CCINI_00689D30* ini)
{
    Cell_00689D30* slot = Waypoints;

    StartX = -1;
    StartY = -1;
    Width = -1;
    Height = -1;
    NumberStartingPoints = -1;

    int zeroX = 0;
    int zeroY = 0;

    Cell_00689D30* clear = slot;
    for (int n = 8; n != 0; n--) {
        clear->X = zeroX;
        clear->Y = zeroY;
        clear++;
    }

    StartX = ini->ReadInteger(STR_0083DE68, STR_0083DE70, StartX);
    StartY = ini->ReadInteger(STR_0083DE68, STR_0083DE60, StartY);
    Width = ini->ReadInteger(STR_0083DE68, STR_0082BBE4, Width);
    Height = ini->ReadInteger(STR_0083DE68, STR_0081A7A8, Height);
    NumberStartingPoints =
        ini->ReadInteger(STR_0083DE68, STR_0083DE48, NumberStartingPoints);
    NumCoopHumanStartSpots =
        ini->ReadInteger(STR_0083DE68, STR_0083DE30, NumCoopHumanStartSpots);

    int i = 0;
    int count = NumberStartingPoints;
    if (count > 0) {
        do {
            int next = i + 1;
            char key[12];
            gg_sprintf(key, STR_0083DE24, next);
            *slot = ini->ReadWaypoint(STR_0083DE68, key, *slot);
            i = next;
            slot++;
        } while (i < NumberStartingPoints);
    }
    return true;
}
