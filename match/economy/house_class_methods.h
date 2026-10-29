// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/bodies derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   (reconfirmed numerically here).
//
// Three tiny accessors grouped by subsystem (economy):
//   HouseClass::AcquiredThreatNode            @0x509130  (__thiscall)
//   HouseClass::IonSensitivesShouldBeOffline  @0x53A130  (__thiscall)
//   UnitTrackerClass::GetAllTotals                @0x7490C0  (__thiscall)
// (0x7490C0 is the UnitTrackerClass accessor that YRpp groups near HouseClass;
//  confirmed from disasm to be a plain `const int*` of `this`.)
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

#include "../_layout/house_class.h"
// ---------------------------------------------------------------------------
// HouseClass — only the single byte these two methods touch is modelled; the
// full HouseClass layout is P2. Confirmed from 0x509130
// (`MOV byte ptr [ECX+0x1fb], 1`): the HasThreatNode flag lives at +0x1FB.
// IonSensitivesShouldBeOffline (0x53A130) touches no member (returns false).
// ---------------------------------------------------------------------------


GG_STATIC_ASSERT(offsetof(HouseClass, HasThreatNode) == 0x1FB);

#include "../_layout/unit_tracker_class.h"

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_METHODS_H
