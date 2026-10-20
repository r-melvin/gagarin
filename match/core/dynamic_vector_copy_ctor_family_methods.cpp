// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001. These thirteen
//   functions are one copy constructor for a growable vector of pointers,
//   instantiated thirteen times. Every byte outside the two vtable constants,
//   the CALL dword ptr [vtable+0xC] displacement (always base vtable + 0xC)
//   and the `operator new` call displacement (always 0x7C8E17) is identical
//   across all thirteen, so the body is written once as a macro and expanded
//   per instantiation. Ordered ascending by retail address.
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

// FUNCTION: GAMEMD 0x004779E0
GG_DYNVEC_COPY_CTOR_BODY(007E4DB8, 007E4E78)

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

