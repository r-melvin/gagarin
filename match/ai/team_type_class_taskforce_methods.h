// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6F1FA0: `[ESI+0xE4]` (the taskforce pointer),
//   `[ESI+0xEC]`, `[ESI+0xF0]`, `[ESI+0xF1]`, `[ESI+0xF6]` on the team type;
//   `[EAX+0x9C]` (entry count) and `[EAX+EBP]` with EBP starting at 0xA8 and
//   stepping by 8 (the per-entry type pointer) on the taskforce; `[EAX+0xCCE]`,
//   `[EAX+0x5E0]`, `[EAX+0x5B4]` on the techno type. The method name and the
//   entry pairing (amount, type) are cross-checked against YRpp.
#ifndef GG_MATCH_AI_TEAM_TYPE_CLASS_TASKFORCE_METHODS_H
#define GG_MATCH_AI_TEAM_TYPE_CLASS_TASKFORCE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// TechnoTypeClass (partial) — the three members the taskforce scan reads.
struct TechnoType_006F1FA0
{
    char _pad000[0x5B4];     // +0x0000
    int  At_5B4;             // +0x05B4  fed to 0x5889F0 together with the running value
    char _pad5B8[0x28];      // +0x05B8
    int  At_5E0;             // +0x05E0  zero => the type has no such capability
    char _pad5E4[0x6EA];     // +0x05E4
    char At_CCE;             // +0x0CCE  the type takes part in the scan
};
GG_STATIC_ASSERT(offsetof(TechnoType_006F1FA0, At_5B4) == 0x5B4);
GG_STATIC_ASSERT(offsetof(TechnoType_006F1FA0, At_5E0) == 0x5E0);
GG_STATIC_ASSERT(offsetof(TechnoType_006F1FA0, At_CCE) == 0xCCE);

// One taskforce entry: 8 bytes, the type pointer second.
struct TaskForceEntry_006F1FA0
{
    int                   Amount;   // +0x0000
    TechnoType_006F1FA0*  Type;     // +0x0004
};
GG_STATIC_ASSERT(sizeof(TaskForceEntry_006F1FA0) == 8);

// TaskForceClass (partial).
struct TaskForce_006F1FA0
{
    char _pad000[0x9C];                   // +0x0000
    int  CountEntries;                    // +0x009C
    char _pad0A0[0x4];                    // +0x00A0
    TaskForceEntry_006F1FA0 Entries[6];   // +0x00A4  (type pointer at +0xA8)
};
GG_STATIC_ASSERT(offsetof(TaskForce_006F1FA0, CountEntries) == 0x9C);
GG_STATIC_ASSERT(offsetof(TaskForce_006F1FA0, Entries) + offsetof(TaskForceEntry_006F1FA0, Type) == 0xA8);

// FUNCTION: GAMEMD 0x5889F0 (decl; reloc) — folds one type's +0x5B4 value into
// the running value. Two register arguments, nothing on the stack.
int __fastcall FUN_005889F0(int value, int running);

// TeamTypeClass (partial) — only the members ProcessTaskForce touches.
struct TeamTypeClass
{
    char _pad000[0xE4];               // +0x0000
    TaskForce_006F1FA0* TaskForce;    // +0x00E4
    char _pad0E8[0x4];                // +0x00E8
    int  At_EC;                       // +0x00EC  seeded with 9, folded per entry
    char At_F0;                       // +0x00F0
    char At_F1;                       // +0x00F1
    char _pad0F2[0x4];                // +0x00F2
    char At_F6;                       // +0x00F6  forces At_F0 clear

    // FUNCTION: GAMEMD 0x6F1FA0
    void ProcessTaskForce();
};
GG_STATIC_ASSERT(offsetof(TeamTypeClass, TaskForce) == 0xE4);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, At_EC) == 0xEC);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, At_F0) == 0xF0);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, At_F1) == 0xF1);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, At_F6) == 0xF6);

#endif  // GG_MATCH_AI_TEAM_TYPE_CLASS_TASKFORCE_METHODS_H
