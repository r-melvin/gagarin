// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: disassembly of 0x510920 against the VectorClass<T>(size, array) family in
//   vector_ctor_pod_family_methods.cpp; the vtable constant 0x7EAA5C is VectorClass<bool>.
//
// VectorClass<bool>(size, array). Address index: 0x510920.

#include "vector_ctor_pod_family_methods.h"

// One-byte element: `new bool[size]` has no scaling shift.
struct PodElem1 { char Value; };
GG_STATIC_ASSERT(sizeof(PodElem1) == 1);

GG_VECTOR_CTOR_POD_DECL(VectorClass_00510920, PodElem1);

// FUNCTION: GAMEMD 0x510920
// vtable constant: 0x7EAA5C
GG_VECTOR_CTOR_POD_BODY(VectorClass_00510920, PodElem1, 0x7EAA5C)
