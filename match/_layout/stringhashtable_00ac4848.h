// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_STRINGHASHTABLE_00AC4848_H_H
#define GG_MATCH__LAYOUT_STRINGHASHTABLE_00AC4848_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class Wstring;

typedef unsigned int (* HashFunction)(const Wstring* key);

class StringHashTable_00AC4848
{
public:
    // FUNCTION: GAMEMD 0x6B9450
    StringHashTable_00AC4848();
    ~StringHashTable_00AC4848();

    void**       Buckets;       // +0x00
    int          Count;         // +0x04
    int          Size;          // +0x08
    int          Bits;          // +0x0C
    unsigned int SizeScratch;   // +0x10
    bool         unknown_14;    // +0x14
    HashFunction Hash;          // +0x18
    double       ShrinkLoad;    // +0x20
    double       GrowLoad;      // +0x28
    int          MinimumSize;   // +0x30
};
GG_STATIC_ASSERT(offsetof(StringHashTable_00AC4848, Count)       == 0x04);
GG_STATIC_ASSERT(offsetof(StringHashTable_00AC4848, Size)        == 0x08);
GG_STATIC_ASSERT(offsetof(StringHashTable_00AC4848, Bits)        == 0x0C);
GG_STATIC_ASSERT(offsetof(StringHashTable_00AC4848, SizeScratch) == 0x10);
GG_STATIC_ASSERT(offsetof(StringHashTable_00AC4848, unknown_14)  == 0x14);
GG_STATIC_ASSERT(offsetof(StringHashTable_00AC4848, Hash)        == 0x18);
GG_STATIC_ASSERT(offsetof(StringHashTable_00AC4848, ShrinkLoad)  == 0x20);
GG_STATIC_ASSERT(offsetof(StringHashTable_00AC4848, GrowLoad)    == 0x28);
GG_STATIC_ASSERT(offsetof(StringHashTable_00AC4848, MinimumSize) == 0x30);

#endif
