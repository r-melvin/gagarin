// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: MissionClass ctor FUN_0x005B2DA0 (chains ObjectClass ctor
//   FUN_0x005F3900 at offset 0). Field offsets read from its init writes:
//   CurrentMission @0xAC (param[0x2B]=-1), SuspendedMission @0xB0,
//   QueuedMission @0xB4, unknown_bool_B8 @0xB8, MissionStatus @0xBC,
//   CurrentMissionStartTime @0xC0, MissionAccumulateTime @0xC4,
//   UpdateTimer.StartTime @0xC8 (param[0x32]) / .TimeLeft @0xD0 (param[0x34]).
//   Last member UpdateTimer ends at 0xD4 -> sizeof(MissionClass)==0xD4.
//   Cross-checked vs YRpp MissionClass.h.
//
// MissionClass — base of every game object that runs an AI mission state
// machine. Derives ObjectClass at offset 0 and adds the mission/sub-mission
// bookkeeping from 0xAC.
#ifndef GG_MATCH_LAYOUT_MISSION_CLASS_H
#define GG_MATCH_LAYOUT_MISSION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "object_class.h"

// CDTimerClass — count-down frame timer (sizeof = 0xC). StartTime @0x00,
// CurrentTime/accumulator @0x04 (FrameTimer clock, not stored by the ctor),
// TimeLeft @0x08. Self-guarded for reuse by downstream layers.
#ifndef GG_MATCH_LAYOUT_CDTIMERCLASS_DEFINED
#define GG_MATCH_LAYOUT_CDTIMERCLASS_DEFINED
struct CDTimerClass
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04  (FrameTimer clock slot)
    int TimeLeft;     // +0x08
};
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimerClass)             == 0xC);
#endif  // GG_MATCH_LAYOUT_CDTIMERCLASS_DEFINED

// MissionClass  (0xAC..0xD3, sizeof = 0xD4)
struct MissionClass : ObjectClass
{
    int           CurrentMission;            // +0xAC  (Mission enum, ctor = -1)
    int           SuspendedMission;          // +0xB0  (Mission enum, ctor = -1)
    int           QueuedMission;             // +0xB4  (Mission enum, ctor = -1)
    unsigned char unknown_bool_B8;           // +0xB8  (bool)
    unsigned char align_B9[3];               // +0xB9
    int           MissionStatus;             // +0xBC
    int           CurrentMissionStartTime;   // +0xC0  (frames)
    int           MissionAccumulateTime;     // +0xC4
    CDTimerClass  UpdateTimer;               // +0xC8  (0xC)
};

GG_STATIC_ASSERT(offsetof(MissionClass, CurrentMission)          == 0xAC);
GG_STATIC_ASSERT(offsetof(MissionClass, SuspendedMission)        == 0xB0);
GG_STATIC_ASSERT(offsetof(MissionClass, QueuedMission)           == 0xB4);
GG_STATIC_ASSERT(offsetof(MissionClass, unknown_bool_B8)         == 0xB8);
GG_STATIC_ASSERT(offsetof(MissionClass, MissionStatus)           == 0xBC);
GG_STATIC_ASSERT(offsetof(MissionClass, CurrentMissionStartTime) == 0xC0);
GG_STATIC_ASSERT(offsetof(MissionClass, MissionAccumulateTime)   == 0xC4);
GG_STATIC_ASSERT(offsetof(MissionClass, UpdateTimer)             == 0xC8);
GG_STATIC_ASSERT(sizeof(MissionClass)                            == 0xD4);

#endif  // GG_MATCH_LAYOUT_MISSION_CLASS_H
