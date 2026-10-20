// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x41DB40.

#include "airstrike_class_clear_target_methods.h"

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
