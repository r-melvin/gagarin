// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Every entry point, comparator address and offset below was read off the
//   user's own retail gamemd.exe v1.001 with the local Ghidra CLI. The offsets
//   come straight off the member accesses: Items at [ESI], Count at [ESI+4],
//   the sorted flag at [ESI+0xC] and the cached slot at [ESI+0x10]; the entry
//   stride is 8 (`MOV ESI,[EDI+EAX*8]`, `LEA EDX,[EDI+EAX*8]`).
//
// Five remaining 121-byte "sort on demand, then binary search" lookups.
//
// The out-of-line form of the lookup that the 0x6E6BB0 family inlines: if the
// table is empty there is nothing to find; if it has not been sorted since the
// last insertion, qsort it with the table's own comparator and drop the cached
// slot; then binary-search the sorted entries for the key the caller passes by
// address, returning the entry or a null pointer.
//
// These five use signed keys and differ in the comparator passed to qsort.
// The former unsigned-key entry at 0x724FC0 now belongs to ToolTipTable.
#ifndef GG_MATCH_CORE_SORT_THEN_SEARCH_SWEEP_H
#define GG_MATCH_CORE_SORT_THEN_SEARCH_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B48(void* base, unsigned int count,
                                     unsigned int width,
                                     int (__cdecl* compare)(const void*,
                                                            const void*));
extern "C" int __cdecl FUN_0041C610(const void* a, const void* b);   // GAMEMD 0x41C610  comparator
extern "C" int __cdecl FUN_0048BC20(const void* a, const void* b);   // GAMEMD 0x48BC20  comparator
extern "C" int __cdecl FUN_0052B6A0(const void* a, const void* b);   // GAMEMD 0x52B6A0  comparator
extern "C" int __cdecl FUN_0052B720(const void* a, const void* b);   // GAMEMD 0x52B720  comparator
extern "C" int __cdecl FUN_00710860(const void* a, const void* b);   // GAMEMD 0x710860  comparator
extern "C" int __cdecl CompareToolTipTableEntries(const void* a, const void* b);   // GAMEMD 0x725040  comparator

// An 8-byte (key, value) entry, in both signed and unsigned key flavours.
#define GG_SORT_SEARCH_TYPES(TAG, KEY)                                     \
struct Entry_##TAG                                                         \
{                                                                          \
    KEY   Key;     /* +0x0000 */                                           \
    void* Value;   /* +0x0004 */                                           \
};                                                                         \
struct Table_##TAG                                                         \
{                                                                          \
    Entry_##TAG* Items;      /* +0x0000 */                                 \
    int          Count;      /* +0x0004 */                                 \
    int          Capacity;   /* +0x0008 */                                 \
    char         IsSorted;   /* +0x000C */                                 \
    char         _pad00D[3]; /* +0x000D */                                 \
    int          Cached;     /* +0x0010 */                                 \
                                                                           \
    Entry_##TAG* SearchSorted(const KEY* key);                             \
    Entry_##TAG* Find_##TAG(const KEY* key);                               \
};                                                                         \
GG_STATIC_ASSERT(sizeof(Entry_##TAG) == 8);                                \
GG_STATIC_ASSERT(offsetof(Table_##TAG, Count) == 0x4);                     \
GG_STATIC_ASSERT(offsetof(Table_##TAG, IsSorted) == 0xC);                  \
GG_STATIC_ASSERT(offsetof(Table_##TAG, Cached) == 0x10)

GG_SORT_SEARCH_TYPES(41C590, int);   // FUNCTION: GAMEMD 0x41C590
GG_SORT_SEARCH_TYPES(52B4F0, int);   // FUNCTION: GAMEMD 0x52B4F0
GG_SORT_SEARCH_TYPES(52B620, int);   // FUNCTION: GAMEMD 0x52B620
GG_SORT_SEARCH_TYPES(55F6E0, int);   // FUNCTION: GAMEMD 0x55F6E0
GG_SORT_SEARCH_TYPES(7107E0, int);   // FUNCTION: GAMEMD 0x7107E0

// The search half, kept as its own inline function on purpose. See the .cpp:
// splitting it out is what stops cl merging the empty-table `return 0` with the
// loop's miss `return 0`, and that merge is what otherwise drags both extra
// callee-saved pushes up into the prologue.
#define GG_SORT_SEARCH_BODY(TAG, KEY)                                      \
inline Entry_##TAG* Table_##TAG::SearchSorted(const KEY* key)              \
{                                                                          \
    Entry_##TAG* base = Items;                                             \
    KEY k = *key;                                                          \
    int count;                                                             \
                                                                           \
    for (count = Count; count > 0; ) {                                     \
        int half = count / 2;                                              \
        Entry_##TAG* mid = base + half;                                    \
                                                                           \
        if (mid->Key > k) {                                                \
            count = half;                                                  \
        } else {                                                           \
            if (mid->Key == k) {                                           \
                return mid;                                                \
            }                                                              \
            base = mid + 1;                                                \
            count = count - 1 - half;                                      \
        }                                                                  \
    }                                                                      \
                                                                           \
    return 0;                                                              \
}                                                                          \
                                                                           \
Entry_##TAG* Table_##TAG::Find_##TAG(const KEY* key)                       \
{                                                                          \
    if (Count == 0) {                                                      \
        return 0;                                                          \
    }                                                                      \
                                                                           \
    if (!IsSorted) {                                                       \
        FUN_007C8B48(Items, Count, sizeof(Entry_##TAG), GG_CMP_##TAG);     \
        Cached = 0;                                                        \
        IsSorted = 1;                                                      \
    }                                                                      \
                                                                           \
    return SearchSorted(key);                                              \
}

#define GG_CMP_41C590 FUN_0041C610
#define GG_CMP_52B4F0 FUN_0052B6A0
#define GG_CMP_52B620 FUN_0052B720
#define GG_CMP_55F6E0 FUN_0048BC20
#define GG_CMP_7107E0 FUN_00710860

#endif  // GG_MATCH_CORE_SORT_THEN_SEARCH_SWEEP_H
