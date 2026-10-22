// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x7248C0: the entry array at `[ESI+0x24C]` with its count
//   at `[ESI+0x250]`, the sorted flag at `[ESI+0x258]` and the cached entry
//   at `[ESI+0x25C]`; entries are eight bytes (key then data pointer) sorted
//   with the CRT `qsort` 0x7C8B48 against the comparison function at
//   0x725040; the lookup is an inlined binary search expanded twice, and
//   the copy is a 28-byte `REP MOVSD` from the entry's data or from the
//   default at 0xB78820. Names cross-checked against YRpp.
#ifndef GG_MATCH_UI_TOOLTIP_MANAGER_FIND_METHODS_H
#define GG_MATCH_UI_TOOLTIP_MANAGER_FIND_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// One tool tip: seven dwords copied out whole.
struct ToolTipData_007248C0
{
    int Fields[7];
};
GG_STATIC_ASSERT(sizeof(ToolTipData_007248C0) == 0x1C);

// One entry of the sorted table.
struct ToolTipEntry_007248C0
{
    unsigned int             Key;    // +0x0000
    ToolTipData_007248C0*    Data;   // +0x0004
};
GG_STATIC_ASSERT(sizeof(ToolTipEntry_007248C0) == 8);

// GLOBAL: GAMEMD 0xB78820 — the tool tip returned when the key is absent.
extern ToolTipData_007248C0* DAT_00B78820;

// FUNCTION: GAMEMD 0x7C8B48 (decl; reloc) — CRT qsort.
extern "C" void __cdecl gg_qsort(void* base, unsigned int count, unsigned int size,
                                 int (__cdecl* compare)(const void*, const void*));
// FUNCTION: GAMEMD 0x725040 (decl; reloc) — the key comparison.
extern "C" int __cdecl CompareToolTipTableEntries(const void* a, const void* b);

struct ToolTip_007248C0
{
    char                      _pad0000[0x24C];   // +0x0000
    ToolTipEntry_007248C0*    Items;             // +0x024C
    int                       Count;             // +0x0250
    char                      _pad0254[4];       // +0x0254
    char                      IsSorted;          // +0x0258
    char                      _pad0259[3];       // +0x0259
    ToolTipEntry_007248C0*    Cached;            // +0x025C

    // The table lookup, expanded inline at both call sites: the cached
    // entry when it still matches, otherwise a binary search over the
    // freshly sorted table, which caches whatever it finds.
    ToolTipEntry_007248C0* Lookup(unsigned int key);

    // The same search asked only whether the key is there; its result is
    // tested, never kept, so retail's first expansion branches straight to
    // the common tail instead of materialising the entry pointer.
    bool Contains(unsigned int key);

    // FUNCTION: GAMEMD 0x7248C0 — ToolTipManager::Find.
    bool Find(unsigned int key, ToolTipData_007248C0* out);
};
GG_STATIC_ASSERT(offsetof(ToolTip_007248C0, Items)    == 0x24C);
GG_STATIC_ASSERT(offsetof(ToolTip_007248C0, Count)    == 0x250);
GG_STATIC_ASSERT(offsetof(ToolTip_007248C0, IsSorted) == 0x258);
GG_STATIC_ASSERT(offsetof(ToolTip_007248C0, Cached)   == 0x25C);

inline ToolTipEntry_007248C0* ToolTip_007248C0::Lookup(unsigned int key)
{
    if (Count == 0) {
        return 0;
    }

    ToolTipEntry_007248C0* cached = Cached;
    if (cached != 0 && cached->Key == key) {
        return cached;
    }

    if (!IsSorted) {
        gg_qsort(Items, Count, 8, CompareToolTipTableEntries);
        Cached = 0;
        IsSorted = 1;
    }

    ToolTipEntry_007248C0* base = Items;
    int n = Count;
    while (n > 0) {
        int half = n / 2;
        ToolTipEntry_007248C0* mid = base + half;
        if (mid->Key > key) {
            n = half;
        } else {
            if (mid->Key == key) {
                if (mid != 0) {
                    Cached = mid;
                    return mid;
                }
                break;
            }
            base = mid + 1;
            n = n + (-1 - half);
        }
    }
    return 0;
}

inline bool ToolTip_007248C0::Contains(unsigned int key)
{
    if (Count == 0) {
        return false;
    }

    ToolTipEntry_007248C0* cached = Cached;
    if (cached != 0 && cached->Key == key) {
        return true;
    }

    if (!IsSorted) {
        gg_qsort(Items, Count, 8, CompareToolTipTableEntries);
        Cached = 0;
        IsSorted = 1;
    }

    ToolTipEntry_007248C0* base = Items;
    int n = Count;
    while (n > 0) {
        int half = n / 2;
        ToolTipEntry_007248C0* mid = base + half;
        if (mid->Key > key) {
            n = half;
        } else {
            if (mid->Key == key) {
                if (mid != 0) {
                    Cached = mid;
                    return true;
                }
                break;
            }
            base = mid + 1;
            n = n + (-1 - half);
        }
    }
    return false;
}

#endif  // GG_MATCH_UI_TOOLTIP_MANAGER_FIND_METHODS_H
