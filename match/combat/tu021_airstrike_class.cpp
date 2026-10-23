// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU021 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x41d070-0x41e15f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail RTTI TypeDescriptors 0x818058 and 0x818088 identify
// VectorClass<AirstrikeClass*> and DynamicVectorClass<AirstrikeClass*>;
// the latter's CHD names the former as its zero-offset base.
// Full entry-origin spans bind these methods; no original TU or standalone
// constructor is claimed. No GX matches the full derived deleting body.
//
//   0x41D7E0.

#include "../core/vector_class_operations.h"
class AirstrikeClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// VTABLE: GAMEMD 0x7E295C -- VectorClass<AirstrikeClass*>.
template class VectorClass<AirstrikeClass*>;
// VTABLE: GAMEMD 0x7E293C -- DynamicVectorClass<AirstrikeClass*>.
template class DynamicVectorClass<AirstrikeClass*>;

typedef VectorClass<AirstrikeClass*> GgAirstrikeVector;
typedef DynamicVectorClass<AirstrikeClass*> GgAirstrikeDynamicVector;
GG_STATIC_ASSERT(sizeof(AirstrikeClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgAirstrikeVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAirstrikeVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAirstrikeVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAirstrikeVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAirstrikeVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAirstrikeVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgAirstrikeDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAirstrikeDynamicVector, CapacityIncrement) == 0x14);

#include "../ai/queue_unlink_methods.h"

#include "airstrike_class_clear_target_methods.h"

#include "airstrike_class_methods.h"

#include "airstrike_class_reset_target_methods.h"

