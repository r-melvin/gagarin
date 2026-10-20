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
// Seat the vtable and the bookkeeping, then take the caller's storage if it
// supplied any and otherwise allocate a block of `count` elements; either way
// every element is zeroed before the pointer is published. Returns `this`.
//
// PARTIAL, 82.5%. The whole prologue, both zeroing loops, the storage branch
// and the allocation branch are instruction-for-instruction exact, registers
// included. Two residuals remain:
//   1. Retail keeps two copies of the "publish the block and set the allocated
//      flag" tail, one for the loop-exit path and one entered from the
//      allocation-failure path (which materialises the null with its own
//      `XOR EAX,EAX` before falling into the shared stores). cl 8804 merges
//      the two into one tail, so the compiled body is eight instructions
//      shorter. The register allocation is coupled to this: every spelling
//      that gets the two copies (an explicit `if (block == 0) { ...; return; }`
//      arm, an if/else, an early-return success arm, and the same three with
//      the loop hoisted into an inline helper per the ninth batch's un-merge
//      lever) swaps ESI and EDI and drops to 36.5-57.1%, while every spelling
//      that merges keeps retail's ESI=count / EDI=this and scores 82.5%.
//   2. The single `XOR EAX,EAX` of that failure path. Writing the store as
//      `self->Items = block` with `block` known null, and as a literal 0, give
//      the same code.
// The translation-unit-shape lever does not reach this one. The same body was
// compiled alone in a file and with two, three, four, five and eight siblings:
// 82.5% in every case, so cl's decision to merge the two tails here is not the
// cross-jumping that a sibling function suppresses. Six more spellings were
// measured in one compile and all confirm the coupling recorded above - the
// loop-entered arm returning on its own 52.4%, a peeled `do/while` with the
// trip test repeated after the advance 55.6%, an early return on allocation
// failure 36.5%, a volatile publish in the loop arm only 57.1%, and `count - 1`
// hoisted into its own local ahead of a duplicated tail 52.4%.
//
// MEMBER-VERSUS-FREE, and the C front end: both refuted this pass. The body is
// written as a free `__fastcall` function with an explicit self parameter,
// which the nineteenth batch warns inverts the ranking of a member function's
// variants. Re-measured as a real `__thiscall` member of a cloned class it is
// 82.5%, byte-identical to the free form, and the duplicated-tail arm is 36.5%
// as a member exactly as it is as a free function -- so the harness shape is
// not hiding a winner here. Compiled as `.c` (batch thirty-nine) the same two
// arms score 82.5% and 36.5%, the same numbers again. A flag sweep over nine
// sets (/GX and /Gy on and off, /Ox, /O1, /Og /Oi /Ot /Oy /Ob1, /Op, /Gr) moves
// nothing except /O1, which collapses it to 22.2%. The tail fold is neither a
// front-end nor a flag effect.
//
// Eight spellings were measured. Four loop forms were also measured on the way
// in: only `for (i = count - 1; i >= 0; i--)` over a walked pointer produces
// retail's `LEA ECX,[ESI-1]; CMP; JL; INC ECX` trip-count preamble (4.8% for
// the index form, 57.1% for that loop alone before the tail work).
#define GG_PAIR_VECTOR_CTOR_BODY(TAG, VT, ELEM)                           \
PairVector* __fastcall FUN_##TAG(PairVector* self, int, int count,        \
                                 ELEM* storage)                           \
{                                                                         \
    int i;                                                                \
    ELEM* p;                                                              \
    self->Items = 0;                                                      \
    self->Capacity = count;                                               \
    self->IsValid = 1;                                                    \
    self->IsAllocated = 0;                                                \
    self->Vptr = &VT_##VT;                                                \
    if (count != 0) {                                                     \
        if (storage != 0) {                                               \
            p = storage;                                                  \
            for (i = count - 1; i >= 0; i--) {                            \
                p->A = 0;                                                 \
                p->B = 0;                                                 \
                p++;                                                      \
            }                                                             \
            self->Items = storage;                                        \
            return self;                                                  \
        }                                                                 \
        {                                                                 \
            ELEM* block = (ELEM*)gg_alloc(count * 8);                     \
            if (block != 0) {                                             \
                p = block;                                                \
                for (i = count - 1; i >= 0; i--) {                        \
                    p->A = 0;                                             \
                    p->B = 0;                                             \
                    p++;                                                  \
                }                                                         \
            }                                                             \
            self->Items = block;                                          \
            self->IsAllocated = 1;                                        \
            return self;                                                  \
        }                                                                 \
    }                                                                     \
    return self;                                                          \
}

#endif  // GG_MATCH_CORE_PAIR_VECTOR_CTOR_FAMILY_METHODS_H
