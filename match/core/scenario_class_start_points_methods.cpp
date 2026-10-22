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
// PARTIAL (94.0%, 94/100 by position; multiset identical; was 8.0%). Two
// levers took it from 8.0%: the clear loop assigns a constructed two-int cell
// (`*clear = Cell(0, 0)`) instead of storing two named zero locals, which is
// what gives retail's two separate zero registers filled in the prologue and
// the plain `TEST ECX,ECX` count test; and the waypoint loop is a counted `for`
// whose key uses `i + 1`, so the increment folds onto the key's `LEA`
// (`MOV EAX,EBX`). What is left is the order inside the loop tail: retail loads
// both halves of the returned cell, stores both, then re-reads the count and
// advances the cursor (`MOV ECX,[EAX]; MOV EAX,[EAX+4]; MOV [EDI],ECX;
// MOV [EDI+4],EAX; ... ADD EDI,8`), where cl stores the first half, advances
// the cursor and stores the second half at `[EDI-4]`. Tried: cursor advance
// before/after the index bump, an indexed `Waypoints[i]` target, a POD cell
// with an inline maker (same 94.0%), a named copy of the returned cell, a
// member-wise copy and a const reference to the returned cell (82.2%).
bool Scenario_00689D30::ReadStartPoints(CCINI_00689D30* ini)
{
    Cell_00689D30* slot = Waypoints;

    StartX = -1;
    StartY = -1;
    Width = -1;
    Height = -1;
    NumberStartingPoints = -1;

    Cell_00689D30* clear = slot;
    for (int n = 8; n != 0; n--) {
        *clear = Cell_00689D30(0, 0);
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

    for (int i = 0; i < NumberStartingPoints; i++) {
        char key[12];
        gg_sprintf(key, STR_0083DE24, i + 1);
        *slot = ini->ReadWaypoint(STR_0083DE68, key, *slot);
        slot++;
    }
    return true;
}