#include "../core/small_misc47_methods.h"

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x41D7E0
bool Obj_0041D7E0::FUN_0041D7E0(int candidate)
{
    int delay = FUN_00750010(Subject + 0x150) ? DelayB : DelayA;

    if (!Suppressed) {
        if (Start + delay <= CurrentFrame) {
            return true;
        }
    }

    bool changed = candidate != Target;

    return changed;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x41D830  AirstrikeClass::StartMission (__thiscall, ret 0x4)
// A fresh airstrike starts its run; one already in progress only re-targets, and
// only when the target actually changed. Retail hoists the argument load between
// the flag TEST and its JNZ, which is what putting the flag test first produces.
void AirstrikeClass::StartMission(ObjectClass* target)
{
    if (!unknown_3C) {
        BeginMission(target);
        return;
    }

    if (target != Target)
        ResetTarget(target);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x41DA20
//
// Point the strike at a new target. If the aircraft on the strike do not
// all agree on their +0x2FC link with the head aircraft, the strike is
// cleared instead. Otherwise a building that was the old target is told
// the strike is off and redrawn, a building that is the new target is
// linked to this strike, told it is on for 100000 frames and redrawn, and
// every aircraft whose link is positive is retargeted and sent to mission
// 1, which flags the strike as engaged.
void Airstrike_0041DA20::ResetTarget(Target_0041DA20* target)
{
    Foot_0041DA20* first = this->FirstObject;
    if (first != 0) {
        Foot_0041DA20* foot = first->NextTeamMember;
        while (foot != 0) {
            if (foot->At_2FC != first->At_2FC) {
                this->ClearTarget();
                return;
            }
            foot = foot->NextTeamMember;
        }
    }

    Target_0041DA20* oldBuilding = AsBuilding_0041DA20(this->Target);
    Target_0041DA20* newBuilding = AsBuilding_0041DA20(target);

    if (oldBuilding != 0) {
        oldBuilding->Airstrike = 0;
        (oldBuilding->*oldBuilding->Vtbl->At_158)();
        (oldBuilding->*oldBuilding->Vtbl->Mark)(2);
    }
    this->Target = 0;
    if (newBuilding != 0) {
        newBuilding->Airstrike = this;
        (newBuilding->*newBuilding->Vtbl->At_15C)(100000);
        (newBuilding->*newBuilding->Vtbl->Mark)(2);
    }

    Foot_0041DA20* foot = this->FirstObject;
    this->Target = target;
    for (int i = 0; i < this->At_30; i++) {
        if (foot != 0) {
            if (foot->At_2FC > 0) {
                (foot->*foot->Vtbl->SetTarget)(target);
                (foot->*foot->Vtbl->SetMission)(1, 0);
                this->At_3D = 1;
            }
            foot = foot->NextTeamMember;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x41DB40
//
// Drop the strike's target. Only while the game is active: if any aircraft on
// the strike has already lost its +0x2FC link, every aircraft's link is cleared;
// then each aircraft (at most 0x65 of them) is sent to mission 4 with no target
// and no destination. The target itself, if it is a building still pointing at
// this strike, is handed to whichever other strike in the registry targets it
// (redrawn when none does), and its link is cleared if it still names this
// strike. Finally the target pointer is dropped.
//
// Phrasing that matters: the clearing pass re-reads `this->FirstObject`
// rather than reusing a `first` local. VC6 CSEs the reload with the head load
// above (no store or call sits between them), but it then does not carry the
// non-null fact from the first loop's entry test onto the second loop, which
// is what keeps retail's `MOV EAX,ECX; CMP EAX,EBX; JZ` at both entries; a
// shared `first` local lets VC6 test ECX directly and fold the second test
// (14.6%).
void Airstrike_0041DB40::ClearTarget()
{
    if (DAT_00A8E9A0 != 0) {
        Foot_0041DB40* foot = this->FirstObject;
        while (foot != 0) {
            if (foot->At_2FC == 0) {
                if (foot != 0) {
                    Foot_0041DB40* p = this->FirstObject;
                    while (p != 0) {
                        p->At_2FC = 0;
                        p = p->NextTeamMember;
                    }
                }
                break;
            }
            foot = foot->NextTeamMember;
        }

        int steps = 0;
        foot = this->FirstObject;
        while (foot != 0) {
            (foot->*foot->Vtbl->SetMission)(4, 0);
            (foot->*foot->Vtbl->SetTarget)(0);
            (foot->*foot->Vtbl->SetDestination)(0, 1);
            foot = foot->NextTeamMember;
            steps++;
            if (steps > 0x64) {
                break;
            }
        }

        Target_0041DB40* target = this->Target;
        this->At_3D = 0;
        if (target != 0
            && (target->*target->Vtbl->WhatAmI)() == 6
            && target->Airstrike == this) {
            Airstrike_0041DB40* other = 0;
            for (int i = 0; i < DAT_00889FB8.Count; i++) {
                Airstrike_0041DB40* a = DAT_00889FB8.Items[i];
                if (a != this && a->Target == target) {
                    other = a;
                }
            }
            target->Airstrike = other;
            if (other == 0 && DAT_00A8E9A0 != 0) {
                (target->*target->Vtbl->Mark)(2);
            }
            if (target->Airstrike == this) {
                target->Airstrike = 0;
            }
        }

        this->Target = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x41DC80
//
// Unlink a node from a singly-linked queue. The head is a special case; anything
// else is found by walking, and the walk is capped at 0x65 steps so a corrupt
// list cannot spin forever.
//
// After a successful unlink the cursor is set to null rather than advanced, which
// ends the walk immediately — the node can only be in the list once, so there is
// nothing left to find. That is written as an explicit `else` on the advance
// rather than by zeroing the lookahead: retail zeroes the cursor in the match
// branch and jumps over the advance (0x41DCDF/0x41DCE1), where zeroing the
// lookahead lets VC6 merge both paths into one unconditional advance.
//
// The cap is written `steps <= 0x64`, not `steps < 0x65`: retail compares
// against 0x64 with `JG`, and the other spelling gives `CMP 0x65; JGE`.
//
// MATCHED 100% (47/47). The residual was an adjacent store/load swap in the
// idle-stamp block, not a register choice: both builds load the counter into
// EDX, but retail issues that load *before* the first flag-byte store and cl
// issued it between the two. Writing the stamp store first in the source is
// what fixes it — the two flag bytes then follow, and cl schedules the byte
// stores around the load exactly as retail does. (The earlier note here read
// the delta as an EAX-vs-EDX encoding choice; that reading was wrong.)
// Measured in one compile against this address: the stamp store first 100%,
// the stamp between the flag stores 95.7%, the stamp read through a local
// 93.6%, through a volatile local 93.6%, volatile flag-byte stores 95.7%, and
// a volatile stamp store 95.7%.
//
// Emptying the queue stamps the frame counter and clears the two flag bytes, so
// a caller can tell how long it has been idle.
void Owner_0041DC80::FUN_0041DC80(Node_0041DC80* node)
{
    int zero = 0;
    int steps = 0;
    Node_0041DC80* cursor = this->Head;

    if (cursor == node) {
        this->Head = node->Next;
        node->Next = 0;
        this->Active = this->Active - 1;
        node->At_294 = zero;
    } else {
        do {
            if (cursor == (Node_0041DC80*)zero) {
                break;
            }

            Node_0041DC80* next = cursor->Next;
            if (next == node) {
                cursor->Next = node->Next;
                node->Next = 0;
                cursor = 0;
                this->Active = this->Active - 1;
                node->At_294 = zero;
            } else {
                cursor = next;
            }

            steps++;
        } while (steps <= 0x64);
    }

    if (this->Active <= zero) {
        this->field_40 = CurrentFrame;
        this->field_3C = (char)zero;
        this->field_3D = (char)zero;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x41DDE0
// DynamicVectorClass<AirstrikeClass*>::Clear
// FUNCTION: GAMEMD 0x41DE10
// DynamicVectorClass<AirstrikeClass*>::Slot5
// FUNCTION: GAMEMD 0x41DE30
// VectorClass<AirstrikeClass*>::Slot6
// FUNCTION: GAMEMD 0x41DE40
// VectorClass<AirstrikeClass*>::operator==
// FUNCTION: GAMEMD 0x41DE80
// VectorClass<AirstrikeClass*>::SetCapacity
// FUNCTION: GAMEMD 0x41DF30
// VectorClass<AirstrikeClass*>::Clear
// FUNCTION: GAMEMD 0x41DF60
// VectorClass<AirstrikeClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x41DFA0
// VectorClass<AirstrikeClass*>::Slot5
// FUNCTION: GAMEMD 0x41DFC0
// DynamicVectorClass<AirstrikeClass*>::SetCapacity
// FUNCTION: GAMEMD 0x41E070
// DynamicVectorClass<AirstrikeClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x41E0A0
// VectorClass<AirstrikeClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x41E0F0
// DynamicVectorClass<AirstrikeClass*>::scalar deleting destructor
