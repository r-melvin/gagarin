// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/addresses derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x4AE4C0 / 0x68BD80),
//   cross-checked against YRpp (reconfirmed here).
//
// ScenarioClass — the global scenario/mission record. Only two methods are
// matched here, so the class is hand-padded to the single member they touch
// (the Waypoints array at +0x632); the full layout is P2.
#ifndef GG_MATCH_CORE_SCENARIO_CLASS_METHODS_H
#define GG_MATCH_CORE_SCENARIO_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/cell.h"   // CellStruct — a packed map cell coordinate { short X; short Y }
#include "../_layout/object_class.h"   // CoordStruct
#include "frame_counter.h"

// ---- iterator singleton + cell, used only by UpdateCellLighting ----
// CellClass — only the lighting-recalc entry (0x484680) is referenced.
class CellClass
{
public:
    void RecalcAttributes_484680();   // GAMEMD 0x484680  __thiscall
};

// The global map/radar singleton at 0x87F7E8. UpdateCellLighting drives its
// spiral cell iterator (begin @0x578350, next @0x578290).
struct MapInstanceClass
{
    // FUNCTION: GAMEMD 0x6D0F00 (decl; reloc)
    void FUN_006D0F00();
    // FUNCTION: GAMEMD 0x6AC5F0 (decl; reloc)
    void FUN_006AC5F0(void* item, int value);
    // FUNCTION: GAMEMD 0x6A7590 (decl; reloc)
    void FUN_006A7590(int index);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) -- the height at a coordinate.
    int FUN_00578080(CoordStruct* where);
    // FUNCTION: GAMEMD 0x57B790 (decl; reloc)
    void FUN_0057B790(CellStruct* cell);
    // FUNCTION: GAMEMD 0x56BEC0 (decl; reloc)
    bool FUN_0056BEC0(CellStruct cell, int value);
    void       IteratorBegin_578350();   // GAMEMD 0x578350  __thiscall
    CellClass* IteratorNext_578290();    // GAMEMD 0x578290  __thiscall
};

// GLOBAL: GAMEMD 0x87F7E8  MapClass::Instance (the map singleton).
extern MapInstanceClass MapInstance;

// GLOBAL: GAMEMD 0x00B05458  the "undefined" waypoint sentinel cell.
extern CellStruct WaypointUndefined;

// The scenario's mission timer at +0x11E8 (a frame timer; the middle dword is
// not initialised by the constructor taking a duration).
struct ScenarioTimer
{
    int StartTime;
    int unknown_04;
    int TimeLeft;
    ScenarioTimer() {}
    explicit ScenarioTimer(int duration)
    {
        StartTime = CurrentFrame;
        TimeLeft = duration;
    }
    int GetTimeLeft() const
    {
        int left = TimeLeft;
        if (StartTime != -1) {
            int elapsed = CurrentFrame - StartTime;
            return (elapsed < left) ? left - elapsed : 0;
        }
        return left;
    }
    bool IsOn() const
    {
        return StartTime != -1;
    }
    bool IsOff() const
    {
        return StartTime == -1;
    }
    void Start()
    {
        if (StartTime == -1) {
            StartTime = CurrentFrame;
        }
    }
    void Stop()
    {
        if (StartTime != -1) {
            TimeLeft = GetTimeLeft();
            StartTime = -1;
        }
    }
};

struct ScenarioClass
{
    // ---- matched methods (ascending by retail address) ----
    static void UpdateCellLighting();        // GAMEMD 0x4AE4C0  (free/static)
    CellStruct GetWaypointCoords(int idx);   // GAMEMD 0x68BCC0  __thiscall
    CoordStruct FUN_0068BD00(int idx);       // GAMEMD 0x68BD00  __thiscall
    bool FUN_0053A100();                     // GAMEMD 0x53A100  __thiscall
    bool IsDefinedWaypoint(int idx);         // GAMEMD 0x68BD80  __thiscall
    void FUN_00689670(int, int);             // GAMEMD 0x689670  __thiscall (decl)
    void FUN_00689910(int, int);             // GAMEMD 0x689910  __thiscall (decl)

    // ---- members touched by the matched methods ----
    char       _base[0x60C];          // 0x000  scenario header — P2
    int        Difficulty;            // 0x60C  read by TAction.cpp 0x6E2AF0
    char       _base2[0x632 - 0x610]; // 0x610
    CellStruct Waypoints[702];        // 0x632  valid range [0..701]
    char       _after_waypoints[0x11E8 - 0x632 - 702 * 4];
    ScenarioTimer Timer_11E8;         // 0x11E8 read by TAction.cpp 0x6E13A0
    char       _pad_11F4[0x34A5 - 0x11F4];
    bool       unknown_34A5;          // 0x34A5
    bool       unknown_34A6;          // 0x34A6
    bool       unknown_34A7;          // 0x34A7
    bool       unknown_34A8;          // 0x34A8
    char       _pad_34A9[0x3528 - 0x34A9];
    int        unknown_3528;          // 0x3528
    char       _pad_352C[4];
    int        unknown_3530;          // 0x3530
    int        unknown_3534;          // 0x3534
    int        unknown_3538;          // 0x3538
    int        unknown_353C;          // 0x353C
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(ScenarioClass, Difficulty) == 0x60C);
GG_STATIC_ASSERT(offsetof(ScenarioClass, Waypoints) == 0x632);
GG_STATIC_ASSERT(offsetof(ScenarioClass, Timer_11E8) == 0x11E8);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34A5) == 0x34A5);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_34A8) == 0x34A8);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3528) == 0x3528);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3530) == 0x3530);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3534) == 0x3534);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_3538) == 0x3538);
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_353C) == 0x353C);
#endif

#endif  // GG_MATCH_CORE_SCENARIO_CLASS_METHODS_H
