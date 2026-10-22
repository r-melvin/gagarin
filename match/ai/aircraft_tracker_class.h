// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4137A0 / 0x413800), cross-checked
//   against YRpp (
//   reconfirmed numerically here).
//
// AircraftTrackerClass — tracks aerial units in a 20x20 grid of
// DynamicVectorClass<TechnoClass*> buckets (TrackerVectors), plus a scratch
// CurrentVector populated by FillCurrentVector and drained by Get.
#ifndef GG_MATCH_AI_AIRCRAFT_TRACKER_CLASS_H
#define GG_MATCH_AI_AIRCRAFT_TRACKER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CellStruct_004134A0 { short X; short Y; };
GG_STATIC_ASSERT(sizeof(CellStruct_004134A0) == 4);

// GLOBAL: GAMEMD 0x87F914 / 0x87F918 — map width / height in cells.
extern int DAT_0087F914;
extern int DAT_0087F918;
// GLOBAL: GAMEMD 0x887850 — the "no cell" coordinate handed back on Remove.
extern CellStruct_004134A0 DAT_00887850;

struct TrackVtbl;
// The tracked object; only three vtable slots are used: +0x1B8 and +0x2F4
// (a CellStruct through an out pointer) and +0x2F8 (a CellStruct by value).
class TechnoClass
{
public:
    TrackVtbl* Vptr;   // +0x00
};
typedef CellStruct_004134A0* (TechnoClass::*FnCell_004134A0)(CellStruct_004134A0* out);
typedef void (TechnoClass::*FnSetCell_004134A0)(CellStruct_004134A0 cell);
struct TrackVtbl
{
    char _pad000[0x1B8];                 // +0x0000
    FnCell_004134A0 GetMapCoords;        // +0x01B8
    char _pad1BC[0x2F4 - 0x1BC];         // +0x01BC
    FnCell_004134A0 GetTrackedCoords;    // +0x02F4
    FnSetCell_004134A0 SetTrackedCoords; // +0x02F8
};
GG_STATIC_ASSERT(offsetof(TrackVtbl, GetMapCoords) == 0x1B8);
GG_STATIC_ASSERT(offsetof(TrackVtbl, GetTrackedCoords) == 0x2F4);
GG_STATIC_ASSERT(offsetof(TrackVtbl, SetTrackedCoords) == 0x2F8);

#include "../_layout/aircraft_tracker_class.h"

#endif // GG_MATCH_AI_AIRCRAFT_TRACKER_CLASS_H
