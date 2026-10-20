// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Twelve remaining copy-constructor-shaped bodies are represented by
// address-scoped four-byte-element layout views. Their raw code agrees apart
// from the two vtable constants, the base Clear-slot address and allocator
// call displacement. This does not establish their original template element
// types, declaring classes or translation-unit boundaries. The RTTI-confirmed
// DynamicVectorClass<int> entry 0x4779E0 now lives in vector_int_methods.cpp.
// Ordered by ascending retail address.
//
// Phrasing note: the allocation-failure path falls through to the plain
// `return *this;`, NOT to the Items=0/IsAllocated=false tail — only a zero
// capacity reaches that. Writing the reset as the `else` arm of
// `if (Capacity != 0) { ... } else { ... }` is what lays the allocating arm
// inline and parks the reset block after the returning tail, which is retail's
// block order. Spelling it as a shared fallthrough tail costs exactly one
// instruction (a 97.6% plateau on both families).

#include "dynamic_vector_copy_ctor_family_methods.h"

// FUNCTION: GAMEMD 0x004777B0
GG_DYNVEC_COPY_CTOR_BODY(007E4DB8, 007E4DD8)

// FUNCTION: GAMEMD 0x0050E830
GG_DYNVEC_COPY_CTOR_BODY(007EA9E4, 007EAAE8)

// FUNCTION: GAMEMD 0x00513740
GG_DYNVEC_COPY_CTOR_BODY(007EAC48, 007EABE8)

// FUNCTION: GAMEMD 0x005137D0
GG_DYNVEC_COPY_CTOR_BODY(007EAC68, 007EABC8)

// FUNCTION: GAMEMD 0x00513860
GG_DYNVEC_COPY_CTOR_BODY(007EAC28, 007EAC88)

// FUNCTION: GAMEMD 0x005255F0
GG_DYNVEC_COPY_CTOR_BODY(007EB6F4, 007EB6D4)

// FUNCTION: GAMEMD 0x005AD660
GG_DYNVEC_COPY_CTOR_BODY(007EAA08, 007ED90C)

// FUNCTION: GAMEMD 0x005C4F30
GG_DYNVEC_COPY_CTOR_BODY(007EE3D0, 007EE3F0)

// FUNCTION: GAMEMD 0x0067C1F0
GG_DYNVEC_COPY_CTOR_BODY(007F0D5C, 007F0D3C)

// FUNCTION: GAMEMD 0x0067C280
GG_DYNVEC_COPY_CTOR_BODY(007F0D7C, 007F0D1C)

// FUNCTION: GAMEMD 0x00717D20
GG_DYNVEC_COPY_CTOR_BODY(007E4424, 007F4F9C)

// FUNCTION: GAMEMD 0x0075E6B0
GG_DYNVEC_COPY_CTOR_BODY(007F0D5C, 007F0DCC)

