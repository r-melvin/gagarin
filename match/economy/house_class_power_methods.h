// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/bodies derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   (reconfirmed numerically
//   from the disassembly below).
//
// HouseClass power/radar-outage helpers (economy subsystem):
//   HouseClass::GetPowerPercentage  @0x4FCE30  (__thiscall, returns double)
//   HouseClass::CreatePowerOutage   @0x50BC90  (__thiscall, int duration)
//   HouseClass::CreateRadarOutage   @0x50BCD0  (__thiscall, int duration)
//
// Only the members these three methods touch are modelled; the rest of the
// HouseClass layout is padded (full layout is P2). Confirmed offsets:
//   PowerBlackoutTimer        @0x2A4  (CDTimerClass, 12 bytes)
//   RadarBlackoutTimer        @0x2B0  (CDTimerClass, 12 bytes)
//   PowerOutput               @0x53A4 (int)
//   PowerDrain                @0x53A8 (int)
//   PowerBlackoutWasActivated @0x5778 (bool)
//   RadarBlackoutWasActivated @0x5779 (bool)
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_POWER_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_POWER_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// Unsorted::CurrentFrame — the global frame counter at 0x00A8ED84. Loaded via
// the absolute-moffs32 form (opcode A1) in both outage helpers; the reloc is
// normalised by the differ.
#include "../core/frame_counter.h"

// ---------------------------------------------------------------------------
// CDTimerClass (TimerStruct<FrameTimer>) — a 12-byte countdown timer. The
// middle dword is the empty FrameTimer "clock" placeholder; the retail copy of
// a freshly-constructed timer into a member is a plain 12-byte (POD) copy that
// drags the uninitialised middle dword along, so model it as a flat struct.
// ---------------------------------------------------------------------------
struct CDTimerClass
{
    int StartTime;    // +0x0
    int CurrentTime;  // +0x4  (empty FrameTimer clock placeholder)
    int TimeLeft;     // +0x8

    CDTimerClass(int duration)
    {
        this->StartTime = CurrentFrame;
        this->TimeLeft = duration;
    }
};

GG_STATIC_ASSERT(offsetof(CDTimerClass, StartTime)   == 0x0);
GG_STATIC_ASSERT(offsetof(CDTimerClass, CurrentTime) == 0x4);
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft)    == 0x8);
GG_STATIC_ASSERT(sizeof(CDTimerClass) == 0xC);

// ---------------------------------------------------------------------------
struct HouseClass
{
    double GetPowerPercentage() const;          // GAMEMD 0x4FCE30 __thiscall
    void   CreatePowerOutage(int duration);     // GAMEMD 0x50BC90 __thiscall
    void   CreateRadarOutage(int duration);     // GAMEMD 0x50BCD0 __thiscall

    char         pad0[0x2A4];                   // +0x000
    CDTimerClass PowerBlackoutTimer;            // +0x2A4
    CDTimerClass RadarBlackoutTimer;            // +0x2B0
    char         pad1[0x53A4 - 0x2BC];          // +0x2BC
    int          PowerOutput;                   // +0x53A4
    int          PowerDrain;                    // +0x53A8
    char         pad2[0x5778 - 0x53AC];         // +0x53AC
    bool         PowerBlackoutWasActivated;     // +0x5778
    bool         RadarBlackoutWasActivated;     // +0x5779
};

GG_STATIC_ASSERT(offsetof(HouseClass, PowerBlackoutTimer)        == 0x2A4);
GG_STATIC_ASSERT(offsetof(HouseClass, RadarBlackoutTimer)        == 0x2B0);
GG_STATIC_ASSERT(offsetof(HouseClass, PowerOutput)               == 0x53A4);
GG_STATIC_ASSERT(offsetof(HouseClass, PowerDrain)                == 0x53A8);
GG_STATIC_ASSERT(offsetof(HouseClass, PowerBlackoutWasActivated) == 0x5778);
GG_STATIC_ASSERT(offsetof(HouseClass, RadarBlackoutWasActivated) == 0x5779);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_POWER_METHODS_H
