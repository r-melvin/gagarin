// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x631C10 (the strcmp is the compiler's
//   inline expansion, the wide compare is the CRT wcscmp at 0x7CA5D3).
//
// Address index: 0x631C10

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7CA5D3 (decl; reloc) -- CRT wcscmp.
extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);

// A list entry: a wide display name at +0x70 and a narrow key at +0x9A.
struct NameEntry_00631C10
{
    char    unknown_00[0x70];
    wchar_t DisplayName[21];   // +0x70
    char    Key[1];            // +0x9A
};
GG_STATIC_ASSERT(offsetof(NameEntry_00631C10, DisplayName) == 0x70);
GG_STATIC_ASSERT(offsetof(NameEntry_00631C10, Key) == 0x9A);

// FUNCTION: GAMEMD 0x631C10
// Order two entries by display name, then by key (qsort comparator over entry pointers).
int __cdecl CompareNameEntries_00631C10(NameEntry_00631C10** a, NameEntry_00631C10** b)
{
    NameEntry_00631C10* left = *a;
    NameEntry_00631C10* right = *b;
    int result = wcscmp(left->DisplayName, right->DisplayName);
    if (result != 0) {
        return result;
    }
    return strcmp(left->Key, right->Key);
}
