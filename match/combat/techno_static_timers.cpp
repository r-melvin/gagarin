// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Two class-scope static timers of the Techno.cpp unit (retail 0x6F28A0-0x7108DF).
// Both initialisers (0x6F2AB0, 0x6F2AF0) sit after that unit's header group, and
// both exit stubs only test-and-set one bit of the guard byte at 0xB0EA38 (bit 0
// for the frame timer, bit 1 for the wall-clock timer), which is how VC6 emits
// the destructor of a static data member. The frame timer starts from the
// frame counter with the middle word untouched; the wall-clock timer stamps the
// multimedia clock (GameClockClass::GetTime, 0x6C8C40) and clears the duration.
#include "../_layout/elapsed_timer.h"
#include "../_layout/frame_timer.h"

struct TechnoStaticFrameTimer : CDTimerClass
{
    TechnoStaticFrameTimer()
    {
        StartTime = CurrentFrame;
        TimeLeft = 0;
    }
    ~TechnoStaticFrameTimer() {}
};
struct TechnoStaticClockTimer : ScenarioElapsedTimer { ~TechnoStaticClockTimer() {} };

struct TechnoStatics
{
    // GLOBAL: GAMEMD 0xB0EA80
    static TechnoStaticFrameTimer FrameTimer;
    // GLOBAL: GAMEMD 0xB0EA70
    static TechnoStaticClockTimer ClockTimer;
};

// SYNTHETIC: GAMEMD 0x006F2AB0 -- initialiser of TechnoStatics::FrameTimer
// SYNTHETIC: GAMEMD 0x006F2AD0 -- exit stub of TechnoStatics::FrameTimer, guard byte 0xB0EA38 bit 0
TechnoStaticFrameTimer TechnoStatics::FrameTimer;
// SYNTHETIC: GAMEMD 0x006F2AF0 -- initialiser of TechnoStatics::ClockTimer
// SYNTHETIC: GAMEMD 0x006F2B20 -- exit stub of TechnoStatics::ClockTimer, guard byte 0xB0EA38 bit 1
TechnoStaticClockTimer TechnoStatics::ClockTimer;
