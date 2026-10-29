// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x70E4B0: `[ECX+0x1B4]` (AirstrikeTintTimer.StartTime,
//   compared with -1), `[ECX+0x1BC]` (AirstrikeTintTimer.TimeLeft), the
//   dword global `[0xA8ED84]` (CurrentFrame, subtracted from StartTime) and
//   `[ECX+0x1C0]` (AirstrikeTintStage, the jump-table selector 1..9). Names
//   cross-checked against YRpp; the
//   timer and stage agree with match/_layout/techno_class.h.
#ifndef GG_MATCH_RENDERER_TECHNO_CLASS_AIRSTRIKE_TINT_METHODS_H
#define GG_MATCH_RENDERER_TECHNO_CLASS_AIRSTRIKE_TINT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame, the engine frame counter.
#include "../core/frame_counter.h"

// CDTimer_0070E4B0 — frame count-down timer (sizeof = 0xC). GetTimeLeft is the
// inlined read seen at 0x70E4B0..0x70E4D3.
struct CDTimer_0070E4B0
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04
    int TimeLeft;     // +0x08

    int GetTimeLeft() const
    {
        int left = TimeLeft;
        if (StartTime != -1) {
            int elapsed = CurrentFrame - StartTime;
            if (elapsed < left) {
                left = left - elapsed;
            } else {
                left = 0;
            }
        }
        return left;
    }
};
GG_STATIC_ASSERT(offsetof(CDTimer_0070E4B0, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimer_0070E4B0)             == 0xC);

// Retail RTTI 0x817B58 establishes the class key; public access preserves this ABI view.
class TechnoView_0070E4B0
{
public:
    char         _pad000[0x1B4];         // +0x0000
    CDTimer_0070E4B0 AirstrikeTintTimer;     // +0x01B4
    unsigned int AirstrikeTintStage;     // +0x01C0

    // FUNCTION: GAMEMD 0x70E4B0
    int GetAirstrikeTintIntensity(int currentIntensity);
};
GG_STATIC_ASSERT(offsetof(TechnoView_0070E4B0, AirstrikeTintTimer) == 0x1B4);
GG_STATIC_ASSERT(offsetof(TechnoView_0070E4B0, AirstrikeTintTimer) + offsetof(CDTimer_0070E4B0, TimeLeft) == 0x1BC);
GG_STATIC_ASSERT(offsetof(TechnoView_0070E4B0, AirstrikeTintStage) == 0x1C0);

#endif  // GG_MATCH_RENDERER_TECHNO_CLASS_AIRSTRIKE_TINT_METHODS_H
