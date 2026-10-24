// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// StageClass is the nonvirtual staged-frame base at TerrainClass+0xAC.
// Construction stores:71BBA4..71BBC7; restart/advance:71C730.
// Inline operations only; no separate retail entry is claimed.
#ifndef GG_MATCH_LAYOUT_STAGE_CLASS_H
#define GG_MATCH_LAYOUT_STAGE_CLASS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "frame_timer.h"
struct AbstractNoInit;
class StageClass
{
public:
    int Value;
    unsigned char HasChanged;
    unsigned char unknown_05[3];
    CDTimerClass Timer;
    int Rate;
    int Step;

    StageClass() : Value(0), HasChanged(false), Timer(0), Rate(0), Step(1) {}
    explicit StageClass(const AbstractNoInit&) {}
    // Project name for the inlined timer/rate restart.
    void SetRate(int rate)
    {
        Timer = CDTimerClass(rate);
        Rate = rate;
    }
};
GG_STATIC_ASSERT(offsetof(StageClass, Value) == 0);
GG_STATIC_ASSERT(offsetof(StageClass, HasChanged) == 4);
GG_STATIC_ASSERT(offsetof(StageClass, Timer) == 8);
GG_STATIC_ASSERT(offsetof(StageClass, Rate) == 0x14);
GG_STATIC_ASSERT(offsetof(StageClass, Step) == 0x18);
GG_STATIC_ASSERT(sizeof(StageClass) == 0x1C);
#endif
