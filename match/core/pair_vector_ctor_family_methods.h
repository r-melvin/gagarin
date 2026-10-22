// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI at 0x5106E0 and its three siblings. Members come straight off
//   the instructions: the vtable pointer at +0 (`MOV dword ptr [EDI],imm32`),
//   the items pointer at +4, the capacity at +8 (`MOV [EDI+8],ESI`, ESI being
//   the requested count), a flag byte set to 1 at +0xC and the allocated flag
//   at +0xD. The element stride is 8 (`ADD EAX,8`) and each element is
//   constructed by two stores; two of the four instances store a dword at +4
//   of the element and two store a byte, which is the only content difference
//   in the family.
#ifndef GG_MATCH_CORE_PAIR_VECTOR_CTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_PAIR_VECTOR_CTOR_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x7C8E17 (decl; reloc) — CRT operator new / malloc.
extern "C" void* __cdecl gg_alloc(unsigned size);

// VTABLE: GAMEMD 0x007EA984
extern char VT_007EA984;
// VTABLE: GAMEMD 0x007EA9A4
extern char VT_007EA9A4;
// VTABLE: GAMEMD 0x007E177C
extern char VT_007E177C;
// VTABLE: GAMEMD 0x007F4154
extern char VT_007F4154;

// The eight-byte element: a dword key and a second field the element's own
// constructor zeroes. Two instances treat the second field as a dword and two
// as a byte, which is what the 0x89/0x88 opcode split in the family mask is.
struct PairElemD { int A; int B; };
struct PairElemB { int A; char B; char _pad[3]; };
GG_STATIC_ASSERT(sizeof(PairElemD) == 8 && sizeof(PairElemB) == 8);

struct PairVector
{
    char* Vptr;         // +0x0000
    void* Items;        // +0x0004
    int   Capacity;     // +0x0008
    char  IsValid;      // +0x000C
    char  IsAllocated;  // +0x000D
    char  _pad00E[2];   // +0x000E
};
GG_STATIC_ASSERT(offsetof(PairVector, Vptr)        == 0x0 &&
                 offsetof(PairVector, Items)       == 0x4 &&
                 offsetof(PairVector, Capacity)    == 0x8 &&
                 offsetof(PairVector, IsValid)     == 0xC &&
                 offsetof(PairVector, IsAllocated) == 0xD);

// Seat the vtable and the bookkeeping, then take the caller's storage if it
// supplied any and otherwise allocate a block of `count` elements; either way
// every element is zeroed before the pointer is published. Returns `this`.
//
// The allocate-and-zero step is an inline helper that returns the block, or
// null when the allocation failed. Inlining it is what gives retail's two
// tails (the loop-exit copy and the failure-entered copy with its own
// `XOR EAX,EAX`); the positive `if (p != 0) { ...; return p; } return 0;`
// spelling is the one that puts the zeroing loop before the failure arm.
// The earlier open-coded forms topped out at 82.5%.
#define GG_PAIR_VECTOR_CTOR_BODY(TAG, VT, ELEM)                           \
static inline ELEM* NewZeroed_##TAG(int n)                                \
{                                                                         \
    ELEM* p = (ELEM*)gg_alloc(n * 8);                                     \
    if (p != 0) {                                                         \
        ELEM* q = p;                                                      \
        for (int i = n - 1; i >= 0; i--) {                                \
            q->A = 0;                                                     \
            q->B = 0;                                                     \
            q++;                                                          \
        }                                                                 \
        return p;                                                         \
    }                                                                     \
    return 0;                                                             \
}                                                                         \
PairVector* __fastcall FUN_##TAG(PairVector* self, int, int count,        \
                                 ELEM* storage)                           \
{                                                                         \
    self->Items = 0;                                                      \
    self->Capacity = count;                                               \
    self->IsValid = 1;                                                    \
    self->IsAllocated = 0;                                                \
    self->Vptr = &VT_##VT;                                                \
    if (count != 0) {                                                     \
        if (storage != 0) {                                               \
            ELEM* p = storage;                                            \
            for (int i = count - 1; i >= 0; i--) {                        \
                p->A = 0;                                                 \
                p->B = 0;                                                 \
                p++;                                                      \
            }                                                             \
            self->Items = storage;                                        \
            return self;                                                  \
        }                                                                 \
        self->Items = NewZeroed_##TAG(count);                             \
        self->IsAllocated = 1;                                            \
    }                                                                     \
    return self;                                                          \
}

#endif  // GG_MATCH_CORE_PAIR_VECTOR_CTOR_FAMILY_METHODS_H
