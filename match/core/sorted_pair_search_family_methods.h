// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4D2F00 and its six siblings. Everything the shape needs is
//   in the instructions: the table entries are eight bytes wide
//   (`MOV EDI,[ECX+EAX*8]`, `LEA EDX,[ECX+EAX*8]`, `LEA ECX,[EDX+8]`) and the
//   key is the first dword of an entry (displacement 0 on that load); the
//   sought key is loaded once, before the loop, from the dword the caller
//   points at (`MOV EAX,[ESP+0x10]; MOV EBX,[EAX]`); the halving is a signed
//   divide by two (`CDQ; SUB EAX,EDX; SAR EAX,1`); and the convention is
//   __fastcall with the table base in ECX, the entry count in EDX and the key
//   pointer on the stack (`RET 4`).
//
// Shape: a textbook binary search over a sorted array of (key, value) pairs.
//   While the window is non-empty, look at its middle entry: a greater key
//   shrinks the window to the lower half, an equal key returns that entry's
//   address, and a lesser key moves the base past the middle and drops the
//   window by the discarded half plus one. Falling out of the loop returns a
//   null pointer. Six instantiations compare the key signed; the seventh,
//   0x725070, is byte-identical except that its `JLE` is a `JBE`, so its key
//   type is unsigned.
//
//   These entry points carry no name in the binary or in the YRpp map and keep
//   their placeholder names.
#ifndef GG_MATCH_CORE_SORTED_PAIR_SEARCH_FAMILY_METHODS_H
#define GG_MATCH_CORE_SORTED_PAIR_SEARCH_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// An eight-byte table entry: the key first, then whatever the table maps it to.
struct SortedEntry_004D2F00
{
    int   Key;     // +0x0000
    void* Value;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(SortedEntry_004D2F00, Key)   == 0x0);
GG_STATIC_ASSERT(offsetof(SortedEntry_004D2F00, Value) == 0x4);
GG_STATIC_ASSERT(sizeof(SortedEntry_004D2F00) == 0x8);

// The unsigned-keyed twin. Same eight bytes, same member offsets.
struct SortedEntryU_00725070
{
    unsigned int Key;     // +0x0000
    void*        Value;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(SortedEntryU_00725070, Key)   == 0x0);
GG_STATIC_ASSERT(offsetof(SortedEntryU_00725070, Value) == 0x4);
GG_STATIC_ASSERT(sizeof(SortedEntryU_00725070) == 0x8);

// The one shared body. Two phrasing points carry it from 34.3% to 94.3%:
// the greater-than arm has to be written first so the window-halving is the
// fall-through and the equality test sits in the taken branch, as retail lays
// them out; and the shrink has to be spelled `count - 1 - half` so cl folds
// the two subtractions into retail's `OR EDX,-1; SUB EDX,EAX; ADD ESI,EDX`
// rather than emitting a separate `DEC`.
#define GG_SORTED_PAIR_SEARCH_BODY(ADDR, ENTRY, KEYTYPE)                  \
ENTRY* __fastcall FUN_##ADDR(ENTRY* base, int count, const KEYTYPE* key)  \
{                                                                         \
    while (count > 0) {                                                   \
        int half = count / 2;                                             \
        ENTRY* mid = base + half;                                         \
        if (mid->Key > *key) {                                            \
            count = half;                                                 \
        } else {                                                          \
            if (mid->Key == *key) {                                       \
                return mid;                                               \
            }                                                             \
            base = mid + 1;                                               \
            count = count - 1 - half;                                     \
        }                                                                 \
    }                                                                     \
    return 0;                                                             \
}

// FUNCTION: GAMEMD 0x004D2F00
SortedEntry_004D2F00* __fastcall FUN_004D2F00(SortedEntry_004D2F00* base, int count, const int* key);
// FUNCTION: GAMEMD 0x00523440
SortedEntry_004D2F00* __fastcall FUN_00523440(SortedEntry_004D2F00* base, int count, const int* key);
// FUNCTION: GAMEMD 0x0052B6D0
SortedEntry_004D2F00* __fastcall FUN_0052B6D0(SortedEntry_004D2F00* base, int count, const int* key);
// FUNCTION: GAMEMD 0x0052B750
SortedEntry_004D2F00* __fastcall FUN_0052B750(SortedEntry_004D2F00* base, int count, const int* key);
// FUNCTION: GAMEMD 0x005FC120
SortedEntry_004D2F00* __fastcall FUN_005FC120(SortedEntry_004D2F00* base, int count, const int* key);
// FUNCTION: GAMEMD 0x00710890
SortedEntry_004D2F00* __fastcall FUN_00710890(SortedEntry_004D2F00* base, int count, const int* key);
// FUNCTION: GAMEMD 0x00725070
SortedEntryU_00725070* __fastcall FUN_00725070(SortedEntryU_00725070* base, int count, const unsigned int* key);

#endif  // GG_MATCH_CORE_SORTED_PAIR_SEARCH_FAMILY_METHODS_H
