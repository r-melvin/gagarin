// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// IAT slots resolved from the pinned image: 0x7E1530 WINMM timeGetTime,
// 0x7E1538 WINMM timeBeginPeriod.
//   0x4E2460 reads the start stamp at +0x00 and returns the elapsed count.
//   0x5D5870 is a constructor that only raises the timer resolution to 1 ms
//     and returns `this` (its six callers construct it in place).
// Class names are descriptive; no allocation site was traced, so no size is
// asserted.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern "C" __declspec(dllimport) unsigned int __stdcall timeBeginPeriod(unsigned int period);

class ElapsedTimer
{
public:
    // FUNCTION: GAMEMD 0x4E2460
    unsigned long Elapsed() const;

    unsigned long Start;   // +0x00
};
GG_STATIC_ASSERT(offsetof(ElapsedTimer, Start) == 0x00);

class TimerResolution
{
public:
    // FUNCTION: GAMEMD 0x5D5870
    TimerResolution();
};

// FUNCTION: GAMEMD 0x4E2460
unsigned long ElapsedTimer::Elapsed() const
{
    unsigned long now = timeGetTime();
    if (now <= Start) {
        return now - Start - 1;
    }
    return now - Start;
}

// FUNCTION: GAMEMD 0x5D5870
TimerResolution::TimerResolution()
{
    timeBeginPeriod(1);
}
