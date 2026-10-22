// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x42FC40 and 0x42FCB0.

#include "vector_class_ctor_methods.h"

// Placement new over caller-supplied storage. The constructor builds the
// elements in place with `new((void*)array) T[size]`; retail keeps the
// array-new counter preamble (`DEC EDI; MOV [ESP+0xC],EDI`) in that arm too:
// the element constructor is empty, so only the preamble survives. VC6 resolves
// the placement array form through this single-object signature; a
// `operator new[](size_t, void*)` overload does not compile.
inline void* __cdecl operator new(size_t, void* where)
{
    return where;
}

// FUNCTION: GAMEMD 0x42FC40
//
// VectorClass over a 0x10-byte element. Empty unless a size is given; over the
// caller's storage if one is supplied, over its own otherwise. A failed
// allocation still marks the vector as owning its storage.
//
// The caller-storage arm is a placement array-new (see the operator above);
// a plain pointer assignment there scores 27.9%.
WideVectorClass_0042FC40* WideVectorClass_0042FC40::Ctor(
        unsigned int size, const Wide_0042FC40* array)
{
    this->Vector = 0;
    this->Capacity = size;
    this->IsValid = 1;
    this->IsAllocated = 0;
    this->Vptr = VTBL_007E38F0;

    if (size) {
        if (array) {
            this->Vector = new((void*)array) Wide_0042FC40[size];
        } else {
            this->Vector = new Wide_0042FC40[size];
            this->IsAllocated = 1;
        }
    }
    return this;
}

// FUNCTION: GAMEMD 0x42FCB0
//
// The 4-byte-element instantiation, written out longhand rather than shared with
// the one above.
//
// Retail emits the array-new counter preamble (`DEC EDI; MOV [ESP+0xC],EDI`)
// in the caller-supplied-storage arm as well as the allocating arm: both arms
// are array-new expressions, the first a placement form over `array`. With a
// plain pointer assignment in the first arm the block appears once (28.6%).
NarrowVectorClass_0042FCB0* NarrowVectorClass_0042FCB0::Ctor(
        unsigned int size, const Narrow_0042FCB0* array)
{
    this->Vector = 0;
    this->Capacity = size;
    this->IsValid = 1;
    this->IsAllocated = 0;
    this->Vptr = VTBL_007E38D0;

    if (size) {
        if (array) {
            this->Vector = new((void*)array) Narrow_0042FCB0[size];
        } else {
            this->Vector = new Narrow_0042FCB0[size];
            this->IsAllocated = 1;
        }
    }
    return this;
}
