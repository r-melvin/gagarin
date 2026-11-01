// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x763A50.

#include "waypoint_path_exists_methods.h"

// FUNCTION: GAMEMD 0x763A50  WaypointPathClass::WaypointExistsAt (__thiscall, ret 0x4)
//
// Is there already a planning waypoint in the same cell as `coords`? Both the
// argument and each stored waypoint are reduced to cell coordinates (signed
// divide by 256, compared as shorts); the first hit records its index at +0x24
// and reports true.
//
// The phrasing is deliberately naive: the argument's cell is converted inside
// the loop and the bound is the member itself. VC6 hoists both invariants
// (the conversion into EBX/EBP, the count into a stack slot) and spills `this`
// to a second slot, which is exactly the `SUB ESP,8` retail prologue. Writing
// the hoisting by hand (a `count` local, the conversion before the loop, a
// pointer walk) changes the register assignment and scores 82.5% at best.
bool WaypointPathClass::WaypointExistsAt(CoordStruct const* coords)
{
    CellStruct target;
    for (int i = 0; i < WaypointCount; i++) {
        target = Coord2Cell(coords);
        if (Coord2Cell(&Waypoints[i]) == target) {
            FoundIndex = i;
            return true;
        }
    }
    return false;
}
