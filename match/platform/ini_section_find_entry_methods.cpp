// Provenance: own-binary-via-Ghidra
//   Read off retail gamemd.exe v1.001 at 0x52A4D0: __thiscall on an INI
//   section (`RET 4`); the twelve-byte hash state zeroed a dword at a time
//   and passed to 0x4A1DE0 with the name and its inlined strlen; the entry
//   index at `[ESI+0x2C]` (table), `[ESI+0x30]` (count), `[ESI+0x38]` (sorted
//   byte) and `[ESI+0x3C]` (cached node); qsort 0x7C8B48 with element width 8
//   and comparator 0x52B6A0; the search at 0x52B6D0 (__fastcall: table in
//   ECX, count in EDX, key pointer pushed); the fallback cell 0xB78830.

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/ini_nodes.h"
#include "../_layout/ini_index_defaults.h"

// The hash state the entry name is run through.
struct Crc_0052A4D0
{
    int A;   // +0x0000
    int B;   // +0x0004
    int C;   // +0x0008

    // FUNCTION: GAMEMD 0x4A1DE0 (decl; reloc) -- hash a block.
    int Hash(const char* data, int length);
};
GG_STATIC_ASSERT(sizeof(Crc_0052A4D0) == 0xC);

// One {key, entry} node of the section's sorted entry index.
struct EntryNode_0052A4D0
{
    int                 Key;     // +0x0000
    INIClass::INIEntry* Entry;   // +0x0004
};
GG_STATIC_ASSERT(sizeof(EntryNode_0052A4D0) == 8);

// FUNCTION: GAMEMD 0x7C8B48 (decl; reloc) -- CRT qsort.
extern "C" void __cdecl gg_qsort(void* base, unsigned int count, unsigned int size,
                                 int (__cdecl* compare)(const void*, const void*));
// FUNCTION: GAMEMD 0x52B6A0 (decl; reloc) -- key comparison.
int __cdecl FUN_0052B6A0(const void* a, const void* b);
// FUNCTION: GAMEMD 0x52B6D0 (decl; reloc) -- table search.
EntryNode_0052A4D0* __fastcall FUN_0052B6D0(EntryNode_0052A4D0* items, int count, int* key);

// Read/write view of the observed INISection entry-index offsets; the
// canonical INISection (ini_nodes.h) has no declaration for this method.
struct INISectionEntryView
{
    char                 _pad000[0x2C];   // +0x0000
    EntryNode_0052A4D0*  Items;           // +0x002C
    int                  Count;           // +0x0030
    int                  Size;            // +0x0034
    char                 IsSorted;        // +0x0038
    char                 _pad039[3];      // +0x0039
    EntryNode_0052A4D0*  Cached;          // +0x003C

    // FUNCTION: GAMEMD 0x52A4D0
    INIClass::INIEntry* FindEntry(const char* name);

    __forceinline INIClass::INIEntry* const& Fetch(int key);
};
GG_STATIC_ASSERT(offsetof(INISectionEntryView, Items)    == 0x2C);
GG_STATIC_ASSERT(offsetof(INISectionEntryView, Count)    == 0x30);
GG_STATIC_ASSERT(offsetof(INISectionEntryView, IsSorted) == 0x38);
GG_STATIC_ASSERT(offsetof(INISectionEntryView, Cached)   == 0x3C);
GG_STATIC_ASSERT(offsetof(INIClass::INISection, EntryIndex) == 0x2C);

// The inlined second lookup: cached node, sort on demand, binary search,
// default cell when absent.
INIClass::INIEntry* const& INISectionEntryView::Fetch(int key)
{
    if (Count != 0) {
        if (Cached != 0 && Cached->Key == key) {
            return Cached->Entry;
        }
        if (!IsSorted) {
            gg_qsort(Items, Count, 8, FUN_0052B6A0);
            Cached = 0;
            IsSorted = 1;
        }
        int n = Count;
        EntryNode_0052A4D0* base = Items;
        while (n > 0) {
            int half = n / 2;
            EntryNode_0052A4D0* mid = base + half;
            if (mid->Key > key) {
                n = half;
            } else {
                if (mid->Key == key) {
                    if (mid != 0) {
                        Cached = mid;
                        return Cached->Entry;
                    }
                    break;
                }
                base = mid + 1;
                n = n + (-1 - half);
            }
        }
    }
    return DAT_00B78830;
}

// FUNCTION: GAMEMD 0x52A4D0
// Find an entry of this section by name: hash the name, answer from the
// cached node when it still matches, otherwise sort on demand and search.
// A name that is absent yields 0; the second (inlined) lookup falls back to
// the shared default entry cell.
INIClass::INIEntry* INISectionEntryView::FindEntry(const char* name)
{
    if (name == 0) {
        goto missing;
    }

    {
        Crc_0052A4D0 crc;
        crc.A = 0;
        crc.B = 0;
        crc.C = 0;
        int key = crc.Hash(name, strlen(name));

        if (Count == 0) {
            goto missing;
        }

        if (Cached == 0 || Cached->Key != key) {
            if (!IsSorted) {
                gg_qsort(Items, Count, 8, FUN_0052B6A0);
                Cached = 0;
                IsSorted = 1;
            }
            crc.A = key;
            EntryNode_0052A4D0* found = FUN_0052B6D0(Items, Count, &crc.A);
            if (found == 0) {
                goto missing;
            }
            Cached = found;
        }

        return Fetch(key);
    }

missing:
    return 0;
}
