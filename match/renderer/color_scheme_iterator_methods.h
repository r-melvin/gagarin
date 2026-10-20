// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x626690: the iterator in ECX is `[ESI]` (bucket),
//   `[ESI+4]` (entry index) and `byte [ESI+8]` (done); the table is
//   `[[0xAC48F0]+0xC]` with `[EBX]` (buckets), `[EBX+4]` (hash routine,
//   called with the entry in ECX) and `[EBX+8]` (bucket count, also the IDIV
//   divisor); buckets are 0x18 bytes (`[EAX+EDX*8]` with EDX = 3*index)
//   holding `[+4]` (entries) and `[+0x10]` (count); entries are 0x104 bytes
//   (`EAX*65*4`, `SUB EBX,0x104`) whose value pointer sits at +0x100 and the
//   returned word is `[value+0x100]`. The blank test at 0x4F4CA0 reads the
//   entry's first byte (`*key == 0`); the compare at 0x4F4CE0 is __thiscall
//   with one pushed entry. Method name from YRpp (consult-only, no LICENSE).
#ifndef GG_MATCH_RENDERER_COLOR_SCHEME_ITERATOR_METHODS_H
#define GG_MATCH_RENDERER_COLOR_SCHEME_ITERATOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// DynamicVectorClass<ColorScheme*> view (the returned per-palette vector).
struct ColorSchemeVec_00626690;

// The keyed object an entry points at: only its scheme vector at +0x100.
struct Palette_00626690
{
    char _pad000[0x100];               // +0x0000
    ColorSchemeVec_00626690* Schemes;  // +0x0100
};
GG_STATIC_ASSERT(offsetof(Palette_00626690, Schemes) == 0x100);

// One hash-table entry: a 256-byte name key and the value pointer.
struct Entry_00626690
{
    char Key[0x100];                   // +0x0000
    Palette_00626690* Value;           // +0x0100

    // FUNCTION: GAMEMD 0x4F4CA0 (decl; reloc) — true when the key is blank.
    bool IsBlank();
    // FUNCTION: GAMEMD 0x4F4CE0 (decl; reloc) — key equality.
    bool Equals(Entry_00626690* other);
};
GG_STATIC_ASSERT(offsetof(Entry_00626690, Value) == 0x100);
GG_STATIC_ASSERT(sizeof(Entry_00626690) == 0x104);

struct Bucket_00626690
{
    int  At_00;                        // +0x0000
    Entry_00626690* Entries;           // +0x0004
    int  At_08;                        // +0x0008
    int  At_0C;                        // +0x000C
    int  Count;                        // +0x0010
    int  At_14;                        // +0x0014
};
GG_STATIC_ASSERT(offsetof(Bucket_00626690, Entries) == 0x04);
GG_STATIC_ASSERT(offsetof(Bucket_00626690, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(Bucket_00626690) == 0x18);

typedef int (__fastcall* HashFn_00626690)(Entry_00626690* key);

struct Table_00626690
{
    Bucket_00626690* Buckets;          // +0x0000
    HashFn_00626690  Hash;             // +0x0004
    int              NumBuckets;       // +0x0008
};
GG_STATIC_ASSERT(offsetof(Table_00626690, Hash) == 0x04);
GG_STATIC_ASSERT(offsetof(Table_00626690, NumBuckets) == 0x08);

// The owner of the palette table.
struct Owner_00626690
{
    char _pad000[0xC];                 // +0x0000
    Table_00626690* Table;             // +0x000C
};
GG_STATIC_ASSERT(offsetof(Owner_00626690, Table) == 0xC);
// GLOBAL: GAMEMD 0xAC48F0 — the palette-table owner.
extern Owner_00626690* DAT_00AC48F0;

// The 12-byte iterator handed in ECX (bucket, index, done).
struct HashIterator_00626690
{
    int  Bucket;                       // +0x0000
    int  Index;                        // +0x0004
    char Done;                         // +0x0008
    char _pad009[3];                   // +0x0009
};
GG_STATIC_ASSERT(offsetof(HashIterator_00626690, Index) == 0x4);
GG_STATIC_ASSERT(offsetof(HashIterator_00626690, Done) == 0x8);
GG_STATIC_ASSERT(sizeof(HashIterator_00626690) == 0xC);

// FUNCTION: GAMEMD 0x626690 — ColorScheme::GetPaletteSchemesFromIterator
// (static; the iterator rides in ECX).
ColorSchemeVec_00626690* __fastcall GetPaletteSchemesFromIterator(HashIterator_00626690* it);

#endif  // GG_MATCH_RENDERER_COLOR_SCHEME_ITERATOR_METHODS_H
