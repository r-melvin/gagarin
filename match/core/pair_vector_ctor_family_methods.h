// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail RTTI binds the vtables stored by 0x5106E0, 0x510780, 0x58AC70 and
//   0x6CF8F0 (0x7EA984, 0x7EA9A4, 0x7E177C, 0x7F4154) to VectorClass over
//   AngerStruct, ScoutStruct, SubzoneConnectionStruct and SwizzlePointerClass.
//   Each body is VectorClass<T>(int, T*) with the element default constructor
//   inlined: stride 8, two stores per element. Two element types store a dword
//   at +4 and two store a byte.
#ifndef GG_MATCH_CORE_PAIR_VECTOR_CTOR_FAMILY_METHODS_H
#define GG_MATCH_CORE_PAIR_VECTOR_CTOR_FAMILY_METHODS_H

#include "vector_class_operations.h"

// Field names are unconfirmed placeholders; only the widths come from the
// stores. operator== and operator!= are modelled, not recovered: the
// explicitly instantiated VectorClass<T>::operator== needs an element
// comparison, and no retail body for these element comparisons has been
// identified. The memberwise form is an assumption.
struct AngerStruct {
    AngerStruct() : A(0), B(0) {}
    bool operator==(const AngerStruct& o) const { return A == o.A && B == o.B; }
    bool operator!=(const AngerStruct& o) const { return !(*this == o); }
    int A;  // +0x0
    int B;  // +0x4
};
struct ScoutStruct {
    ScoutStruct() : A(0), B(0) {}
    bool operator==(const ScoutStruct& o) const { return A == o.A && B == o.B; }
    bool operator!=(const ScoutStruct& o) const { return !(*this == o); }
    int A;   // +0x0
    char B;  // +0x4
};
struct SubzoneConnectionStruct {
    SubzoneConnectionStruct() : A(0), B(0) {}
    bool operator==(const SubzoneConnectionStruct& o) const { return A == o.A && B == o.B; }
    bool operator!=(const SubzoneConnectionStruct& o) const { return !(*this == o); }
    int A;   // +0x0
    char B;  // +0x4
};
class SwizzlePointerClass {
public:
    SwizzlePointerClass() : A(0), B(0) {}
    bool operator==(const SwizzlePointerClass& o) const { return A == o.A && B == o.B; }
    bool operator!=(const SwizzlePointerClass& o) const { return !(*this == o); }
    int A;  // +0x0
    int B;  // +0x4
};
GG_STATIC_ASSERT(sizeof(AngerStruct) == 8 && sizeof(ScoutStruct) == 8);
GG_STATIC_ASSERT(sizeof(SubzoneConnectionStruct) == 8 && sizeof(SwizzlePointerClass) == 8);
GG_STATIC_ASSERT(offsetof(ScoutStruct, B) == 4 && offsetof(AngerStruct, B) == 4);

#endif  // GG_MATCH_CORE_PAIR_VECTOR_CTOR_FAMILY_METHODS_H
