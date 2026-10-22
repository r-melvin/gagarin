// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4F4CE0, 0x4F4D30
//   and 0x626690.

#include "color_scheme_iterator_methods.h"

extern "C" int __cdecl strcmp(const char* a, const char* b);
#pragma intrinsic(strcmp)

// FUNCTION: GAMEMD 0x4F4CE0
// True when the two keys hold the same text.
bool Entry_00626690::Equals(Entry_00626690* other)
{
    return strcmp(Key, other->Key) == 0;
}

// FUNCTION: GAMEMD 0x4F4D30
// True when the two keys differ.
bool Entry_00626690::FUN_004F4D30(Entry_00626690* other)
{
    return strcmp(Key, other->Key) != 0;
}

// Advance the iterator to the next non-blank entry of the palette table and
// return it, or null (and mark the iterator done) once the buckets run out.
static inline Entry_00626690* Inline_00626690_a(Table_00626690* table, HashIterator_00626690* it)
{
    if (it->Done != 0) {
        return 0;
    }
    while (it->Bucket < table->NumBuckets) {
        Bucket_00626690* bucket = &table->Buckets[it->Bucket];
        while (it->Index < bucket->Count) {
            Entry_00626690* entry = &bucket->Entries[it->Index];
            it->Index++;
            if (!entry->IsBlank()) {
                return entry;
            }
        }
        it->Index = 0;
        it->Bucket = it->Bucket + 1;
    }
    it->Done = 1;
    return 0;
}

// Look an entry's key up again through the hash and return the address of the
// matching entry's value slot, or null.
static inline Palette_00626690** Inline_00626690_b(Table_00626690* table, Entry_00626690* key)
{
    int h = (*table->Hash)(key) % table->NumBuckets;
    Bucket_00626690* bucket = &table->Buckets[h];
    for (int i = bucket->Count - 1; i >= 0; i--) {
        Entry_00626690* e = &bucket->Entries[i];
        if (e->Equals(key)) {
            return &e->Value;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x626690
//
// Step the palette iterator: the next non-blank entry is looked up again by
// key and the scheme vector of the palette it names is returned. A finished
// iterator, an exhausted table, or a failed lookup all answer null.
//
// Phrasing that matters: the entry is taken at the current index and the
// index bumped afterwards (`Entries[it->Index]; it->Index++`), which keeps
// retail's `INC EAX; MOV [ESI+4],EAX` after the 65x scale; `it->Index = i + 1`
// through a local becomes `LEA ECX,[EAX+1]` ahead of it (82.4%). The lookup's
// found body returns through the loop's cached entry pointer (`LEA
// EAX,[ESI+0x100]`) rather than re-indexing the bucket.
ColorSchemeVec_00626690* __fastcall GetPaletteSchemesFromIterator(HashIterator_00626690* it)
{
    Table_00626690* table = DAT_00AC48F0->Table;
    Entry_00626690* entry = Inline_00626690_a(table, it);
    if (entry == 0) {
        return 0;
    }
    Palette_00626690** value = Inline_00626690_b(DAT_00AC48F0->Table, entry);
    if (value == 0) {
        return 0;
    }
    return (*value)->Schemes;
}
