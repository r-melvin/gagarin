// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, vtable slots and callees read off the user's retail gamemd.exe
//   v1.001 (Ghidra disasm) at the annotated addresses. Team mission action
//   handlers (this = team, action record*, flag), siblings of the handlers in
//   team_mission_handlers_006eddc0.cpp. First member is at +0x54, the next
//   member link at +0x5D8, and the "action done" flag at +0x80.
//
// Address index:
//   0x6EA080  TeamClass::FUN_006EA080
//   0x6EC730  TeamClass::FUN_006EC730
//   0x6ECB50  TeamClass::FUN_006ECB50
//   0x6ECF10  TeamClass::FUN_006ECF10
//   0x6ECF50  TeamClass::FUN_006ECF50
//   0x6EDC70  TeamClass::FUN_006EDC70

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "team_class_methods.h"
#include "../_layout/map_0087f7e8.h"
#include "../_layout/script_class.h"

#include "team_class_r14_views.h"

// FUNCTION: GAMEMD 0x6ECF50
//
// PARTIAL: 84.8% -- identical instruction multiset; retail keeps the argument
// record in EBP and the vtable in EBX, VC6 swaps the two (variants tried:
// hoisted locals, for-loop, next-tested loop).
// Calls member slot 0x3D4 with a lookup keyed by the record's second field,
// for every member (next link read first).
void TeamClass::FUN_006ECF50(ActionArg_r14* a1, int a2)
{
    TeamMemberVtbl_r14* vt;
    TeamMember_r14* next;
    TeamMember_r14* m = (TeamMember_r14*)this->FirstUnit;
    if (m != 0) {
        do {
            next = m->Next;
            vt = m->Vtbl;
            (m->*vt->At_3D4)(((ObjList_r14_6502D30*)a1->unknown_04)->FUN_00502D30(1));
            m = next;
        } while (m != 0);
    }
    this->Done = true;
}

