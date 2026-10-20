// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x689D30: the five header fields at `[ESI+0x112C]` ..
//   `[ESI+0x113C]` preset to -1, the co-op spot count at `[ESI+0x11E4]`,
//   and the eight-entry waypoint table at `[ESI+0x1140]` zeroed eight
//   bytes at a time; the INI reads through 0x5276D0 with the section
//   "Header" at 0x83DE68 and the keys at 0x83DE70, 0x83DE60, 0x82BBE4,
//   0x81A7A8, 0x83DE48 and 0x83DE30; the per-waypoint key built by
//   `sprintf` 0x7C8EF4 from "Waypoint%d" at 0x83DE24; and the waypoint
//   read 0x529880, a __thiscall returning an eight-byte cell through a
//   hidden pointer with the current entry passed as the default. Names
//   cross-checked against YRpp ScenarioClass.h / CCINIClass.h
//   (consult-only; NO LICENSE).
#ifndef GG_MATCH_CORE_SCENARIO_CLASS_START_POINTS_METHODS_H
#define GG_MATCH_CORE_SCENARIO_CLASS_START_POINTS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A map cell pair. The user-declared constructor is what selects the
// hidden-pointer return convention for the waypoint read.
struct Cell_00689D30
{
    int X;   // +0x0000
    int Y;   // +0x0004
    Cell_00689D30() {}
};
GG_STATIC_ASSERT(sizeof(Cell_00689D30) == 8);

struct CCINI_00689D30
{
    // FUNCTION: GAMEMD 0x5276D0 (decl; reloc) — INIClass::ReadInteger.
    int ReadInteger(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x529880 (decl; reloc) — read a waypoint cell.
    Cell_00689D30 ReadWaypoint(const char* section, const char* key,
                               const Cell_00689D30& defaultValue);
};

// FUNCTION: GAMEMD 0x7C8EF4 (decl; reloc) — CRT sprintf.
extern "C" int __cdecl gg_sprintf(char* buffer, const char* format, ...);

// STRING: GAMEMD 0x83DE68 — "Header".
extern const char STR_0083DE68[];
// STRING: GAMEMD 0x83DE70 — "StartX".
extern const char STR_0083DE70[];
// STRING: GAMEMD 0x83DE60 — "StartY".
extern const char STR_0083DE60[];
// STRING: GAMEMD 0x82BBE4 — "Width".
extern const char STR_0082BBE4[];
// STRING: GAMEMD 0x81A7A8 — "Height".
extern const char STR_0081A7A8[];
// STRING: GAMEMD 0x83DE48 — "NumberStartingPoints".
extern const char STR_0083DE48[];
// STRING: GAMEMD 0x83DE30 — "NumCoopHumanStartSpots".
extern const char STR_0083DE30[];
// STRING: GAMEMD 0x83DE24 — "Waypoint%d".
extern const char STR_0083DE24[];

struct Scenario_00689D30
{
    char           _pad0000[0x112C];   // +0x0000
    int            StartX;             // +0x112C
    int            StartY;             // +0x1130
    int            Width;              // +0x1134
    int            Height;             // +0x1138
    int            NumberStartingPoints; // +0x113C
    Cell_00689D30  Waypoints[8];       // +0x1140
    char           _pad1180[0x11E4 - 0x1180]; // +0x1180
    int            NumCoopHumanStartSpots;    // +0x11E4

    // FUNCTION: GAMEMD 0x689D30 — ScenarioClass::ReadStartPoints.
    bool ReadStartPoints(CCINI_00689D30* ini);
};
GG_STATIC_ASSERT(offsetof(Scenario_00689D30, StartX)               == 0x112C);
GG_STATIC_ASSERT(offsetof(Scenario_00689D30, NumberStartingPoints) == 0x113C);
GG_STATIC_ASSERT(offsetof(Scenario_00689D30, Waypoints)            == 0x1140);
GG_STATIC_ASSERT(offsetof(Scenario_00689D30, NumCoopHumanStartSpots) == 0x11E4);

#endif  // GG_MATCH_CORE_SCENARIO_CLASS_START_POINTS_METHODS_H
