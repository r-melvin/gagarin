// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm @ 0x4AE4C0,
//   0x68BD80). Names cross-checked against YRpp ScenarioClass.h (consult-only,
//   no LICENSE; every offset/address reconfirmed against the user's binary).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x4AE4C0   ScenarioClass::UpdateCellLighting  (static)
//   FUNCTION: GAMEMD 0x68BD80   ScenarioClass::IsDefinedWaypoint   (__thiscall)
//   GLOBAL:   GAMEMD 0x87F7E8   MapClass::Instance
//   GLOBAL:   GAMEMD 0x00B05458 undefined-waypoint sentinel cell

#include "scenario_class_methods.h"

// FUNCTION: GAMEMD 0x4AE4C0  (static)
// Walk every cell of the map via the spiral iterator and recompute its tinted
// lighting. Iterator begin @0x578350 primes the walk; next @0x578290 returns
// each CellClass* (NULL terminates); 0x484680 is the per-cell recalc.
void ScenarioClass::UpdateCellLighting()
{
    MapInstance.IteratorBegin_578350();

    CellClass* cell = MapInstance.IteratorNext_578290();
    while (cell != 0)
    {
        cell->RecalcAttributes_484680();
        cell = MapInstance.IteratorNext_578290();
    }
}

// FUNCTION: GAMEMD 0x68BCC0  ScenarioClass::GetWaypointCoords (__thiscall, ret 0x8)
// Returns the 4-byte CellStruct by value, so retail's RET 0x8 covers the hidden
// return-buffer pointer plus the index. No bounds check — callers are expected
// to have asked IsDefinedWaypoint first.
CellStruct ScenarioClass::GetWaypointCoords(int idx)
{
    return Waypoints[idx];
}

// FUNCTION: GAMEMD 0x68BD80  (__thiscall)
// True iff waypoint `idx` is in range [0..701] and its stored cell differs from
// the sentinel "undefined" cell. The first mismatching coordinate short-circuits
// to true; an exact match (both X and Y equal the sentinel) is "not defined".
bool ScenarioClass::IsDefinedWaypoint(int idx)
{
    if (idx < 702 && idx >= 0 &&
        (Waypoints[idx].X != WaypointUndefined.X ||
         Waypoints[idx].Y != WaypointUndefined.Y))
    {
        return true;
    }
    return false;
}
