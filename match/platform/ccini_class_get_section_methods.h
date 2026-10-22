// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x526810: the twelve-byte CRC state zeroed a dword at a
//   time and handed to 0x4A1DE0 with the name and its inlined `strlen`, the
//   section array at `[ESI+0x28]` with its count at `[ESI+0x2C]`, the
//   sorted flag at `[ESI+0x34]` and the cached entry at `[ESI+0x38]`;
//   entries are eight bytes (key then section pointer) sorted with the CRT
//   `qsort` 0x7C8B48 against the comparison at 0x52B720 and found with the
//   CRT `bsearch` 0x52B750; the fallback section pointer lives at
//   0xB7882C. Names cross-checked against YRpp.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_GET_SECTION_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_GET_SECTION_METHODS_H

#include <stddef.h>
#include "../_layout/ini_nodes.h"
#include "../_layout/ini_index_defaults.h"
#include <string.h>
#include "../_rt/gg_static_assert.h"

// The CRC engine the section name is hashed with.
struct Crc_00526810
{
    int A;   // +0x0000
    int B;   // +0x0004
    int C;   // +0x0008

    // FUNCTION: GAMEMD 0x4A1DE0 (decl; reloc) — hash a block.
    int Hash(const char* data, int length);
};
GG_STATIC_ASSERT(sizeof(Crc_00526810) == 0xC);

typedef INIClass::INISection Section_00526810;

// One entry of the sorted section table.
struct Entry_00526810
{
    int                Key;       // +0x0000
    Section_00526810*  Section;   // +0x0004
};
GG_STATIC_ASSERT(sizeof(Entry_00526810) == 8);

// GLOBAL: GAMEMD 0xB7882C — the section handed back when the name is absent.

// FUNCTION: GAMEMD 0x7C8B48 (decl; reloc) — CRT qsort.
extern "C" void __cdecl gg_qsort(void* base, unsigned int count, unsigned int size,
                                 int (__cdecl* compare)(const void*, const void*));
// FUNCTION: GAMEMD 0x52B720 (decl; reloc) — the key comparison.
int __cdecl FUN_0052B720(const void* a, const void* b);
// FUNCTION: GAMEMD 0x52B750 (decl; reloc) — the table search, __fastcall:
// the array in ECX, the count in EDX and the probe key pushed.
Entry_00526810* __fastcall FUN_0052B750(Entry_00526810* items, int count, int* key);

// Explicit read/write view of only the observed index offsets in INIClass.
// It is not a competing concrete class declaration.
struct INISectionLookupView
{
    char             _pad000[0x28];   // +0x0000
    Entry_00526810*  Items;           // +0x0028
    int              Count;           // +0x002C
    char             _pad030[4];      // +0x0030
    char             IsSorted;        // +0x0034
    char             _pad035[3];      // +0x0035
    Entry_00526810*  Cached;          // +0x0038

};
GG_STATIC_ASSERT(offsetof(INISectionLookupView, Items)    == 0x28);
GG_STATIC_ASSERT(offsetof(INISectionLookupView, Count)    == 0x2C);
GG_STATIC_ASSERT(offsetof(INISectionLookupView, IsSorted) == 0x34);
GG_STATIC_ASSERT(offsetof(INISectionLookupView, Cached)   == 0x38);

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_GET_SECTION_METHODS_H
