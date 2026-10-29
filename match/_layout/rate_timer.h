// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RateTimer = CDTimerClass plus its reload rate (sizeof = 0x10, Rate at +0x0C).
//   Proven by BuildingClass::GateTimer (ctor stores StartTime 0x604, TimeLeft
//   0x60C, Rate 0x610) and by DriveLocomotionClass::Draw_Matrix 0x004AFF60, which
//   reads StartTime, TimeLeft and divides the elapsed fraction by Rate. The
//   duration constructor starts the timer, then stores Rate (retail 0x4AF540).
//   Shared by the ship and drive locomotor headers. It uses the same guard as the
//   copies in building_class.h and locomotion_class.h, so whichever comes first wins;
//   the layout is identical.
#ifndef GG_MATCH_LAYOUT_RATETIMER_DEFINED
#define GG_MATCH_LAYOUT_RATETIMER_DEFINED

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "frame_timer.h"

struct RateTimer : public CDTimerClass
{
    int Rate;   // +0x0C

    RateTimer() {}
    RateTimer(int rate)
    {
        this->CDTimerClass::Start(rate);
        this->Rate = rate;
    }
};
GG_STATIC_ASSERT(offsetof(RateTimer, Rate) == 0x0C);
GG_STATIC_ASSERT(sizeof(RateTimer)         == 0x10);
#endif
