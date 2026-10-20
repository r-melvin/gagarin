// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; retail gamemd.exe v1.001 entries 0x589DC0..0x58A3C5.
#ifndef GG_VECTOR_LOOKUP_FAMILY_00589DC0_H
#define GG_VECTOR_LOOKUP_FAMILY_00589DC0_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
// Prefix views. The two loop-bound fields are named by their offsets because
// these entries alone do not establish the owning container's full layout.
struct VectorLookup4_00589DC0 {
    char unknown_00[4];
    int* Data;
    int Count_08;
    unsigned char Valid;
    char unknown_0D[3];
    int Count_10;
    int FindFirst(const int& value) const;
    unsigned int IndexFirst(const int* item) const;
    int FindSecond(const int& value) const;
    unsigned int IndexSecond(const int* item) const;
    int FindActive(const int& value) const;
};
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(offsetof(VectorLookup4_00589DC0, Data) == 4);
GG_STATIC_ASSERT(offsetof(VectorLookup4_00589DC0, Count_08) == 8);
GG_STATIC_ASSERT(offsetof(VectorLookup4_00589DC0, Valid) == 0xC);
GG_STATIC_ASSERT(offsetof(VectorLookup4_00589DC0, Count_10) == 0x10);
GG_STATIC_ASSERT(sizeof(VectorLookup4_00589DC0) == 0x14);
struct LookupRecord8_0058A230 {
    int Key;
    char unknown_04[4];
};
GG_STATIC_ASSERT(offsetof(LookupRecord8_0058A230, Key) == 0);
GG_STATIC_ASSERT(sizeof(LookupRecord8_0058A230) == 8);
struct VectorLookup8_0058A230 {
    char unknown_00[4];
    LookupRecord8_0058A230* Data;
    char unknown_08[8];
    int Count;
    int Find(const int& value) const;
};
GG_STATIC_ASSERT(offsetof(VectorLookup8_0058A230, Data) == 4);
GG_STATIC_ASSERT(offsetof(VectorLookup8_0058A230, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(VectorLookup8_0058A230) == 0x14);
struct LookupRecord12_0058A3A0 {
    int Key;
    char unknown_04[8];
};
GG_STATIC_ASSERT(offsetof(LookupRecord12_0058A3A0, Key) == 0);
GG_STATIC_ASSERT(sizeof(LookupRecord12_0058A3A0) == 12);
struct VectorLookup12_0058A3A0 {
    char unknown_00[4];
    LookupRecord12_0058A3A0* Data;
    char unknown_08[8];
    int Count;
    int Find(const int& value) const;
};
GG_STATIC_ASSERT(offsetof(VectorLookup12_0058A3A0, Data) == 4);
GG_STATIC_ASSERT(offsetof(VectorLookup12_0058A3A0, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(VectorLookup12_0058A3A0) == 0x14);
#endif
