// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/bodies derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   (reconfirmed numerically here).
//
// Three tiny accessors grouped by subsystem (economy):
//   HouseClass::AcquiredThreatNode            @0x509130  (__thiscall)
//   HouseClass::IonSensitivesShouldBeOffline  @0x53A130  (__thiscall)
//   UnitTrackerClass::GetArray                @0x7490C0  (__thiscall)
// (0x7490C0 is the UnitTrackerClass accessor that YRpp groups near HouseClass;
//  confirmed from disasm to be a plain `const int*` of `this`.)
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// HouseClass — only the single byte these two methods touch is modelled; the
// full HouseClass layout is P2. Confirmed from 0x509130
// (`MOV byte ptr [ECX+0x1fb], 1`): the HasThreatNode flag lives at +0x1FB.
// IonSensitivesShouldBeOffline (0x53A130) touches no member (returns false).
// ---------------------------------------------------------------------------
class HouseClass
{
public:
    void AcquiredThreatNode();                       // GAMEMD 0x509130 __thiscall
    bool IonSensitivesShouldBeOffline() const;       // GAMEMD 0x53A130 __thiscall

    char unknown_base[0x1FB];   // +0x000 .. +0x1FA  (P2 layout)
    bool HasThreatNode;         // +0x1FB
};

GG_STATIC_ASSERT(offsetof(HouseClass, HasThreatNode) == 0x1FB);

// ---------------------------------------------------------------------------
// UnitTrackerClass — GetArray returns `const int*` to the head of the unit
// totals table. Confirmed from 0x7490C0 (`MOV EAX,ECX; RET`): the returned
// pointer IS `this`, i.e. &UnitTotals[0] at offset 0. YRpp UnitTrackerClass.
// ---------------------------------------------------------------------------
struct UnitTrackerClass
{
    const int* GetArray();                           // GAMEMD 0x7490C0 __thiscall

    int  UnitTotals[0x200];     // +0x000
    int  UnitCount;             // +0x800
    int  InNetworkFormat;       // +0x804  (BOOL)
};

GG_STATIC_ASSERT(offsetof(UnitTrackerClass, UnitTotals) == 0x000);
GG_STATIC_ASSERT(offsetof(UnitTrackerClass, UnitCount)  == 0x800);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_METHODS_H
