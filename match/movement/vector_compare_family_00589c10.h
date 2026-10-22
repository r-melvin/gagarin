// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; retail gamemd.exe v1.001 entries 0x589C10..0x58A29D. | YRpp-cross-check
#ifndef GG_VECTOR_COMPARE_FAMILY_00589C10_H
#define GG_VECTOR_COMPARE_FAMILY_00589C10_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct SearchRecord36_00589C10 {
    char unknown_00[0x18];
    short Key_18;
    char unknown_1A[2];
    int Key_1C;
    char unknown_20[4];
};
GG_STATIC_ASSERT(offsetof(SearchRecord36_00589C10, Key_18) == 0x18);
GG_STATIC_ASSERT(offsetof(SearchRecord36_00589C10, Key_1C) == 0x1C);
GG_STATIC_ASSERT(sizeof(SearchRecord36_00589C10) == 0x24);
// Prefix view of the container touched by the search.
struct SearchVector36_00589C10 {
    char unknown_00[4];
    SearchRecord36_00589C10* Data;
    char unknown_08[8];
    int Count;
    int Find(const SearchRecord36_00589C10& value) const;
};
GG_STATIC_ASSERT(offsetof(SearchVector36_00589C10, Data) == 4);
GG_STATIC_ASSERT(offsetof(SearchVector36_00589C10, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(SearchVector36_00589C10) == 0x14);
// Several distinct container instantiations share this comparison prefix.
struct CompareVector4_00589CA0 {
    char unknown_00[4];
    int* Data;
    int Count;
    bool EqualsA(const CompareVector4_00589CA0& other) const;
    bool EqualsB(const CompareVector4_00589CA0& other) const;
};
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(offsetof(CompareVector4_00589CA0, Data) == 4);
GG_STATIC_ASSERT(offsetof(CompareVector4_00589CA0, Count) == 8);
GG_STATIC_ASSERT(sizeof(CompareVector4_00589CA0) == 0xC);
struct CompareRecord8_0058A110 { int Key; char unknown_04[4]; };
GG_STATIC_ASSERT(offsetof(CompareRecord8_0058A110, Key) == 0);
GG_STATIC_ASSERT(sizeof(CompareRecord8_0058A110) == 8);
struct CompareVector8_0058A110 {
    char unknown_00[4];
    CompareRecord8_0058A110* Data;
    int Count;
    bool Equals(const CompareVector8_0058A110& other) const;
};
GG_STATIC_ASSERT(offsetof(CompareVector8_0058A110, Data) == 4);
GG_STATIC_ASSERT(offsetof(CompareVector8_0058A110, Count) == 8);
GG_STATIC_ASSERT(sizeof(CompareVector8_0058A110) == 0xC);
struct CompareRecord12_0058A260 { int Key; char unknown_04[8]; };
GG_STATIC_ASSERT(offsetof(CompareRecord12_0058A260, Key) == 0);
GG_STATIC_ASSERT(sizeof(CompareRecord12_0058A260) == 12);
struct CompareVector12_0058A260 {
    char unknown_00[4];
    CompareRecord12_0058A260* Data;
    int Count;
    bool Equals(const CompareVector12_0058A260& other) const;
};
GG_STATIC_ASSERT(offsetof(CompareVector12_0058A260, Data) == 4);
GG_STATIC_ASSERT(offsetof(CompareVector12_0058A260, Count) == 8);
GG_STATIC_ASSERT(sizeof(CompareVector12_0058A260) == 0xC);
#endif
