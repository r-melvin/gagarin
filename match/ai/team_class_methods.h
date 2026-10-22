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

struct AbstractClass;

// ---------------------------------------------------------------------------
// FootClass — minimal model. ScanLimit walks the team-member singly linked
// list (NextTeamMember @0x5D8), sets IsScanLimited @0x688, and fires the
// virtual at vtable byte-offset 0x3C8 (= slot 242) on each member.
//
// VC6 forbids the `__thiscall` keyword in a typedef/cast (C4234), so the only
// way to emit the retail `MOV EAX,[ESI]` / `CALL [EAX+0x3c8]` (a __thiscall
// memory-operand virtual dispatch) is a genuine C++ virtual call. We therefore
// give FootClass a real vtable, pad it with 242 dummy slots (0..241), and put
// the fired method (ScanLimitCallback) at slot 242 so its byte offset is 0x3C8.
// The padding virtuals are never defined/called — only the slot index matters.
// The compiler-inserted vptr occupies offset 0 (matching retail's real vptr),
// so the data pad starts at 4.
// ---------------------------------------------------------------------------

// 16 unique declared virtuals per macro expansion -> 16 vtable slots.
#define GG_VPAD16(p) \
    virtual void p##_0(); virtual void p##_1(); virtual void p##_2(); virtual void p##_3(); \
    virtual void p##_4(); virtual void p##_5(); virtual void p##_6(); virtual void p##_7(); \
    virtual void p##_8(); virtual void p##_9(); virtual void p##_a(); virtual void p##_b(); \
    virtual void p##_c(); virtual void p##_d(); virtual void p##_e(); virtual void p##_f();

struct FootClass
{
    // ---- vtable padding: slots 0..241 -----------------------------------
    GG_VPAD16(s00) GG_VPAD16(s01) GG_VPAD16(s02) GG_VPAD16(s03) GG_VPAD16(s04)
    GG_VPAD16(s05) GG_VPAD16(s06) GG_VPAD16(s07) GG_VPAD16(s08) GG_VPAD16(s09)
    GG_VPAD16(s10) GG_VPAD16(s11) GG_VPAD16(s12) GG_VPAD16(s13) GG_VPAD16(s14)
    virtual void pad_240();   // slot 240
    virtual void pad_241();   // slot 241
    // ---- the fired method: slot 242 -> byte offset 0x3C8 ----------------
    virtual void ScanLimitCallback(int arg);   // slot 242

    // ---- data members ---------------------------------------------------
    char            _pad_4[0x5D8 - 4];   // vptr@0 + TechnoClass-derived base (P2)
    FootClass*      NextTeamMember;      // +0x5D8
    char            _pad_5DC[0x688 - 0x5DC];
    unsigned char   IsScanLimited;       // +0x688
};
#undef GG_VPAD16

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(FootClass, NextTeamMember) == 0x5D8);
GG_STATIC_ASSERT(offsetof(FootClass, IsScanLimited)  == 0x688);
#endif

// ---------------------------------------------------------------------------
// TeamClass — minimal model. ScanLimit reads FirstUnit @0x54 and calls
// AssignMissionTarget (body-less, so cl emits a reloc-normalised direct call).
// FirstUnit @0x54 confirmed by `MOV ESI,[ESI+0x54]`. (No virtuals modelled on
// TeamClass: ScanLimit never dereferences this's vtable, and the real vptr
// space is already inside the 0x54 pad.)
// ---------------------------------------------------------------------------
struct TeamClass
{
    char            _pad_0[0x54];        // AbstractClass base + earlier members (P2)
    FootClass*      FirstUnit;           // +0x54

    // GAMEMD 0x6E9050 — clears/assigns the team's mission target.
    void AssignMissionTarget(AbstractClass* pTarget);

    // GAMEMD 0x6EC3A0 — flag every member as scan-limited (see .cpp).
    void ScanLimit();
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TeamClass, FirstUnit) == 0x54);
#endif

#endif // GG_MATCH_AI_TEAM_CLASS_METHODS_H
