// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x70E380: `[ECX+0x198]` (IronTintTimer.StartTime,
//   compared with -1), `[ECX+0x1A0]` (IronTintTimer.TimeLeft), the dword
//   global `[0xA8ED84]` (CurrentFrame, minus StartTime) and `[ECX+0x1A4]`
//   (IronTintStage, the jump-table selector 1..9 via `LEA EAX,[ECX-1]; CMP
//   EAX,8; JA`). Names from the YRpp method map / TechnoClass.h
//   (consult-only, no LICENSE); the timer and stage agree with
//   match/_layout/techno_class.h (IronTintTimer @0x198, IronTintStage @0x1A4).
//   Shape mirrors the sibling GetAirstrikeTintIntensity (0x70E4B0) in
//   match/renderer/techno_class_airstrike_tint_methods.h.
#ifndef GG_MATCH_COMBAT_TECHNO_CLASS_INVULN_TINT_METHODS_H
#define GG_MATCH_COMBAT_TECHNO_CLASS_INVULN_TINT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame, the engine frame counter.
extern int CurrentFrame_0070E380;

// CDTimerClass — frame count-down timer (sizeof = 0xC). GetTimeLeft is the
// inlined read seen at 0x70E380..0x70E3A3.
struct CDTimer_0070E380
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04
    int TimeLeft;     // +0x08

    int GetTimeLeft() const
    {
        int left = TimeLeft;
        if (StartTime != -1) {
            int elapsed = CurrentFrame_0070E380 - StartTime;
            if (elapsed < left) {
                left = left - elapsed;
            } else {
                left = 0;
            }
        }
        return left;
    }
};
GG_STATIC_ASSERT(offsetof(CDTimer_0070E380, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimer_0070E380)             == 0xC);

struct TechnoClass
{
    char             _pad000[0x198];     // +0x0000
    CDTimer_0070E380 IronTintTimer;      // +0x0198
    unsigned int     IronTintStage;      // +0x01A4

    // FUNCTION: GAMEMD 0x70E380  TechnoClass::GetInvulnerabilityTintIntensity
    int GetInvulnerabilityTintIntensity(int currentIntensity);
};
GG_STATIC_ASSERT(offsetof(TechnoClass, IronTintTimer) == 0x198);
GG_STATIC_ASSERT(offsetof(TechnoClass, IronTintTimer) + offsetof(CDTimer_0070E380, TimeLeft) == 0x1A0);
GG_STATIC_ASSERT(offsetof(TechnoClass, IronTintStage) == 0x1A4);

#endif  // GG_MATCH_COMBAT_TECHNO_CLASS_INVULN_TINT_METHODS_H
