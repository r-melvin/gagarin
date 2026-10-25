// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail RTTI binds the vtables stored by 0x5106E0, 0x510780, 0x58AC70 and
//   0x6CF8F0 (0x7EA984, 0x7EA9A4, 0x7E177C, 0x7F4154) to VectorClass over
//   AngerStruct, ScoutStruct, SubzoneConnectionStruct and SwizzlePointerClass.
//   Each body is VectorClass<T>(int, T*) with the element default constructor
//   inlined: stride 8, two stores per element. Two element types store a dword
//   at +4 and two store a byte. The other slots of these vtables, and of
//   DynamicVectorClass<SubzoneConnectionStruct> (0x7ED5A0), are bound in
//   pair_vector_ctor_family_methods.cpp.
#ifndef GG_MATCH_CORE_PAIR_VECTOR_CTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_PAIR_VECTOR_CTOR_FAMILY_METHODS_H

#include "vector_class_operations.h"

// Field names are unconfirmed placeholders; only the widths come from the
// stores. The element comparisons have no out-of-line retail bodies: they are
// inlined into VectorClass<T>::operator== (0x50EE80, 0x50F1B0, 0x40B140,
// 0x6CF560), and their shape is read from those loops. AngerStruct compares
// both dwords and ScoutStruct the dword and then the byte.
// SubzoneConnectionStruct and SwizzlePointerClass compare only the first
// dword; retail never reads +4 in their loops.
// AngerStruct, ScoutStruct and SubzoneConnectionStruct have a memberwise copy
// constructor; SwizzlePointerClass does not. Evidence: Slot6 returns T by
// value. In 0x50E5B0, 0x50E620 and 0x40B120, retail forms the element address
// with LEA and copies the members through it, and 0x40B120 copies +4 as a
// byte. 0x6CF540 copies SwizzlePointerClass as two dwords with no LEA, which
// is cl's implicit bitwise copy.
#include "../_layout/anger_scout_struct.h"

struct SubzoneConnectionStruct {
    SubzoneConnectionStruct() : A(0), B(0) {}
    SubzoneConnectionStruct(const SubzoneConnectionStruct& o) : A(o.A), B(o.B) {}
    bool operator==(const SubzoneConnectionStruct& o) const { return A == o.A; }
    bool operator!=(const SubzoneConnectionStruct& o) const { return !(*this == o); }
    int A;   // +0x0
    char B;  // +0x4
};
class SwizzlePointerClass {
public:
    SwizzlePointerClass() : A(0), B(0) {}
    bool operator==(const SwizzlePointerClass& o) const { return A == o.A; }
    bool operator!=(const SwizzlePointerClass& o) const { return !(*this == o); }
    int A;  // +0x0
    int B;  // +0x4
};
GG_STATIC_ASSERT(sizeof(SubzoneConnectionStruct) == 8 && sizeof(SwizzlePointerClass) == 8);

#endif  // GG_MATCH_CORE_PAIR_VECTOR_CTOR_FAMILY_METHODS_H
