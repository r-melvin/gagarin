// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x6C6D00 (front removal) and 0x6C8870 / 0x6C8900
//   (shrink and grow). The array at 0xB0BD50 is {count, capacity, storage}; every element is 0x8008 bytes: a type word, a length word and 0x8000 bytes
//   of data.
#ifndef GG_MATCH_CORE_VECTOR_BIG_006C8870_H
#define GG_MATCH_CORE_VECTOR_BIG_006C8870_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"

extern "C" void __cdecl gg_free(void*);

struct BigEntry_006C6B00
{
    int  Type;          // +0x0000
    int  Length;        // +0x0004
    char Data[0x8000];  // +0x0008
};
GG_STATIC_ASSERT(offsetof(BigEntry_006C6B00, Length) == 0x04);
GG_STATIC_ASSERT(offsetof(BigEntry_006C6B00, Data) == 0x08);
GG_STATIC_ASSERT(sizeof(BigEntry_006C6B00) == 0x8008);

struct VectorBig_006C8870
{
    int                Count;      // +0x00
    int                Capacity;   // +0x04
    BigEntry_006C6B00* Items;      // +0x08

    // The file-scope object's constructor zeroes the three words; its destructor frees the block and
    // clears the count.
    VectorBig_006C8870() : Count(0), Capacity(0), Items(0) {}
    ~VectorBig_006C8870()
    {
        BigEntry_006C6B00* block = Items;
        Count = 0;
        gg_free(block);
    }

    // FUNCTION: GAMEMD 0x6C8900 (__thiscall)
    bool FUN_006C8900();
    // FUNCTION: GAMEMD 0x6C8870 (__thiscall)
    bool FUN_006C8870();
};
GG_STATIC_ASSERT(offsetof(VectorBig_006C8870, Capacity) == 0x04);
GG_STATIC_ASSERT(offsetof(VectorBig_006C8870, Items) == 0x08);
GG_STATIC_ASSERT(sizeof(VectorBig_006C8870) == 0x0C);

#endif  // GG_MATCH_CORE_VECTOR_BIG_006C8870_H
