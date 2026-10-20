// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x5D8D10), cross-checked against
//   YRpp MPTeams.h (consult-only; reconfirmed here).
//
// MPTeam — one entry in the multiplayer "alliance team" list (Team:A/B/C/D in
// the frontend). A title string plus an index. AddToList pushes the entry into
// a Win32 combo/list box and stamps its item-data with the index.
#ifndef GG_MATCH_NETWORK_MPTEAMS_METHODS_H
#define GG_MATCH_NETWORK_MPTEAMS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// MPTeam. A vtable pointer occupies [0x00..0x03] (virtual dtor +
// IsTeamIncluded + SetPlayerTeam). Only the two data members below are touched
// by AddToList; both confirmed numerically from the disassembly and asserted.
struct MPTeam
{
    int AddToList(void* hWnd);            // GAMEMD 0x5D8D10 __thiscall

    void*    _vptr;                       // +0x00  vtable pointer
    wchar_t* Title;                       // +0x04  [ESI+0x4]
    int      Index;                       // +0x08  [ESI+0x8]
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(MPTeam, Title) == 0x4);
GG_STATIC_ASSERT(offsetof(MPTeam, Index) == 0x8);
#endif

#endif  // GG_MATCH_NETWORK_MPTEAMS_METHODS_H
