// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/convention derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x6EC3A0), cross-checked
//   against YRpp (every
//   offset/slot reconfirmed below from the disassembly).
//
// TeamClass — an AI strike team. Only the members ScanLimit touches are
// modelled; the full AbstractClass-derived TeamClass layout is P2.
#ifndef GG_MATCH_AI_TEAM_CLASS_METHODS_H
#define GG_MATCH_AI_TEAM_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/foot_class.h"   // NextTeamMember @0x5D8, IsScanLimited @0x688, slot 242


// ---------------------------------------------------------------------------
// TeamClass — minimal model. ScanLimit reads FirstUnit @0x54 and calls
// AssignMissionTarget (body-less, so cl emits a reloc-normalised direct call).
// FirstUnit @0x54 confirmed by `MOV ESI,[ESI+0x54]`. (No virtuals modelled on
// TeamClass: ScanLimit never dereferences this's vtable, and the real vptr
// space is already inside the 0x54 pad.)
// ---------------------------------------------------------------------------
struct TeamTarget_r14;
struct TeamMember_r14;
struct ActionArg_r14;

class TeamClass
{
public:
    char            _pad_0[0x28];        // AbstractClass base + earlier members (P2)
    TeamTarget_r14* Target28;            // +0x28
    char            _pad_2C[0x34 - 0x2C];
    TeamMember_r14* Member34;            // +0x34
    char            _pad_38[0x54 - 0x38];
    FootClass*      FirstUnit;           // +0x54
    char            _pad_58[0x77 - 0x58];
    bool            Flag77;              // +0x77
    bool            Flag78;              // +0x78
    char            _pad_79;
    bool            Flag7A;              // +0x7A
    bool            Flag7B;              // +0x7B
    char            _pad_7C[0x7F - 0x7C];
    bool            Flag7F;              // +0x7F
    bool            Done;                // +0x80

    // GAMEMD 0x6E9050 — clears/assigns the team's mission target.
    void AssignMissionTarget(AbstractClass* pTarget);

    // GAMEMD 0x6EC3A0 — flag every member as scan-limited (see .cpp).
    void ScanLimit();

    // FUNCTION: GAMEMD 0x6EA870 (decl; reloc) -- TeamClass::LiberateMember.
    void LiberateMember(FootClass* foot, int idx, unsigned char count);
    // FUNCTION: GAMEMD 0x6EBAD0 (decl; reloc)
    void FUN_006EBAD0();
    // FUNCTION: GAMEMD 0x6EA080
    void FUN_006EA080();
    // FUNCTION: GAMEMD 0x6EC730
    void FUN_006EC730(int a1, bool a2);
    // FUNCTION: GAMEMD 0x6ECB50
    void FUN_006ECB50(int a1, int a2);
    // FUNCTION: GAMEMD 0x6ECF10
    void FUN_006ECF10(int a1, int a2);
    // FUNCTION: GAMEMD 0x6ECF50
    void FUN_006ECF50(ActionArg_r14* a1, int a2);
    // FUNCTION: GAMEMD 0x6EDC70
    void FUN_006EDC70(int a1, int a2);
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TeamClass, Target28) == 0x28);
GG_STATIC_ASSERT(offsetof(TeamClass, Member34) == 0x34);
GG_STATIC_ASSERT(offsetof(TeamClass, FirstUnit) == 0x54);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag77)   == 0x77);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag78)   == 0x78);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag7A)   == 0x7A);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag7B)   == 0x7B);
GG_STATIC_ASSERT(offsetof(TeamClass, Flag7F)   == 0x7F);
GG_STATIC_ASSERT(offsetof(TeamClass, Done)     == 0x80);
#endif

#endif // GG_MATCH_AI_TEAM_CLASS_METHODS_H
