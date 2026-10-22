// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x452540: the type at `[ESI+0x520]`
//   and its gate byte `[EAX+0x16B7]`, the current-mission slot
//   `[EDX+0x184]` compared with 0x18, the transition timer as
//   `LEA EDI,[ESI+0x350]` feeding CALLs 0x4A5130 / 0x4A51D0 / 0x4A51B0
//   (state-pair predicates over bytes +0x18/+0x19 of the timer), and the
//   mission slots `[EAX+0x1F0]` (one pushed -1), `[EDX+0x1E8]` (pushed 0x18,
//   0) and `[EAX+0x1EC]`. The tail from 0x452584 is 0x4525F0
//   (BuildingClass::IsTraversable) inlined. Names cross-checked against
//   YRpp BuildingClass::MakeTraversable / TransitionTimer::AreStates* /
//   MissionClass (re-derived here). The timer's size (0x20) is
//   the one already asserted in match/ui/transition_timer_more_methods.h.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_TRAVERSABLE_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_TRAVERSABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct TransitionTimer_00452540
{
    char _pad000[0x18];   // +0x0000  rate + action timer
    char State1;          // +0x0018
    char State2;          // +0x0019
    char _pad01A[6];      // +0x001A

    // FUNCTION: GAMEMD 0x4A5130 (decl; reloc) — State1 && !State2.
    bool AreStates10();
    // FUNCTION: GAMEMD 0x4A51B0 (decl; reloc) — !State1 && State2 == 1.
    bool AreStates01();
    // FUNCTION: GAMEMD 0x4A51D0 (decl; reloc) — !State1 && !State2.
    bool AreStates00();
};
GG_STATIC_ASSERT(offsetof(TransitionTimer_00452540, State1) == 0x18);
GG_STATIC_ASSERT(offsetof(TransitionTimer_00452540, State2) == 0x19);
GG_STATIC_ASSERT(sizeof(TransitionTimer_00452540) == 0x20);

struct Type_00452540
{
    char _pad000[0x16B7];   // +0x0000
    char Gate;              // +0x16B7  needs the gate opened before traversal
};
GG_STATIC_ASSERT(offsetof(Type_00452540, Gate) == 0x16B7);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_00452540;

struct BuildingClass_00452540
{
    Vtbl_00452540*            Vtbl;                    // +0x0000
    char                      _pad004[0x34C];          // +0x0004
    TransitionTimer_00452540  GateTimer;               // +0x0350
    char                      _pad370[0x520 - 0x370];  // +0x0370
    Type_00452540*            Type;                    // +0x0520

    // FUNCTION: GAMEMD 0x452540
    bool MakeTraversable();
    // FUNCTION: GAMEMD 0x4525F0 — BuildingClass::IsTraversable (inlined into
    // MakeTraversable; matched standalone in match/economy/building_class.cpp).
    bool IsTraversable();
};
GG_STATIC_ASSERT(offsetof(BuildingClass_00452540, GateTimer) == 0x350);
GG_STATIC_ASSERT(offsetof(BuildingClass_00452540, Type) == 0x520);

typedef int  (BuildingClass_00452540::*Fn184_00452540)();
typedef bool (BuildingClass_00452540::*Fn1E8_00452540)(int mission, bool start);
typedef bool (BuildingClass_00452540::*Fn1EC_00452540)();
typedef void (BuildingClass_00452540::*Fn1F0_00452540)(int mission);

struct Vtbl_00452540
{
    char            _pad000[0x184];          // +0x0000
    Fn184_00452540  GetCurrentMission;       // +0x0184
    char            _pad188[0x1E8 - 0x188];  // +0x0188
    Fn1E8_00452540  QueueMission;            // +0x01E8
    Fn1EC_00452540  NextMission;             // +0x01EC
    Fn1F0_00452540  ForceMission;            // +0x01F0
};
GG_STATIC_ASSERT(offsetof(Vtbl_00452540, GetCurrentMission) == 0x184);
GG_STATIC_ASSERT(offsetof(Vtbl_00452540, QueueMission) == 0x1E8);
GG_STATIC_ASSERT(offsetof(Vtbl_00452540, NextMission) == 0x1EC);
GG_STATIC_ASSERT(offsetof(Vtbl_00452540, ForceMission) == 0x1F0);

// Mission::Open — the gate-opening mission id compared and queued here.
#define MISSION_OPEN_00452540 0x18

// Inlined into MakeTraversable; kept in the header so cl can fold it.
inline bool BuildingClass_00452540::IsTraversable()
{
    if (!this->Type->Gate)
        return true;
    if ((this->*this->Vtbl->GetCurrentMission)() == MISSION_OPEN_00452540
        && this->GateTimer.AreStates01())
        return true;
    return false;
}

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_TRAVERSABLE_METHODS_H
