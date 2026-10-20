// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | EA-GPL-RA1-reference
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4C9220: DesiredFacing.Raw `MOV AX,[ECX]` compared
//   word-wise with `[EDX]` (the argument), StartFacing.Raw `SUB AX,[ECX+0x4]`
//   and the dword store `MOV [ECX+0x4],EAX`, ROT.Raw `MOV BP,[ECX+0x14]`
//   tested as a signed short, the timer at +0x8 read as StartTime
//   `[ECX+0x8]` (compared with -1) / TimeLeft `[ECX+0x10]` and written back
//   as three dwords `[ECX+0x8..0x10]` from a stack temporary whose middle
//   dword is never initialised, and the frame counter `[0xA8ED84]`. The
//   layout is the one already confirmed in match/movement/facing_methods.h
//   (not edited; re-declared so this TU stands alone). YRpp Facing.h /
//   Timer.h consulted for the member and method names only; the shape of the
//   timer's remaining-time inline (remain/value, if/else returns) follows the
//   RA1 TIMER.H structure as a phrasing reference only (no text copied).
#ifndef GG_MATCH_MOVEMENT_FACING_SET_DESIRED_METHODS_H
#define GG_MATCH_MOVEMENT_FACING_SET_DESIRED_METHODS_H

#include <stddef.h>
#include <stdlib.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame, the engine frame counter.
#include "../core/frame_counter.h"

// A 16-bit binary-angle direction padded to 4 bytes.
struct Dir_004C9220
{
    unsigned short Raw;       // +0x0000
    unsigned short Padding;   // +0x0002
};
GG_STATIC_ASSERT(sizeof(Dir_004C9220) == 4);

// CDTimerClass (TimerStruct<FrameTimer>). CurrentTime is the empty
// FrameTimer's 4-byte slot: the constructor never writes it, which is why
// retail's timer restart copies an uninitialised dword through the temporary.
struct Timer_004C9220
{
    int StartTime;            // +0x0000
    int CurrentTime;          // +0x0004  (empty FrameTimer slot)
    int TimeLeft;             // +0x0008

    Timer_004C9220() {}
    Timer_004C9220(int duration) : StartTime(CurrentFrame), TimeLeft(duration) {}

    // Frames still to go: TimeLeft minus the frames elapsed since StartTime,
    // clamped at zero; a timer that was never started reports TimeLeft.
    // Phrasing is load-bearing: the `remain` local with the two returns in an
    // if/else is the only form (of eight tried) that places the zero result
    // out of line behind the caller's join (`JGE; ... XOR EDI,EDI; JMP`);
    // the equivalent `if (passed >= total) return 0; return total - passed;`
    // inverts the branch and keeps the zero inline.
    int GetTimeLeft() const
    {
        int remain = this->TimeLeft;
        if (this->StartTime != -1) {
            int value = CurrentFrame - this->StartTime;
            if (value < remain)
                return remain - value;
            else
                return 0;
        }
        return remain;
    }
};
GG_STATIC_ASSERT(offsetof(Timer_004C9220, TimeLeft) == 0x8);
GG_STATIC_ASSERT(sizeof(Timer_004C9220) == 0xC);

struct Facing_004C9220
{
    Dir_004C9220   DesiredFacing;   // +0x0000
    Dir_004C9220   StartFacing;     // +0x0004
    Timer_004C9220 RotationTimer;   // +0x0008
    Dir_004C9220   ROT;             // +0x0014

    // The facing right now: DesiredFacing once the rotation has run down,
    // otherwise DesiredFacing backed off by the remaining steps. Inlined
    // into SetDesired (retail body at 0x4C93D0, not matched here).
    Dir_004C9220 Current() const
    {
        if ((short)this->ROT.Raw > 0 && this->RotationTimer.GetTimeLeft() != 0) {
            short diff  = (short)(this->DesiredFacing.Raw - this->StartFacing.Raw);
            short steps = (short)(abs(diff) / (short)this->ROT.Raw);
            Dir_004C9220 ret = this->DesiredFacing;
            if (steps > 0) {
                ret.Raw = (unsigned short)(ret.Raw - (diff / steps) * this->RotationTimer.GetTimeLeft());
            }
            return ret;
        }
        return this->DesiredFacing;
    }

    // FUNCTION: GAMEMD 0x4C9220 — Facing::SetDesired.
    bool SetDesired(const Dir_004C9220& facing);
};
GG_STATIC_ASSERT(offsetof(Facing_004C9220, DesiredFacing) == 0x00);
GG_STATIC_ASSERT(offsetof(Facing_004C9220, StartFacing)   == 0x04);
GG_STATIC_ASSERT(offsetof(Facing_004C9220, RotationTimer) == 0x08);
GG_STATIC_ASSERT(offsetof(Facing_004C9220, ROT)           == 0x14);
GG_STATIC_ASSERT(sizeof(Facing_004C9220)                  == 0x18);

#endif  // GG_MATCH_MOVEMENT_FACING_SET_DESIRED_METHODS_H
