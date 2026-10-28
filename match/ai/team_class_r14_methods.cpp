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

struct ActionArg_r14 {
    int unknown_00;
    int unknown_04;   // +0x04
};

struct TeamMemberVtbl_r14;

struct TeamMember_r14 {
    TeamMemberVtbl_r14* Vtbl;                 // +0x000
    char                _pad004[0x5D8 - 0x04];
    TeamMember_r14*     Next;                 // +0x5D8
    char                _pad5DC[0x689 - 0x5DC];
    bool                Flag689;              // +0x689
};
GG_STATIC_ASSERT(offsetof(TeamMember_r14, Next)    == 0x5D8);
GG_STATIC_ASSERT(offsetof(TeamMember_r14, Flag689) == 0x689);

struct TeamTarget_r14 {
    // FUNCTION: GAMEMD 0x691590 (decl; reloc)
    void FUN_00691590();
};

struct TeamMap_r14 {
    // FUNCTION: GAMEMD 0x580BC0 (decl; reloc)
    void* FUN_00580BC0(void* a1);
};
// GLOBAL: GAMEMD 0x87F7E8
extern TeamMap_r14 DAT_0087F7E8;

typedef void (TeamMember_r14::*Fn174_r14)(void* a1, int a2, int a3);
typedef void (TeamMember_r14::*Fn3D4_r14)(int a1);
typedef bool (TeamMember_r14::*Fn33C_r14)();
typedef void (TeamMember_r14::*Fn51C_r14)();
struct TeamMemberVtbl_r14 {
    char      _pad000[0x174];
    Fn174_r14 At_174;                         // +0x174
    char      _pad178[0x33C - 0x178];
    Fn33C_r14 At_33C;                         // +0x33C
    char      _pad340[0x3D4 - 0x340];
    Fn3D4_r14 At_3D4;                         // +0x3D4
    char      _pad3D8[0x51C - 0x3D8];
    Fn51C_r14 At_51C;                         // +0x51C
};
GG_STATIC_ASSERT(offsetof(TeamMemberVtbl_r14, At_174) == 0x174);
GG_STATIC_ASSERT(offsetof(TeamMemberVtbl_r14, At_33C) == 0x33C);
GG_STATIC_ASSERT(offsetof(TeamMemberVtbl_r14, At_3D4) == 0x3D4);
GG_STATIC_ASSERT(offsetof(TeamMemberVtbl_r14, At_51C) == 0x51C);

struct ObjList_r14_6502D30 {
    // FUNCTION: GAMEMD 0x502D30 (decl; reloc)
    int FUN_00502D30(int a1);
};

// GLOBAL: GAMEMD 0xB0E968 -- constant argument for member slot 0x174.
extern char DAT_00B0E968[];

// FUNCTION: GAMEMD 0x6EA080
//
// Restart the team's scripted action: raise the 7F and 78 flags, clear 7A,
// give every member the 689 flag when the 7B or 77 flag is up, refresh the
// target and mark the action done.
void TeamClass::FUN_006EA080()
{
    this->Flag7F = true;
    this->Flag78 = true;
    this->Flag7A = false;
    for (TeamMember_r14* m = (TeamMember_r14*)this->FirstUnit; m != 0; m = m->Next) {
        if (this->Flag7B || this->Flag77) {
            m->Flag689 = true;
        }
    }
    this->Target28->FUN_00691590();
    this->Done = true;
}

// FUNCTION: GAMEMD 0x6EC730
//
// With the flag set, retarget the team on the map entry for the current
// member (or the first member), then run the follow-up.
void TeamClass::FUN_006EC730(int a1, bool a2)
{
    if (a2) {
        TeamMember_r14* m = this->Member34;
        if (m == 0) {
            m = (TeamMember_r14*)this->FirstUnit;
        }
        AssignMissionTarget((AbstractClass*)DAT_0087F7E8.FUN_00580BC0(m));
    }
    FUN_006EBAD0();
}

// FUNCTION: GAMEMD 0x6ECB50
//
// Liberate every member whose slot 0x33C answers true; the next link is read
// before the call.
void TeamClass::FUN_006ECB50(int a1, int a2)
{
    for (TeamMember_r14* m = (TeamMember_r14*)this->FirstUnit; m != 0; ) {
        bool r = ((m->*m->Vtbl->At_33C)() != 0);
        TeamMember_r14* next = m->Next;
        if (r) {
            LiberateMember((FootClass*)m, -1, 1);
        }
        m = next;
    }
    this->Done = true;
}

// FUNCTION: GAMEMD 0x6ECF10
//
// Calls member slot 0x174 (constant block, 1, 0) for every member.
void TeamClass::FUN_006ECF10(int a1, int a2)
{
    for (TeamMember_r14* m = (TeamMember_r14*)this->FirstUnit; m != 0; m = m->Next) {
        (m->*m->Vtbl->At_174)(DAT_00B0E968, 1, 0);
    }
    this->Done = true;
}

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

// FUNCTION: GAMEMD 0x6EDC70
//
// Calls member slot 0x51C for every member.
void TeamClass::FUN_006EDC70(int a1, int a2)
{
    for (TeamMember_r14* m = (TeamMember_r14*)this->FirstUnit; m != 0; m = m->Next) {
        (m->*m->Vtbl->At_51C)();
    }
    this->Done = true;
}
