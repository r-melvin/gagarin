// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x42F670. The member layout and the constructor's shape
//   are the RA1 VectorClass/DynamicVectorClass pair (structure reference only,
//   not transcribed): vptr, Vector, VectorMax, IsValid, IsAllocated, then
//   ActiveCount and GrowthStep on the derived class, with GrowthStep seeded to
//   10 — which is the `MOV [ESI+0x14],0xA` at 0x42F6D0.
#ifndef GG_MATCH_CORE_DYNAMIC_VECTOR_CTOR_METHODS_H
#define GG_MATCH_CORE_DYNAMIC_VECTOR_CTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// A 4-byte element with a user-declared default constructor. The declaration is
// load-bearing: `new T[n]` on such a class emits VC6's
// vector-constructor-iterator preamble (`DEC` the count, spill it) and then
// elides the loop because the body is empty, which is retail's 0x42F6BA/0x42F6BB
// pair. A POD element compiles to a bare `operator new` with no counter.
// TU-local placement forms: `new((void*)array) T[size]` is what puts retail's
// array-new counter preamble (`DEC EDI; MOV [ESP+0xC],EDI`) in the
// caller-supplied-storage arm as well as the allocating one.
void* __cdecl operator new(size_t);
void* __cdecl operator new[](size_t);
inline void* operator new(size_t, void* where) { return where; }
inline void* operator new[](size_t, void* where) { return where; }

struct Elem_0042F670
{
    int Value;
    Elem_0042F670() {}
};
GG_STATIC_ASSERT(sizeof(Elem_0042F670) == 4);

struct VectorClass_0042F670
{
    // VTABLE: GAMEMD 0x7E38D0
    Elem_0042F670* Vector;   // +0x0004
    int  VectorMax;          // +0x0008
    bool IsValid;            // +0x000C
    bool IsAllocated;        // +0x000D

    // Defined in the class body so it is implicitly inline: retail has no call
    // between the member stores and the derived class's vptr store, so the base
    // constructor is inlined into 0x42F670. Defined out of line in the same TU it
    // stays a call and the target function comes out at 14 instructions against
    // retail's 37.
    VectorClass_0042F670(unsigned int size, const Elem_0042F670* array)
        : Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
    {
        if (size) {
            if (array) {
                Vector = new((void*)array) Elem_0042F670[size];
            } else {
                Vector = new Elem_0042F670[size];
                IsAllocated = true;
            }
        }
    }

    virtual ~VectorClass_0042F670();
};
GG_STATIC_ASSERT(offsetof(VectorClass_0042F670, Vector) == 0x4);
GG_STATIC_ASSERT(offsetof(VectorClass_0042F670, VectorMax) == 0x8);
GG_STATIC_ASSERT(offsetof(VectorClass_0042F670, IsValid) == 0xC);
GG_STATIC_ASSERT(offsetof(VectorClass_0042F670, IsAllocated) == 0xD);

struct DynamicVectorClass_0042F670 : VectorClass_0042F670
{
    // VTABLE: GAMEMD 0x7E3890
    int ActiveCount;         // +0x0010
    int GrowthStep;          // +0x0014

    // FUNCTION: GAMEMD 0x42F670
    DynamicVectorClass_0042F670(unsigned int size, const Elem_0042F670* array);
};
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_0042F670, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass_0042F670, GrowthStep) == 0x14);

#endif  // GG_MATCH_CORE_DYNAMIC_VECTOR_CTOR_METHODS_H
