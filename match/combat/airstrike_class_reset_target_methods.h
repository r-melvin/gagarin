// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x41DA20: on the airstrike `[EBP+0x30]` (the loop
//   bound), `byte [EBP+0x3D]` (set to 1), `[EBP+0x50]` (target, zeroed then
//   stored) and `[EBP+0x5C]` (first aircraft); on each aircraft `[EAX+0x2FC]`
//   (compared with the head's, later tested > 0) and `[ESI+0x5D8]` (next
//   team member) plus slots +0x3C8 (`PUSH EBX`) and +0x1E8 (`PUSH 0; PUSH
//   1`); on each target `[EDI+0x294]` (owning airstrike) plus slots +0x2C
//   (no args, compared with 6), +0x158 (no args), +0x15C (`PUSH 0x186A0`)
//   and +0x124 (`PUSH 2`); the sibling 0x41DB40 (ClearTarget) called with
//   `this`. Method name from YRpp AirstrikeClass.h (consult-only, no
//   LICENSE); layout re-derived here and shared with the ClearTarget TU.
#ifndef GG_MATCH_COMBAT_AIRSTRIKE_CLASS_RESET_TARGET_METHODS_H
#define GG_MATCH_COMBAT_AIRSTRIKE_CLASS_RESET_TARGET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Airstrike_0041DA20;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct FootVtbl_0041DA20;

// FootClass (partial): the aircraft on the strike.
struct Foot_0041DA20
{
    FootVtbl_0041DA20* Vtbl;          // +0x0000
    char _pad004[0x2FC - 0x004];      // +0x0004
    int  At_2FC;                      // +0x02FC
    char _pad300[0x5D8 - 0x300];      // +0x0300
    Foot_0041DA20* NextTeamMember;    // +0x05D8
};
GG_STATIC_ASSERT(offsetof(Foot_0041DA20, At_2FC) == 0x2FC);
GG_STATIC_ASSERT(offsetof(Foot_0041DA20, NextTeamMember) == 0x5D8);

typedef int (Foot_0041DA20::*Fn1E8_0041DA20)(int mission, int immediate);
typedef int (Foot_0041DA20::*Fn3C8_0041DA20)(void* target);

struct FootVtbl_0041DA20
{
    char _pad000[0x1E8];              // +0x0000
    Fn1E8_0041DA20 SetMission;        // +0x01E8
    char _pad1EC[0x3C8 - 0x1EC];      // +0x01EC
    Fn3C8_0041DA20 SetTarget;         // +0x03C8
};
GG_STATIC_ASSERT(offsetof(FootVtbl_0041DA20, SetMission) == 0x1E8);
GG_STATIC_ASSERT(offsetof(FootVtbl_0041DA20, SetTarget) == 0x3C8);

struct TargetVtbl_0041DA20;

// The strike's target (an ObjectClass; a BuildingClass when WhatAmI says 6):
// its airstrike link and the slots used here.
struct Target_0041DA20
{
    TargetVtbl_0041DA20* Vtbl;        // +0x0000
    char _pad004[0x294 - 0x004];      // +0x0004
    Airstrike_0041DA20* Airstrike;    // +0x0294
};
GG_STATIC_ASSERT(offsetof(Target_0041DA20, Airstrike) == 0x294);

typedef int (Target_0041DA20::*Fn2C_0041DA20)();
typedef int (Target_0041DA20::*Fn124_0041DA20)(int mark);
typedef int (Target_0041DA20::*Fn158_0041DA20)();
typedef int (Target_0041DA20::*Fn15C_0041DA20)(int duration);

struct TargetVtbl_0041DA20
{
    char _pad000[0x2C];               // +0x0000
    Fn2C_0041DA20  WhatAmI;           // +0x002C
    char _pad030[0x124 - 0x30];       // +0x0030
    Fn124_0041DA20 Mark;              // +0x0124
    char _pad128[0x158 - 0x128];      // +0x0128
    Fn158_0041DA20 At_158;            // +0x0158 — building: airstrike off.
    Fn15C_0041DA20 At_15C;            // +0x015C — building: airstrike on, timer.
};
GG_STATIC_ASSERT(offsetof(TargetVtbl_0041DA20, WhatAmI) == 0x2C);
GG_STATIC_ASSERT(offsetof(TargetVtbl_0041DA20, Mark) == 0x124);
GG_STATIC_ASSERT(offsetof(TargetVtbl_0041DA20, At_158) == 0x158);
GG_STATIC_ASSERT(offsetof(TargetVtbl_0041DA20, At_15C) == 0x15C);

// The target as a building, or null: `p ? (p->WhatAmI() == 6 ? p : 0) : 0`
// is what retail's `SUB 6; NEG; SBB; NOT; AND` selects.
inline Target_0041DA20* AsBuilding_0041DA20(Target_0041DA20* p)
{
    if (p == 0) {
        return 0;
    }
    return ((p->*p->Vtbl->WhatAmI)() == 6) ? p : 0;
}

struct Airstrike_0041DA20
{
    char _pad000[0x30];               // +0x0000
    int  At_30;                       // +0x0030 — aircraft count (loop bound).
    char _pad034[0x3D - 0x34];        // +0x0034
    unsigned char At_3D;              // +0x003D
    char _pad03E[0x50 - 0x3E];        // +0x003E
    Target_0041DA20* Target;          // +0x0050
    char _pad054[0x5C - 0x54];        // +0x0054
    Foot_0041DA20* FirstObject;       // +0x005C

    // FUNCTION: GAMEMD 0x41DA20 — AirstrikeClass::ResetTarget.
    void ResetTarget(Target_0041DA20* target);

    // FUNCTION: GAMEMD 0x41DB40 (decl; reloc) — AirstrikeClass::ClearTarget.
    void ClearTarget();
};
GG_STATIC_ASSERT(offsetof(Airstrike_0041DA20, At_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Airstrike_0041DA20, At_3D) == 0x3D);
GG_STATIC_ASSERT(offsetof(Airstrike_0041DA20, Target) == 0x50);
GG_STATIC_ASSERT(offsetof(Airstrike_0041DA20, FirstObject) == 0x5C);

#endif  // GG_MATCH_COMBAT_AIRSTRIKE_CLASS_RESET_TARGET_METHODS_H
