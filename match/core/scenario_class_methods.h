// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/addresses derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x4AE4C0 / 0x68BD80),
//   cross-checked against YRpp (consult-only; reconfirmed here).
//
// ScenarioClass — the global scenario/mission record. Only two methods are
// matched here, so the class is hand-padded to the single member they touch
// (the Waypoints array at +0x632); the full layout is P2.
#ifndef GG_MATCH_CORE_SCENARIO_CLASS_METHODS_H
#define GG_MATCH_CORE_SCENARIO_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// CellStruct — a packed map cell coordinate { short X; short Y }.
struct CellStruct
{
    short X;   // +0x0
    short Y;   // +0x2
};

// ---- iterator singleton + cell, used only by UpdateCellLighting ----
// CellClass — only the lighting-recalc entry (0x484680) is referenced.
struct CellClass
{
    void RecalcAttributes_484680();   // GAMEMD 0x484680  __thiscall
};

// The global map/radar singleton at 0x87F7E8. UpdateCellLighting drives its
// spiral cell iterator (begin @0x578350, next @0x578290).
struct MapInstanceClass
{
    void       IteratorBegin_578350();   // GAMEMD 0x578350  __thiscall
    CellClass* IteratorNext_578290();    // GAMEMD 0x578290  __thiscall
};

// GLOBAL: GAMEMD 0x87F7E8  MapClass::Instance (the map singleton).
extern MapInstanceClass MapInstance;

// GLOBAL: GAMEMD 0x00B05458  the "undefined" waypoint sentinel cell.
extern CellStruct WaypointUndefined;

struct ScenarioClass
{
    // ---- matched methods (ascending by retail address) ----
    static void UpdateCellLighting();        // GAMEMD 0x4AE4C0  (free/static)
    CellStruct GetWaypointCoords(int idx);   // GAMEMD 0x68BCC0  __thiscall
    bool IsDefinedWaypoint(int idx);         // GAMEMD 0x68BD80  __thiscall

    // ---- members touched by the matched methods ----
    char       _base[0x632];          // 0x000  scenario header — P2
    CellStruct Waypoints[702];        // 0x632  valid range [0..701]
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(ScenarioClass, Waypoints) == 0x632);
#endif

#endif  // GG_MATCH_CORE_SCENARIO_CLASS_METHODS_H
