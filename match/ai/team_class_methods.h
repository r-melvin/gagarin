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
class TeamClass
{
public:
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
