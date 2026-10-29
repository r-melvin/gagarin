// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x6339B0). Names cross-checked
//   against YRpp (every
//   offset reconfirmed numerically below from the matched body).
//
// This TU matches one TechnoClass query helper:
//   * GetControllingHouse — returns the controlling house's ArrayIndex. The
//     Owner's index normally, but when the Owner is the local human player the
//     CurrentPlayer's index is substituted (the "replace ID with player's ID"
//     behaviour documented in YRpp).
// Confirmed offsets (from GetControllingHouse @0x6339B0):
//   * TechnoClass::Owner            +0x21C  `MOV ECX,[ECX+0x21C]` — matches spine
//   * HouseClass::ArrayIndex        +0x030  `MOV ESI,[ECX+0x30]` / `MOV EAX,[EAX+0x30]`
//   * HouseClass::CurrentPlayer     global  `[0x00A83D4C]`
//   * HouseClass::IsControlledByCurrentPlayer  CALL 0x50B6F0 (__thiscall, not matched here)
#ifndef GG_MATCH_CORE_TECHNO_CLASS_HOUSE_H
#define GG_MATCH_CORE_TECHNO_CLASS_HOUSE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#ifndef NULL
#define NULL 0
#endif

// ---------------------------------------------------------------------------
// HouseClass — minimal offset-pinned model. ArrayIndex is the first member of
// HouseClass after its 0x30-byte AbstractClass base. IsControlledByCurrentPlayer
// (retail 0x50B6F0) is declared-only so cl emits a reloc-normalised CALL.
// ---------------------------------------------------------------------------
#include "../_layout/house_class.h"

// GLOBAL: GAMEMD 0xA83D4C -- the local player's house.
extern HouseClass* CurrentPlayer;


GG_STATIC_ASSERT(offsetof(HouseClass, ArrayIndex) == 0x30);

// ---------------------------------------------------------------------------
// TechnoClass — minimal offset-pinned model for the matched helper. The pad gap
// stands in for the full RadioClass/MissionClass/ObjectClass/TechnoClass spine
// (see match/_layout/techno_class.h); only the touched member is named.
// ---------------------------------------------------------------------------
#include "../_layout/techno_class.h"


GG_STATIC_ASSERT(offsetof(TechnoClass, Owner) == 0x21C);

#endif  // GG_MATCH_CORE_TECHNO_CLASS_HOUSE_H
