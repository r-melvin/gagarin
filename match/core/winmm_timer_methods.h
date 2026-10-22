// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The two multimedia-timer helpers (winmm_timer_methods.cpp). Class names are
// descriptive; no allocation site was traced, so no size is asserted.
#ifndef GG_MATCH_CORE_WINMM_TIMER_METHODS_H
#define GG_MATCH_CORE_WINMM_TIMER_METHODS_H

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
    // FUNCTION: GAMEMD 0x5D5880 (declaration) -- lowers the resolution again
    // (timeEndPeriod(1)).
    ~TimerResolution();
    // FUNCTION: GAMEMD 0x5D5890 (declaration) -- the current timeGetTime value.
    unsigned long FUN_005D5890() const;
};

#endif  // GG_MATCH_CORE_WINMM_TIMER_METHODS_H
