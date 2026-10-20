// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x629720: on this `[ESI+0x28]` Victim (whose
//   PrimaryFacing at +0x388 receives FacingClass::Current @0x4C93D0, the
//   DirStruct coming back through a hidden pointer read as one dword),
//   `[ESI+0x44]` GrappleAnim, `[ESI+0x48]` GrappleState, `[ESI+0x4C]`
//   GrappleAnimFrame and `[ESI+0x50]` GrappleAnimDelay; on the anim
//   `[EAX+0xAC]` (the frame index), the timer rewrite at `[ECX+0xB4]` /
//   `[EBP+4]` / `[EBP+8]` storing frame / an uninitialised stack dword /
//   0x80, and `[ECX+0xC0]` = 0x80; 0xA8ED84 is the frame counter. Names
//   cross-checked against YRpp ParasiteClass.h / AnimClass.h (consult-only;
//   every offset reconfirmed above). Victim @0x28 and the parasite's Owner
//   @0x24 agree with match/combat/parasite_class_infect_methods.h.
#ifndef GG_MATCH_COMBAT_PARASITE_CLASS_GRAPPLE_METHODS_H
#define GG_MATCH_COMBAT_PARASITE_CLASS_GRAPPLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
extern int DAT_00A8ED84;

// A frame-clocked countdown (YRpp CDTimerClass). The clock slot at +0x04 is
// never written by the constructor, which is exactly what retail shows: the
// temporary's middle dword is copied out of an uninitialised stack slot.
struct CDTimer_00629720
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04
    int TimeLeft;     // +0x08

    explicit CDTimer_00629720(int duration)
    {
        StartTime = DAT_00A8ED84;
        TimeLeft = duration;
    }
};
GG_STATIC_ASSERT(offsetof(CDTimer_00629720, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimer_00629720) == 0x0C);

// A binary-angle direction. The user-declared constructor is what makes VC6
// return it through a hidden pointer (a POD of this size would come back in
// EAX); retail reads the whole dword off that pointer.
struct Dir_00629720
{
    unsigned int Raw;   // +0x00
    Dir_00629720() {}
};
GG_STATIC_ASSERT(sizeof(Dir_00629720) == 4);

// FacingClass (0x18) — opaque here; only Current() is called.
struct Facing_00629720
{
    char opaque[0x18];

    // FUNCTION: GAMEMD 0x4C93D0 (decl; reloc) — FacingClass::Current.
    Dir_00629720 Current();
};
GG_STATIC_ASSERT(sizeof(Facing_00629720) == 0x18);

// The grappled FootClass: only PrimaryFacing @0x388 is touched.
struct Foot_00629720
{
    char             _pad000[0x388];   // +0x0000
    Facing_00629720  PrimaryFacing;    // +0x0388
};
GG_STATIC_ASSERT(offsetof(Foot_00629720, PrimaryFacing) == 0x388);

// AnimClass — the three members the grapple animation rewrite touches.
struct Anim_00629720
{
    char              _pad000[0xAC];   // +0x0000
    int               At_AC;           // +0x00AC  current frame index
    char              _pad0B0[0x4];    // +0x00B0
    CDTimer_00629720  Timer;           // +0x00B4  frame timer
    int               At_C0;           // +0x00C0  frame rate
};
GG_STATIC_ASSERT(offsetof(Anim_00629720, At_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(Anim_00629720, Timer) == 0xB4);
GG_STATIC_ASSERT(offsetof(Anim_00629720, At_C0) == 0xC0);

struct ParasiteClass_00629720
{
    char             _pad000[0x28];        // +0x0000
    Foot_00629720*   Victim;               // +0x0028
    char             _pad02C[0x44 - 0x2C]; // +0x002C
    Anim_00629720*   GrappleAnim;          // +0x0044
    int              GrappleState;         // +0x0048
    int              GrappleAnimFrame;     // +0x004C
    int              GrappleAnimDelay;     // +0x0050

    // FUNCTION: GAMEMD 0x629720
    bool UpdateGrapple();
};
GG_STATIC_ASSERT(offsetof(ParasiteClass_00629720, Victim)           == 0x28);
GG_STATIC_ASSERT(offsetof(ParasiteClass_00629720, GrappleAnim)      == 0x44);
GG_STATIC_ASSERT(offsetof(ParasiteClass_00629720, GrappleState)     == 0x48);
GG_STATIC_ASSERT(offsetof(ParasiteClass_00629720, GrappleAnimFrame) == 0x4C);
GG_STATIC_ASSERT(offsetof(ParasiteClass_00629720, GrappleAnimDelay) == 0x50);

#endif  // GG_MATCH_COMBAT_PARASITE_CLASS_GRAPPLE_METHODS_H
