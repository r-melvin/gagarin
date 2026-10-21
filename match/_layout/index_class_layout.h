// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Accessed IndexClass prefix: retail INISection destructor and INIClass
// destructor 0x5256F0 free +0 and reset +4/+8/+C/+10 with the widths below.
#ifndef GG_MATCH_LAYOUT_INDEX_CLASS_LAYOUT_H
#define GG_MATCH_LAYOUT_INDEX_CLASS_LAYOUT_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete.
extern "C" void __cdecl FUN_007C8B3D(void*);
struct IndexClassRaw
{
    void* IndexTable;   // +0x00
    int   IndexCount;   // +0x04
    int   IndexSize;    // +0x08
    char  IsSorted;     // +0x0C
    void* Archive;      // +0x10

    __forceinline void Clear();
};
GG_STATIC_ASSERT(offsetof(IndexClassRaw, IndexTable) == 0);
GG_STATIC_ASSERT(offsetof(IndexClassRaw, IndexCount) == 4);
GG_STATIC_ASSERT(offsetof(IndexClassRaw, IndexSize) == 8);
GG_STATIC_ASSERT(offsetof(IndexClassRaw, IsSorted) == 0xC);
GG_STATIC_ASSERT(offsetof(IndexClassRaw, Archive) == 0x10);
GG_STATIC_ASSERT(sizeof(IndexClassRaw) == 0x14);
__forceinline void IndexClassRaw::Clear()
{
    FUN_007C8B3D(IndexTable);
    IndexTable = 0;
    IndexCount = 0;
    IndexSize = 0;
    IsSorted = 0;
    Archive = 0;
}
#endif
