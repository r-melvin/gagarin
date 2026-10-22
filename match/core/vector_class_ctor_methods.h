// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x42FCB0 and 0x42FC40. The two differ only in element size —
//   0x42FCB0 scales by 4 (`LEA EAX,[EDI*4]`) and 0x42FC40 by 0x10
//   (`MOV EAX,EDI; SHL EAX,4`, since LEA cannot scale by sixteen) — and in their
//   vtables, 0x7E38D0 against 0x7E38F0. Layout is the VectorClass one asserted below. See re_findings §19 for the family.
#ifndef GG_MATCH_CORE_VECTOR_CLASS_CTOR_METHODS_H
#define GG_MATCH_CORE_VECTOR_CLASS_CTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x7E38D0 — the 4-byte-element instantiation.
extern void* const VTBL_007E38D0[];
// VTABLE: GAMEMD 0x7E38F0 — the 0x10-byte-element instantiation.
extern void* const VTBL_007E38F0[];

// Both element types carry a user-declared default constructor. That is what
// makes `new T[n]` emit the vector-constructor-iterator preamble — `DEC` the
// count and spill it — which is retail's 0x42FCFF/0x42FD03 pair. See section 4.6.
struct Narrow_0042FCB0
{
    int Value;
    Narrow_0042FCB0() {}
};
GG_STATIC_ASSERT(sizeof(Narrow_0042FCB0) == 4);

struct Wide_0042FC40
{
    int A, B, C, D;
    Wide_0042FC40() {}
};
GG_STATIC_ASSERT(sizeof(Wide_0042FC40) == 0x10);

struct NarrowVectorClass_0042FCB0
{
    const void* Vptr;             // +0x0000
    Narrow_0042FCB0* Vector;      // +0x0004
    int  Capacity;               // +0x0008
    char IsValid;                 // +0x000C
    char IsAllocated;             // +0x000D

    // FUNCTION: GAMEMD 0x42FCB0
    NarrowVectorClass_0042FCB0* Ctor(unsigned int size,
                                     const Narrow_0042FCB0* array);
};
GG_STATIC_ASSERT(offsetof(NarrowVectorClass_0042FCB0, IsAllocated) == 0xD);

struct WideVectorClass_0042FC40
{
    const void* Vptr;             // +0x0000
    Wide_0042FC40* Vector;        // +0x0004
    int  Capacity;               // +0x0008
    char IsValid;                 // +0x000C
    char IsAllocated;             // +0x000D

    // FUNCTION: GAMEMD 0x42FC40
    WideVectorClass_0042FC40* Ctor(unsigned int size,
                                   const Wide_0042FC40* array);
};

#endif  // GG_MATCH_CORE_VECTOR_CLASS_CTOR_METHODS_H
