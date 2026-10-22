// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x42F670.

#include "dynamic_vector_ctor_methods.h"

VectorClass_0042F670::~VectorClass_0042F670() {}

// FUNCTION: GAMEMD 0x42F670
//
// MATCHED 100% (37/37). The caller-supplied-storage arm is placement
// array-new over the incoming block, `Vector = new((void*)array)
// Elem_0042F670[size];`, which is what puts retail's array-new counter
// preamble (`DEC EDI; MOV [ESP+0xC],EDI`) in that arm as well as in the
// allocating one. The TU declares the ordinary `operator new`/`operator new[]`
// alongside the placement overloads, otherwise VC6 hides the one-argument
// array form and the allocating arm fails to compile.
//
// Construct a growable vector, either over storage the caller supplies or over
// storage of its own. A zero size leaves it empty and allocates nothing; a
// failed allocation still marks the vector as owning its storage, which is what
// the `MOV byte [ESI+0xD],1` after the null path at 0x42F6C6 records.
DynamicVectorClass_0042F670::DynamicVectorClass_0042F670(
        unsigned int size, const Elem_0042F670* array)
    : VectorClass_0042F670(size, array)
{
    CapacityIncrement = 10;
    Count = 0;
}
