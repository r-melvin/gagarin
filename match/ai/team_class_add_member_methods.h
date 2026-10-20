// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6EA500: on the team `[ESI+0x24]` (type),
//   `[ESI+0x34]`/`[ESI+0x38]` (handed by address to 0x6EAEE0), `[ESI+0x48]`,
//   `[ESI+0x4C]`, `[ESI+0x54]` (first member), `[ESI+0x70]` (trigger),
//   `[ESI+0x7D]`/`[ESI+0x7E]` (bytes) and the per-slot counters
//   `[ESI+EAX*4+0x88]`; on the member `[EDI+0x214]`, `byte [EDI+0x422]`,
//   `[EDI+0x5D4]` (owning team), `[EDI+0x5D8]` (next member),
//   `byte [EDI+0x689]`, and slots +0x84 (type, no args) and +0x2C0 (int, no
//   args); on the team type `byte [EAX+0xB3]` and `byte [EDX+0xF5]`; on the
//   techno type `[EAX+0x5E0]` (signed). Callees: 0x6EA610 (member fit test,
//   member/&slot/flag), 0x6EA870 (TeamClass::LiberateMember), 0x6F1870
//   (TeamTypeClass::GetGroup), 0x5F5B50 (ObjectClass::AttachTrigger),
//   0x6EAEE0 (two-pointer __thiscall). Method and callee names from YRpp
//   (consult-only, no LICENSE); each reconfirmed here.
#ifndef GG_MATCH_AI_TEAM_CLASS_ADD_MEMBER_METHODS_H
#define GG_MATCH_AI_TEAM_CLASS_ADD_MEMBER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// TechnoTypeClass (partial): only the signed count at +0x5E0.
struct TechnoType_006EA500
{
    char _pad000[0x5E0];              // +0x0000
    int  At_5E0;                      // +0x05E0
};
GG_STATIC_ASSERT(offsetof(TechnoType_006EA500, At_5E0) == 0x5E0);

// TeamTypeClass (partial).
struct TeamType_006EA500
{
    char _pad000[0xB3];               // +0x0000
    unsigned char At_B3;              // +0x00B3
    char _pad0B4[0xF5 - 0xB4];        // +0x00B4
    unsigned char At_F5;              // +0x00F5

    // FUNCTION: GAMEMD 0x6F1870 (decl; reloc) — TeamTypeClass::GetGroup.
    int GetGroup();
};
GG_STATIC_ASSERT(offsetof(TeamType_006EA500, At_B3) == 0xB3);
GG_STATIC_ASSERT(offsetof(TeamType_006EA500, At_F5) == 0xF5);

struct Team_006EA500;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct FootVtbl_006EA500;

// FootClass (partial): the team links plus two slots.
struct Foot_006EA500
{
    FootVtbl_006EA500* Vtbl;          // +0x0000
    char _pad004[0x214 - 0x004];      // +0x0004
    int  Group;                       // +0x0214
    char _pad218[0x422 - 0x218];      // +0x0218
    unsigned char At_422;             // +0x0422
    char _pad423[0x5D4 - 0x423];      // +0x0423
    Team_006EA500* Team;              // +0x05D4
    Foot_006EA500* NextTeamMember;    // +0x05D8
    char _pad5DC[0x689 - 0x5DC];      // +0x05DC
    unsigned char At_689;             // +0x0689

    // FUNCTION: GAMEMD 0x5F5B50 (decl; reloc) — ObjectClass::AttachTrigger.
    void AttachTrigger(void* trigger);
};
GG_STATIC_ASSERT(offsetof(Foot_006EA500, Group) == 0x214);
GG_STATIC_ASSERT(offsetof(Foot_006EA500, At_422) == 0x422);
GG_STATIC_ASSERT(offsetof(Foot_006EA500, Team) == 0x5D4);
GG_STATIC_ASSERT(offsetof(Foot_006EA500, NextTeamMember) == 0x5D8);
GG_STATIC_ASSERT(offsetof(Foot_006EA500, At_689) == 0x689);

typedef TechnoType_006EA500* (Foot_006EA500::*Fn84_006EA500)();
typedef int (Foot_006EA500::*Fn2C0_006EA500)();

struct FootVtbl_006EA500
{
    char _pad000[0x84];               // +0x0000
    Fn84_006EA500 GetTechnoType;      // +0x0084
    char _pad088[0x2C0 - 0x88];       // +0x0088
    Fn2C0_006EA500 At_2C0;            // +0x02C0
};
GG_STATIC_ASSERT(offsetof(FootVtbl_006EA500, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(FootVtbl_006EA500, At_2C0) == 0x2C0);

// TeamClass (partial).
struct Team_006EA500
{
    char _pad000[0x24];               // +0x0000
    TeamType_006EA500* Type;          // +0x0024
    char _pad028[0x34 - 0x28];        // +0x0028
    int  At_34;                       // +0x0034
    int  At_38;                       // +0x0038
    char _pad03C[0x48 - 0x3C];        // +0x003C
    int  TotalObjects;                // +0x0048
    int  TotalThreatValue;            // +0x004C
    char _pad050[0x54 - 0x50];        // +0x0050
    Foot_006EA500* FirstUnit;         // +0x0054
    char _pad058[0x70 - 0x58];        // +0x0058
    void* Trigger;                    // +0x0070
    char _pad074[0x7D - 0x74];        // +0x0074
    unsigned char At_7D;              // +0x007D
    unsigned char At_7E;              // +0x007E
    char _pad07F[0x88 - 0x7F];        // +0x007F
    int  CountObjects[1];             // +0x0088  per-task-force-slot counts

    // FUNCTION: GAMEMD 0x6EA610 (decl; reloc) — can the member join; the
    // task-force slot it fills comes back through `slot`.
    bool FUN_006EA610(Foot_006EA500* member, int* slot, bool flag);
    // FUNCTION: GAMEMD 0x6EA870 (decl; reloc) — TeamClass::LiberateMember.
    bool LiberateMember(Foot_006EA500* member, int slot, bool flag);
    // FUNCTION: GAMEMD 0x6EAEE0 (decl; reloc) — fill the two words at +0x34.
    void FUN_006EAEE0(int* a, int* b);

    // FUNCTION: GAMEMD 0x6EA500 — TeamClass::AddMember.
    bool AddMember(Foot_006EA500* member, bool flag);
};
GG_STATIC_ASSERT(offsetof(Team_006EA500, Type) == 0x24);
GG_STATIC_ASSERT(offsetof(Team_006EA500, At_34) == 0x34);
GG_STATIC_ASSERT(offsetof(Team_006EA500, At_38) == 0x38);
GG_STATIC_ASSERT(offsetof(Team_006EA500, TotalObjects) == 0x48);
GG_STATIC_ASSERT(offsetof(Team_006EA500, TotalThreatValue) == 0x4C);
GG_STATIC_ASSERT(offsetof(Team_006EA500, FirstUnit) == 0x54);
GG_STATIC_ASSERT(offsetof(Team_006EA500, Trigger) == 0x70);
GG_STATIC_ASSERT(offsetof(Team_006EA500, At_7D) == 0x7D);
GG_STATIC_ASSERT(offsetof(Team_006EA500, At_7E) == 0x7E);
GG_STATIC_ASSERT(offsetof(Team_006EA500, CountObjects) == 0x88);

#endif  // GG_MATCH_AI_TEAM_CLASS_ADD_MEMBER_METHODS_H
