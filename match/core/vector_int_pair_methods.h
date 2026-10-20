// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Every offset and call target below was read numerically off the user's own
//   retail gamemd.exe v1.001 through the local Ghidra CLI. EA's GPLv3 Red
//   Alert 1 release (CODE/VECTOR.H) was read for the member and method NAMES
//   and for the shape of each loop only; nothing is transcribed from it.
//
// The dword-element VectorClass / DynamicVectorClass pair at
// 0x660CB0-0x660F75. Eight bodies: the lookup, subscript and comparison
// operators of the plain vector, both resize forms, and three instantiations
// of the two `ID` overloads.
//
// HOW THE RUN WAS FOUND. The whole 0x660460-0x662240 range was swept as raw
// bytes (`ghidra memory read` piped through `objdump -D -b binary -m i386`) and
// its entry points taken from the 0x90 pad runs that end on a four-byte
// boundary; that found 73 candidates where the Ghidra function list knows
// about 38. Three of the nine bodies here - 0x660CD0, 0x660E40 and 0x660F10 -
// are not in the function list at all, and 0x660F10 has NO pad in front of it:
// it starts on the four-byte boundary immediately after the `RET 8` that ends
// the resize at 0x660E60. An aligned address directly after a terminating
// return is therefore an entry candidate in its own right, not only a
// pad-preceded one.
//
// The neighbouring destructors at 0x660C80, 0x660DD0, 0x660F80 and 0x660FD0
// are already matched in match/core/vector_counted_dtor_family_methods.cpp,
// match/core/vector_plain_dtor_family_methods.cpp and
// match/core/vector_dtor_family_methods.cpp, which is what confirms the
// layout used here belongs to these two classes and not to a lookalike.
//
// The two resize bodies reuse VectorBase::ResizeBase from
// match/core/vector_resize_methods.h verbatim rather than redeclaring the
// layout, so this TU cannot drift from the 38 instantiations already matched
// there; 0x660E60 is the DynamicVectorClass wrapper with the ActiveCount clamp
// (0xB0 bytes, the family's own size) and 0x660D20 is the plain VectorClass
// form without it (0xAE bytes).
#ifndef GG_MATCH_CORE_VECTOR_INT_PAIR_METHODS_H
#define GG_MATCH_CORE_VECTOR_INT_PAIR_METHODS_H

#include "vector_resize_methods.h"

// The layout is VectorBase's, re-confirmed against this run's own accesses:
//   +0x04 Vector       `MOV EDX,[ECX+4]` at 0x660CC0, indexed `[EAX+ECX*4]` at
//                      0x660CD7, so the element width is four.
//   +0x08 Length       `MOV ESI,[ECX+8]` at 0x660CE2 and `[EDI+8]` at 0x660CEA.
//   +0x0C IsValid      `MOV AL,[ECX+0xC]` at 0x660CB0, 0x660E00 and 0x660E40.
//   +0x0D IsAllocated  `CMP [ESI+0xD],BL` at 0x660DDD.
//   +0x10 ActiveCount  `MOV EDX,[ECX+0x10]` at 0x660F10 and 0x660F50.
GG_STATIC_ASSERT(offsetof(VectorBase, Vector)      == 0x04);
GG_STATIC_ASSERT(offsetof(VectorBase, Length)      == 0x08);
GG_STATIC_ASSERT(offsetof(VectorBase, IsValid)     == 0x0C);
GG_STATIC_ASSERT(offsetof(VectorBase, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(VectorBase, ActiveCount) == 0x10);
GG_STATIC_ASSERT(sizeof(VectorBase) == 0x14);

struct VectorIntPair : VectorBase
{
    // FUNCTION: GAMEMD 0x660CB0  VectorClass::ID(const T*)
    int  ID_00660CB0(const int* ptr) const;
    // FUNCTION: GAMEMD 0x660CD0  VectorClass::operator[]
    int  Item_00660CD0(int index) const;
    // FUNCTION: GAMEMD 0x660CE0  VectorClass::operator==
    bool Equals_00660CE0(const VectorIntPair& other) const;
    // FUNCTION: GAMEMD 0x660D20  VectorClass::Resize
    bool Resize_00660D20(int newsize, void** array);
    // FUNCTION: GAMEMD 0x660E00  VectorClass::ID(const T&)
    int  ID_00660E00(const int& object) const;
    // FUNCTION: GAMEMD 0x660E40  VectorClass::ID(const T*)
    int  ID_00660E40(const int* ptr) const;
    // FUNCTION: GAMEMD 0x660E60  DynamicVectorClass::Resize
    bool Resize_00660E60(int newsize, void** array);
    // FUNCTION: GAMEMD 0x660F50  DynamicVectorClass::ID(const T&)
    int  ID_00660F50(const int& object) const;
};

#endif  // GG_MATCH_CORE_VECTOR_INT_PAIR_METHODS_H
