// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//   This TU must build without /GX, now the project default: with exception
//   handling on, cl 8804 refuses to inline the vector destructor iterator and
//   emits an out-of-line call where retail has the five inlined instructions.
//   The same claim, with the same evidence, is already carried by
//   match/core/vector_object_sdd_family_methods.cpp for the destructor form of
//   this very vector.
//
// Eight Clear() members of a growable vector over an object element type:
// release the element block through the inlined vector destructor iterator
// when this vector owns one, then reset the pointer, the allocated flag and
// the capacity. Within each shape the members are byte-identical apart from
// the CRT free relocation, so one body serves each. Ordered ascending by
// retail address.

#include "object_vector_clear_family_methods.h"

// FUNCTION: GAMEMD 0x004E0950
GG_OVEC_CLEAR_BODY(004E0950)

// FUNCTION: GAMEMD 0x004E0AB0
GG_OVEC_CLEAR_COUNT_BODY(004E0AB0)

// FUNCTION: GAMEMD 0x0050E760
GG_OVEC_CLEAR_COUNT_BODY(0050E760)

// FUNCTION: GAMEMD 0x0050FD70
GG_OVEC_CLEAR_BODY(0050FD70)

// FUNCTION: GAMEMD 0x006F21B0
GG_OVEC_CLEAR_COUNT_BODY(006F21B0)

// FUNCTION: GAMEMD 0x006F2400
GG_OVEC_CLEAR_BODY(006F2400)

// FUNCTION: GAMEMD 0x00763EF0
GG_OVEC_CLEAR_COUNT_BODY(00763EF0)

// FUNCTION: GAMEMD 0x00764220
GG_OVEC_CLEAR_BODY(00764220)
