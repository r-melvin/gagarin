// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// 0x6B9450: the constructor of the static object at 0xAC4848 (built by
// 0x600530, which registers the 0x6B9530 teardown with atexit 0x7C978A).
// Stores read off the body: doubles 0.2 at +0x20 and 0.8 at +0x28, 128 at
// +0x30/+0x10/+0x08, a bit count at +0x0C derived from +0x10, zero at +0x04
// and the byte +0x14, a 4*size-byte zeroed bucket array at +0x00 from
// operator new, and the address 0x6B94E0 at +0x18. 0x6B94E0 takes its key in
// ECX and hashes it through the narrow string helpers 0x7B54B0/0x7B5400.
// Names are descriptive; the object's full extent is not proven, so no size
// is asserted.
#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x6B94E0 (decl; reloc) -- key hash, key pointer in ECX.
unsigned int __fastcall FUN_006B94E0(const void* key);

typedef unsigned int (__fastcall* HashFunction)(const void* key);

class StringHashTable_00AC4848
{
public:
    // FUNCTION: GAMEMD 0x6B9450
    StringHashTable_00AC4848();

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

// FUNCTION: GAMEMD 0x6B9450
StringHashTable_00AC4848::StringHashTable_00AC4848() :
    ShrinkLoad(0.2),
    GrowLoad(0.8),
    MinimumSize(128)
{
    SizeScratch = 128;
    Size = 128;
    Bits = 0;
    while (SizeScratch != 0) {
        Bits++;
        SizeScratch >>= 1;
    }
    Bits--;
    Count = 0;
    unknown_14 = false;
    Size = 1 << Bits;
    Buckets = new void*[Size];
    memset(Buckets, 0, Size * sizeof(void*));
    Hash = FUN_006B94E0;
}
