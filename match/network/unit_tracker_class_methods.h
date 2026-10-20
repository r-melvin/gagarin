// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | TSpp-name-cross-check
//   Layout and every offset were read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI (the five methods below plus the
//   inlined constructor body at 0x748FD7). Method names are cross-checked
//   against TS++ src/utracker.h (Vinifera-Developers, GPL-3.0), corrected from
//   Westwood snake_case to RA2 camelCase (`Increment_Unit_Total` ->
//   `IncrementUnitTotal`, `Get_Total_Of_All` -> `GetTotalOfAll`).
//
// UnitTrackerClass — the per-house unit-production tally used for multiplayer
// end-game statistics.
//
// RA2 DIVERGES FROM TIBERIAN SUN HERE. TS's UnitTrackerClass holds a heap
// pointer (`long* UnitTotals; int UnitCount; int InNetworkFormat;`, 12 bytes).
// RA2 inlines the table into the object: 512 ints at +0x000..+0x7FC, then
// UnitCount at +0x800 and InNetworkFormat at +0x804, for sizeof 0x808. The
// binary proves it two ways:
//   * GetAllTotals @0x7490C0 is `MOV EAX,ECX; RET` — the totals base *is* the
//     object address, so there is no pointer to dereference.
//   * ClearUnitTotal @0x7490D0 reloads UnitCount from [ECX+0x800] on *every*
//     iteration (`MOV ESI,[ECX+0x800]` inside the loop) because the store
//     `UnitTotals[i] = 0` may alias it — only possible if both live in the same
//     object. GetTotalOfAll @0x7490A0, which stores nothing, keeps the count in
//     a register and counts down instead.
#ifndef GG_MATCH_NETWORK_UNIT_TRACKER_CLASS_METHODS_H
#define GG_MATCH_NETWORK_UNIT_TRACKER_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The table width the reset path stamps in before overwriting it with the
// caller's count (`MOV dword ptr [ECX+0x800],0x200` @0x749061).
#define UNIT_TRACKER_MAX_TYPES 0x200

struct UnitTrackerClass
{
    int UnitTotals[UNIT_TRACKER_MAX_TYPES];  // +0x0000  (INC [ECX+EAX*4] @0x74902E)
    int UnitCount;                           // +0x0800  (CMP [ECX+0x800]  @0x749024)
    int InNetworkFormat;                     // +0x0804  (cleared by the ctor @0x748FF5)

    // Declared ascending by retail address.
    void IncrementUnitTotal(int unitType);   // GAMEMD 0x749020
    void Init(int unitCount);                // GAMEMD 0x749060
    int  GetTotalOfAll();                    // GAMEMD 0x7490A0
    int* GetAllTotals();                     // GAMEMD 0x7490C0
    void ClearUnitTotal();                   // GAMEMD 0x7490D0
};

GG_STATIC_ASSERT(offsetof(UnitTrackerClass, UnitTotals)      == 0x000);
GG_STATIC_ASSERT(offsetof(UnitTrackerClass, UnitCount)       == 0x800);
GG_STATIC_ASSERT(offsetof(UnitTrackerClass, InNetworkFormat) == 0x804);
GG_STATIC_ASSERT(sizeof(UnitTrackerClass) == 0x808);

#endif  // GG_MATCH_NETWORK_UNIT_TRACKER_CLASS_METHODS_H
