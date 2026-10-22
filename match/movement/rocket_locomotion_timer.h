// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; YRpp consulted for the timer name only.
// Rocket-specific value views: fields, copy extents and frame global are pinned
// by the Rocket constructor/Process entry instructions.
#ifndef GG_MATCH_MOVEMENT_ROCKET_LOCOMOTION_TIMER_H
#define GG_MATCH_MOVEMENT_ROCKET_LOCOMOTION_TIMER_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "rocket_locomotion_views.h"
#include "rocket_locomotion_globals_view.h"
struct RocketTimer {
    int StartTime;
    int unknown_04;
    int TimeLeft;
    RocketTimer() : StartTime(DAT_00A8ED84), TimeLeft(0) {}
    RocketTimer(RocketNoInit) {}
    bool Expired() const {
        int left = TimeLeft;
        if (StartTime != -1) {
            int elapsed = DAT_00A8ED84 - StartTime;
            if (elapsed < left) left -= elapsed; else left = 0;
        }
        return left == 0;
    }
};
GG_STATIC_ASSERT(offsetof(RocketTimer,StartTime)==0);
GG_STATIC_ASSERT(offsetof(RocketTimer,unknown_04)==4);
GG_STATIC_ASSERT(offsetof(RocketTimer,TimeLeft)==8);
GG_STATIC_ASSERT(sizeof(RocketTimer)==0xC);
struct RocketRateTimer : RocketTimer {
    int Rate;
    RocketRateTimer() : Rate(0) {}
    RocketRateTimer(RocketNoInit tag) : RocketTimer(tag) {}
    int RemainingSubtract() const {
        int left=TimeLeft;
        if (StartTime != -1) {
            int elapsed=DAT_00A8ED84-StartTime;
            if (elapsed<left) left-=elapsed; else left=0;
        }
        return left;
    }
};
GG_STATIC_ASSERT(offsetof(RocketRateTimer,Rate)==0xC);
GG_STATIC_ASSERT(sizeof(RocketRateTimer)==0x10);
#endif
