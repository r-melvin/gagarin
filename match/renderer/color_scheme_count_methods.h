// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x626C60: the owner global `[0xAC48F0]` is a 0x10-byte
//   object (`PUSH 0x10; CALL 0x7C8E17`) holding `-1` at +0, two 0x18-byte
//   vectors at +4 / +8 (each built by `PUSH 0; PUSH 0; CALL 0x5AD6F0` resp.
//   `CALL 0x628DF0` with the object in ECX, then the vtable `0x7E5BC4` /
//   `0x7EF750`, `[ESI+0x14] = 10`, `[ESI+0x10] = 0`) and a 0x10-byte hash
//   table at +0xC (`[ESI+4] = 0x626660`, `[ESI+8] = 0x1F`, `[ESI+0xC] = 10`,
//   `[ESI] = buckets`); the buckets are one `PUSH 0x2EC` allocation with the
//   count cookie `[EAX] = 0x1F` in front and the strided constructor helper
//   0x4068F0 (`PUSH 0x628740; PUSH 0x1F; PUSH 0x18; PUSH EDI`), then each
//   bucket's `[+0x14]` is set to 10 in a loop over `[ESI+8]`. The answer is
//   `[[[0xAC48F0]+4]+0x10]`. The bucket layout is the one confirmed in
//   match/renderer/color_scheme_iterator_methods.h (re-declared here so the TU
//   stands alone). Method name from YRpp.
#ifndef GG_MATCH_RENDERER_COLOR_SCHEME_COUNT_METHODS_H
#define GG_MATCH_RENDERER_COLOR_SCHEME_COUNT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8E17 — operator new (CRT; reloc).
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);

// A __thiscall element constructor: the element goes in ECX.
typedef void (* ElemFn_00626C60)(void* elem);

// FUNCTION: GAMEMD 0x4068F0 (decl; reloc) — the vector constructor iterator:
// run `fn` over `count` elements of `stride` bytes starting at `base`.
void __stdcall FUN_004068F0(char* base, int stride, int count, ElemFn_00626C60 fn);

// FUNCTION: GAMEMD 0x628740 (decl; reloc) — the bucket vector's default
// constructor, reached through the iterator above with the bucket in ECX.
void FUN_00628740(void* bucket);

// VectorClass<T> base: vtable, Items, Capacity, IsInitialized, IsAllocated.
// One base per scheme vector because each has its own out-of-line ctor.
struct VecBaseA_00626C60
{
    void* Items;                      // +0x0004
    int   Capacity;                   // +0x0008
    char  IsInitialized;              // +0x000C
    char  IsAllocated;                // +0x000D
    char  _pad00E[2];                 // +0x000E

    // FUNCTION: GAMEMD 0x5AD6F0 (decl; reloc) — VectorClass ctor (capacity,
    // items).
    VecBaseA_00626C60(int capacity, void* items) throw();
    virtual void Slot0();             // vtable at +0x0000
};
GG_STATIC_ASSERT(sizeof(VecBaseA_00626C60) == 0x10);

struct VecBaseB_00626C60
{
    void* Items;                      // +0x0004
    int   Capacity;                   // +0x0008
    char  IsInitialized;              // +0x000C
    char  IsAllocated;                // +0x000D
    char  _pad00E[2];                 // +0x000E

    // FUNCTION: GAMEMD 0x628DF0 (decl; reloc) — VectorClass ctor (capacity,
    // items).
    VecBaseB_00626C60(int capacity, void* items) throw();
    virtual void Slot0();             // vtable at +0x0000
};
GG_STATIC_ASSERT(sizeof(VecBaseB_00626C60) == 0x10);

// DynamicVectorClass<T> for the first scheme vector (0x18 bytes).
// VTABLE: GAMEMD 0x7E5BC4
struct VecA_00626C60 : VecBaseA_00626C60
{
    int Count;                        // +0x0010
    int CapacityIncrement;            // +0x0014

    VecA_00626C60() throw() : VecBaseA_00626C60(0, 0) { CapacityIncrement = 10; Count = 0; }
    virtual void Slot0();
};
GG_STATIC_ASSERT(offsetof(VecA_00626C60, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(VecA_00626C60, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(VecA_00626C60) == 0x18);

// DynamicVectorClass<T> for the second scheme vector (0x18 bytes).
// VTABLE: GAMEMD 0x7EF750
struct VecB_00626C60 : VecBaseB_00626C60
{
    int Count;                        // +0x0010
    int CapacityIncrement;            // +0x0014

    VecB_00626C60() throw() : VecBaseB_00626C60(0, 0) { CapacityIncrement = 10; Count = 0; }
    virtual void Slot0();
};
GG_STATIC_ASSERT(offsetof(VecB_00626C60, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(VecB_00626C60) == 0x18);

// One hash bucket: a DynamicVectorClass of entries (0x18 bytes).
struct Bucket_00626C60
{
    void* Vtbl;                       // +0x0000
    void* Entries;                    // +0x0004
    int   Capacity;                   // +0x0008
    char  IsInitialized;              // +0x000C
    char  IsAllocated;                // +0x000D
    char  _pad00E[2];                 // +0x000E
    int   Count;                      // +0x0010
    int   CapacityIncrement;          // +0x0014
};
GG_STATIC_ASSERT(offsetof(Bucket_00626C60, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(Bucket_00626C60) == 0x18);

typedef int (* HashFn_00626C60)(void* key);

// FUNCTION: GAMEMD 0x626660 (decl; reloc) — the palette-name hash routine.
int FUN_00626660(void* key);

// The palette hash table (0x10 bytes).
struct Table_00626C60
{
    Bucket_00626C60* Buckets;         // +0x0000
    HashFn_00626C60  Hash;            // +0x0004
    int              NumBuckets;      // +0x0008
    int              At_0C;           // +0x000C

    Table_00626C60(HashFn_00626C60 hash, int numBuckets) throw();
};
GG_STATIC_ASSERT(offsetof(Table_00626C60, Hash) == 0x04);
GG_STATIC_ASSERT(offsetof(Table_00626C60, NumBuckets) == 0x08);
GG_STATIC_ASSERT(offsetof(Table_00626C60, At_0C) == 0x0C);
GG_STATIC_ASSERT(sizeof(Table_00626C60) == 0x10);

// The owner of the palette table and scheme vectors (0x10 bytes).
struct Owner_00626C60
{
    int              At_00;           // +0x0000  -1
    VecA_00626C60*   VecA;            // +0x0004
    VecB_00626C60*   VecB;            // +0x0008
    Table_00626C60*  Table;           // +0x000C

    Owner_00626C60() throw();
    // FUNCTION: GAMEMD 0x6272A0 (decl; reloc) -- the out-of-line destructor.
    ~Owner_00626C60();
};
GG_STATIC_ASSERT(offsetof(Owner_00626C60, VecA) == 0x4);
GG_STATIC_ASSERT(offsetof(Owner_00626C60, Table) == 0xC);
GG_STATIC_ASSERT(sizeof(Owner_00626C60) == 0x10);

// GLOBAL: GAMEMD 0xAC48F0 — the palette-table owner.
extern Owner_00626C60* DAT_00AC48F0;

struct ColorScheme_00626C60
{
    // FUNCTION: GAMEMD 0x626C60 — ColorScheme::GetNumberOfSchemes (static).
    static int GetNumberOfSchemes();
};

#endif  // GG_MATCH_RENDERER_COLOR_SCHEME_COUNT_METHODS_H
