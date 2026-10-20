// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x41DB40: on the airstrike `byte [EBP+0x3D]`,
//   `[EBP+0x50]` (target) and `[EBP+0x5C]` (first aircraft); on each aircraft
//   `[EAX+0x2FC]` (cleared) and `[ESI+0x5D8]` (next team member) plus slots
//   +0x1E8 (`PUSH 0; PUSH 4`), +0x3C8 (`PUSH 0`) and +0x480 (`PUSH 1; PUSH 0`);
//   on the target `[ESI+0x294]` (owning airstrike) plus slots +0x2C (no args,
//   compared with 6) and +0x124 (`PUSH 2`); the airstrike registry Items
//   `[0x889FBC]` and Count `[0x889FC8]` (the vector at 0x889FB8); the active
//   byte `[0xA8E9A0]`. Method name and the registry/active names are YRpp's
//   (consult-only, no LICENSE); each reconfirmed here.
#ifndef GG_MATCH_COMBAT_AIRSTRIKE_CLASS_CLEAR_TARGET_METHODS_H
#define GG_MATCH_COMBAT_AIRSTRIKE_CLASS_CLEAR_TARGET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// GLOBAL: GAMEMD 0xA8E9A0 — Unsorted::IsActive (byte).
extern unsigned char DAT_00A8E9A0;

struct Airstrike_0041DB40;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct FootVtbl_0041DB40;

// FootClass (partial): the aircraft on the strike.
struct Foot_0041DB40
{
    FootVtbl_0041DB40* Vtbl;          // +0x0000
    char _pad004[0x2FC - 0x004];      // +0x0004
    int  At_2FC;                      // +0x02FC
    char _pad300[0x5D8 - 0x300];      // +0x0300
    Foot_0041DB40* NextTeamMember;    // +0x05D8
};
GG_STATIC_ASSERT(offsetof(Foot_0041DB40, At_2FC) == 0x2FC);
GG_STATIC_ASSERT(offsetof(Foot_0041DB40, NextTeamMember) == 0x5D8);

typedef int (Foot_0041DB40::*Fn1E8_0041DB40)(int mission, int immediate);
typedef int (Foot_0041DB40::*Fn3C8_0041DB40)(void* target);
typedef int (Foot_0041DB40::*Fn480_0041DB40)(void* target, int flag);

struct FootVtbl_0041DB40
{
    char _pad000[0x1E8];              // +0x0000
    Fn1E8_0041DB40 SetMission;        // +0x01E8
    char _pad1EC[0x3C8 - 0x1EC];      // +0x01EC
    Fn3C8_0041DB40 SetTarget;         // +0x03C8
    char _pad3CC[0x480 - 0x3CC];      // +0x03CC
    Fn480_0041DB40 SetDestination;    // +0x0480
};
GG_STATIC_ASSERT(offsetof(FootVtbl_0041DB40, SetMission) == 0x1E8);
GG_STATIC_ASSERT(offsetof(FootVtbl_0041DB40, SetTarget) == 0x3C8);
GG_STATIC_ASSERT(offsetof(FootVtbl_0041DB40, SetDestination) == 0x480);

struct TargetVtbl_0041DB40;

// The strike's target (a TechnoClass): its airstrike link and two slots.
struct Target_0041DB40
{
    TargetVtbl_0041DB40* Vtbl;        // +0x0000
    char _pad004[0x294 - 0x004];      // +0x0004
    Airstrike_0041DB40* Airstrike;    // +0x0294
};
GG_STATIC_ASSERT(offsetof(Target_0041DB40, Airstrike) == 0x294);

typedef int (Target_0041DB40::*Fn2C_0041DB40)();
typedef int (Target_0041DB40::*Fn124_0041DB40)(int mark);

struct TargetVtbl_0041DB40
{
    char _pad000[0x2C];               // +0x0000
    Fn2C_0041DB40 WhatAmI;            // +0x002C
    char _pad030[0x124 - 0x30];       // +0x0030
    Fn124_0041DB40 Mark;              // +0x0124
};
GG_STATIC_ASSERT(offsetof(TargetVtbl_0041DB40, WhatAmI) == 0x2C);
GG_STATIC_ASSERT(offsetof(TargetVtbl_0041DB40, Mark) == 0x124);

struct Airstrike_0041DB40
{
    char _pad000[0x3D];               // +0x0000
    unsigned char At_3D;              // +0x003D
    char _pad03E[0x50 - 0x3E];        // +0x003E
    Target_0041DB40* Target;          // +0x0050
    char _pad054[0x5C - 0x54];        // +0x0054
    Foot_0041DB40* FirstObject;       // +0x005C

    // FUNCTION: GAMEMD 0x41DB40 — AirstrikeClass::ClearTarget.
    void ClearTarget();
};
GG_STATIC_ASSERT(offsetof(Airstrike_0041DB40, At_3D) == 0x3D);
GG_STATIC_ASSERT(offsetof(Airstrike_0041DB40, Target) == 0x50);
GG_STATIC_ASSERT(offsetof(Airstrike_0041DB40, FirstObject) == 0x5C);

// AirstrikeClass::Array — the registry vector at 0x889FB8; only Items (+0x04)
// and Count (+0x10) are read.
struct AirstrikeVec_0041DB40
{
    void* Vptr;                       // +0x0000  (0x889FB8)
    Airstrike_0041DB40** Items;       // +0x0004  (0x889FBC)
    int  Capacity;                    // +0x0008  (0x889FC0)
    char IsValid;                     // +0x000C  (0x889FC4)
    char IsAllocated;                 // +0x000D  (0x889FC5)
    char _pad00E[2];                  // +0x000E
    int  Count;                       // +0x0010  (0x889FC8)
};
GG_STATIC_ASSERT(offsetof(AirstrikeVec_0041DB40, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(AirstrikeVec_0041DB40, Count) == 0x10);
// GLOBAL: GAMEMD 0x889FB8 — AirstrikeClass::Array.
extern AirstrikeVec_0041DB40 DAT_00889FB8;

#endif  // GG_MATCH_COMBAT_AIRSTRIKE_CLASS_CLEAR_TARGET_METHODS_H
