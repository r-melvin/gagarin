// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x6FB080: the techno's Ammo `[ESI+0x2FC]` and
//   its reload timer rewritten through `ADD ESI,0x1FC` as three dwords
//   (frame / an uninitialised stack dword / the duration); the type reached
//   through slot `[EAX+0x84]` (GetTechnoType) and read at `[EAX+0x684]`,
//   `[EAX+0x69C]`, `[EAX+0x3E4]`, `[EAX+0x6A0]` and `[EAX+0x698]`; 0xA8ED84 is
//   the frame counter. Member names are YRpp's (consult-only, no LICENSE);
//   every offset reconfirmed here and against match/_layout/techno_class.h /
//   techno_type_class.h (not included: this TU needs a timer with a ctor).
#ifndef GG_MATCH_COMBAT_TECHNO_CLASS_RELOADING_METHODS_H
#define GG_MATCH_COMBAT_TECHNO_CLASS_RELOADING_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
extern int DAT_00A8ED84;

// A frame-clocked countdown (YRpp CDTimerClass). The clock slot at +0x04 is
// never written by the constructor, which is exactly what retail shows: the
// temporary's middle dword is copied out of an uninitialised stack slot.
struct CDTimer_006FB080
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04
    int TimeLeft;     // +0x08

    explicit CDTimer_006FB080(int duration)
    {
        StartTime = DAT_00A8ED84;
        TimeLeft = duration;
    }
};
GG_STATIC_ASSERT(sizeof(CDTimer_006FB080) == 0xC);

// TechnoTypeClass (partial) — the five members StartReloading reads.
struct TechnoType_006FB080
{
    char _pad000[0x3E4];     // +0x0000
    int  PipWrap;            // +0x03E4
    char _pad3E8[0x29C];     // +0x03E8
    int  Ammo;               // +0x0684
    char _pad688[0x10];      // +0x0688
    int  Reload;             // +0x0698
    int  EmptyReload;        // +0x069C
    int  ReloadIncrement;    // +0x06A0
};
GG_STATIC_ASSERT(offsetof(TechnoType_006FB080, PipWrap) == 0x3E4);
GG_STATIC_ASSERT(offsetof(TechnoType_006FB080, Ammo) == 0x684);
GG_STATIC_ASSERT(offsetof(TechnoType_006FB080, Reload) == 0x698);
GG_STATIC_ASSERT(offsetof(TechnoType_006FB080, EmptyReload) == 0x69C);
GG_STATIC_ASSERT(offsetof(TechnoType_006FB080, ReloadIncrement) == 0x6A0);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_006FB080;

struct Techno_006FB080
{
    Vtbl_006FB080*    Vtbl;          // +0x0000
    char              _pad004[0x1F8];// +0x0004
    CDTimer_006FB080  ReloadTimer;   // +0x01FC
    char              _pad208[0xF4]; // +0x0208
    int               Ammo;          // +0x02FC

    // FUNCTION: GAMEMD 0x6FB080 — TechnoClass::StartReloading.
    void StartReloading();
};
GG_STATIC_ASSERT(offsetof(Techno_006FB080, ReloadTimer) == 0x1FC);
GG_STATIC_ASSERT(offsetof(Techno_006FB080, Ammo) == 0x2FC);

typedef TechnoType_006FB080* (Techno_006FB080::*Fn84_006FB080)();

struct Vtbl_006FB080
{
    char _pad000[0x84];        // +0x0000
    Fn84_006FB080 GetTechnoType; // +0x0084
};
GG_STATIC_ASSERT(offsetof(Vtbl_006FB080, GetTechnoType) == 0x84);

#endif  // GG_MATCH_COMBAT_TECHNO_CLASS_RELOADING_METHODS_H
