// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// A static data member of IndexClass type, as laid out at 0x8B3CC0. Its
// initialiser at 0x4D07F0 zeroes the five prefix fields and registers the
// exit-time destructor stub at 0x4D0820, which tests bit 0 of the guard byte
// 0x8B3CD4, frees the table and zeroes the fields again. The owning class is
// not recoverable, so the member gets a placeholder holder as in
// static_vector_member_dtor_stubs_a.cpp.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete.
extern "C" void __cdecl FUN_007C8B3D(void*);

struct StaticIndex_008B3CC0 {
    void* IndexTable;   // +0x00
    int   IndexCount;   // +0x04
    int   IndexSize;    // +0x08
    char  IsSorted;     // +0x0C
    void* Archive;      // +0x10
    StaticIndex_008B3CC0() : IndexTable(0), IndexCount(0), IndexSize(0), IsSorted(0), Archive(0) {}
    ~StaticIndex_008B3CC0()
    {
        FUN_007C8B3D(IndexTable);
        IndexTable = 0;
        IndexCount = 0;
        IndexSize = 0;
        IsSorted = 0;
        Archive = 0;
    }
};
GG_STATIC_ASSERT(sizeof(StaticIndex_008B3CC0) == 0x14);

struct StaticIndexHolder_008B3CC0 {
    // GLOBAL: GAMEMD 0x008B3CC0
    static StaticIndex_008B3CC0 DAT_008B3CC0;
};
// SYNTHETIC: GAMEMD 0x004D0820 -- exit-time destructor stub of DAT_008B3CC0, guard byte 0x008B3CD4 bit 0
// SYNTHETIC: GAMEMD 0x004D07F0 -- initialiser of DAT_008B3CC0
StaticIndex_008B3CC0 StaticIndexHolder_008B3CC0::DAT_008B3CC0;
