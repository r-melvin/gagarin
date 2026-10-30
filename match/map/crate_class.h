// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | TibSun-cross-check | behaviour-confirmed-name
#ifndef GG_MATCH_MAP_CRATE_CLASS_H
#define GG_MATCH_MAP_CRATE_CLASS_H
#include "../_layout/frame_timer.h"
#include "../_layout/cell.h"

// Native 0x4A1754/1780/1787 and map callers at 0x56C07B/56BFAE.
class CrateClass
{
public:
    CDTimerClass Timer;
    CellStruct Location;
    // FUNCTION: GAMEMD 0x4A1750 (declaration) -- clears the crate's slot and timer.
    void FUN_004A1750();
};
GG_STATIC_ASSERT(offsetof(CrateClass, Timer) == 0x00);
GG_STATIC_ASSERT(offsetof(CrateClass, Timer) + offsetof(CDTimerClass, StartTime) == 0x00);
GG_STATIC_ASSERT(offsetof(CrateClass, Timer) + offsetof(CDTimerClass, CurrentTime) == 0x04);
GG_STATIC_ASSERT(offsetof(CrateClass, Timer) + offsetof(CDTimerClass, TimeLeft) == 0x08);
GG_STATIC_ASSERT(offsetof(CrateClass, Location) == 0x0C);
GG_STATIC_ASSERT(offsetof(CrateClass, Location) + offsetof(CellStruct, Y) == 0x0E);
GG_STATIC_ASSERT(sizeof(CrateClass) == 0x10);
#endif
