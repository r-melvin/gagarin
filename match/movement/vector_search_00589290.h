// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; retail gamemd.exe v1.001 entries 0x589290..0x589362.
#ifndef GG_VECTOR_SEARCH_00589290_H
#define GG_VECTOR_SEARCH_00589290_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct SearchRecord8_00589290 {
    int Key;
    int unknown_04;
};
GG_STATIC_ASSERT(offsetof(SearchRecord8_00589290, Key) == 0);
GG_STATIC_ASSERT(offsetof(SearchRecord8_00589290, unknown_04) == 4);
GG_STATIC_ASSERT(sizeof(SearchRecord8_00589290) == 8);
// Prefix view: entry 0x589290 copies complete 8-byte elements; the search
// at 0x5892D0 compares only their first dword.
struct SearchVector8_00589290 {
    char unknown_00[4];
    SearchRecord8_00589290* Data;
    char unknown_08[8];
    int Count;
    bool Remove(int index);
    int Find(const SearchRecord8_00589290& item) const;
};
GG_STATIC_ASSERT(offsetof(SearchVector8_00589290, Data) == 4);
GG_STATIC_ASSERT(offsetof(SearchVector8_00589290, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(SearchVector8_00589290) == 0x14);
struct SearchRecord16_00589300 {
    short unknown_00;
    short unknown_02;
    short unknown_04;
    short unknown_06;
    char unknown_08[8];

};
GG_STATIC_ASSERT(offsetof(SearchRecord16_00589300, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(SearchRecord16_00589300, unknown_02) == 2);
GG_STATIC_ASSERT(offsetof(SearchRecord16_00589300, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(SearchRecord16_00589300, unknown_06) == 6);
GG_STATIC_ASSERT(sizeof(SearchRecord16_00589300) == 0x10);
// Prefix view; +8 is the comparison loop bound in 0x589300.
struct SearchVector16_00589300 {
    char unknown_00[4];
    SearchRecord16_00589300* Data;
    int Count;
    bool Equals(const SearchVector16_00589300& other) const;
};
GG_STATIC_ASSERT(offsetof(SearchVector16_00589300, Data) == 4);
GG_STATIC_ASSERT(offsetof(SearchVector16_00589300, Count) == 8);
GG_STATIC_ASSERT(sizeof(SearchVector16_00589300) == 0xC);
#endif
