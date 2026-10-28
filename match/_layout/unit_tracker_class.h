// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Native748FD0 sets count+800 to512, clears512DWORDs at stride4, then
// clears the DWORD+804. Existing749020..749150 providers read/write the
// same fields. Names retain the existing project contracts; no original
// source filename or new constructor implementation is claimed.
#ifndef GG_MATCH_LAYOUT_UNIT_TRACKER_CLASS_H
#define GG_MATCH_LAYOUT_UNIT_TRACKER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct UnitTrackerClass
{
    // Native entry 0x748FD0; declaration only. (external constructor declaration only)
    UnitTrackerClass();
    // Native entry 0x749020; declaration only.
    void IncrementUnitTotal(int unitType);
    // Native entry 0x749060; declaration only.
    void Init(int unitCount);
    // Native entry 0x7490A0; declaration only.
    int GetTotalOfAll();
    // Native entry 0x7490C0; declaration only.
    int* GetAllTotals();
    // Native entry 0x7490D0; declaration only.
    void ClearUnitTotal();
    // Native entry 0x749040; declaration only.
    void DecrementUnitTotal(int unitType);
    // Native entry 0x749100; declaration only.
    void ToNetworkFormat();
    // Native entry 0x749150; declaration only.
    void ToPCFormat();

    int UnitTotals[0x200]; // native748FE1/EE:512DWORDs,stride4
    int UnitCount;        // native748FD7:+800=0x200
    int InNetworkFormat;  // native748FF5:+804 DWORD0;749100/150 DWORD accesses
};
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(int[0x200]) == 0x800);
GG_STATIC_ASSERT(offsetof(UnitTrackerClass, UnitTotals) == 0);
GG_STATIC_ASSERT(offsetof(UnitTrackerClass, UnitCount) == 0x800);
GG_STATIC_ASSERT(offsetof(UnitTrackerClass, InNetworkFormat) == 0x804);
GG_STATIC_ASSERT(sizeof(UnitTrackerClass) == 0x808);

#endif
