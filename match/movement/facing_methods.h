// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4C9480-0x4C9529), cross-checked
//   against YRpp Facing.h / Dir.h / Timer.h (consult-only; reconfirmed
//   numerically here).
//
// FacingClass models a rotation-in-progress: a desired/starting BAM direction,
// a count-down RotationTimer, and a ROT (rate-of-turn) direction. Only the
// rotation predicates IsRotating / IsRotatingCW / IsRotatingCCW are modelled
// here; the full ctor/setter set is P2.
//
// Confirmed layout (0x18 bytes):
//   [ECX+0x00] DesiredFacing.Raw   (word) -> MOV AX,[ECX]      in CW/CCW
//   [ECX+0x04] StartFacing.Raw     (word) -> SUB AX,[ECX+0x4]  in CW/CCW
//   [ECX+0x08] RotationTimer.StartTime  (dword) -> MOV EDX/ESI,[ECX+0x8]
//   [ECX+0x0C] RotationTimer.CurrentTime (empty FrameTimer, 4-byte slot)
//   [ECX+0x10] RotationTimer.TimeLeft    (dword) -> MOV EAX,[ECX+0x10]
//   [ECX+0x14] ROT.Raw             (word) -> CMP word [ECX+0x14],0
#ifndef GG_MATCH_MOVEMENT_FACING_METHODS_H
#define GG_MATCH_MOVEMENT_FACING_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84
// (read by RotationTimer.GetTimeLeft -> MOV ECX/EDX/EBX,[0x00A8ED84]).
extern int CurrentFrame;

// A 16-bit binary-angle-measure direction (Raw) padded to 4 bytes.
struct DirStruct
{
    unsigned short Raw;     // +0x00
    unsigned short Padding; // +0x02
};

// CDTimerClass = TimerStruct<FrameTimer>. FrameTimer is an empty clock whose
// value is the global CurrentFrame; as a member it occupies a 4-byte slot, so
// TimeLeft lands at +0x08 (confirmed by YRpp's static_assert and the disasm
// reading StartTime@+0x0 / TimeLeft@+0x8 relative to RotationTimer@0x8).
struct CDTimerClass
{
    int StartTime;   // +0x00
    int CurrentTime; // +0x04  (empty FrameTimer slot; not read directly)
    int TimeLeft;    // +0x08

    // Inlined into the predicates as: load TimeLeft; if StartTime!=-1 then
    // passed = CurrentFrame - StartTime; if passed >= TimeLeft return 0 else
    // return TimeLeft - passed.
    int GetTimeLeft() const
    {
        int start = StartTime;
        int total = TimeLeft;
        if (start == -1)
            return total;
        int passed = CurrentFrame - start;
        if (passed >= total)
            return 0;
        return total - passed;
    }
};

struct FacingClass
{
    bool IsRotating() const;    // GAMEMD 0x4C9480  __thiscall
    bool IsRotatingCW() const;  // GAMEMD 0x4C94B0  __thiscall
    bool IsRotatingCCW() const; // GAMEMD 0x4C94F0  __thiscall

    DirStruct    DesiredFacing; // +0x00
    DirStruct    StartFacing;   // +0x04
    CDTimerClass RotationTimer; // +0x08
    DirStruct    ROT;           // +0x14

    // Difference() = (short)DesiredFacing.Raw - (short)StartFacing.Raw,
    // truncated to 16 bits (MOV AX,[ECX]; SUB AX,[ECX+0x4]).
    short Difference() const
    {
        return (short)DesiredFacing.Raw - (short)StartFacing.Raw;
    }
};

GG_STATIC_ASSERT(offsetof(FacingClass, DesiredFacing) == 0x00);
GG_STATIC_ASSERT(offsetof(FacingClass, StartFacing)   == 0x04);
GG_STATIC_ASSERT(offsetof(FacingClass, RotationTimer) == 0x08);
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft)     == 0x08);
GG_STATIC_ASSERT(offsetof(FacingClass, ROT)           == 0x14);
GG_STATIC_ASSERT(sizeof(FacingClass)                  == 0x18);

#endif  // GG_MATCH_MOVEMENT_FACING_METHODS_H
