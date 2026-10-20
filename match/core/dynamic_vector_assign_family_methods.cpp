// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 at each address
//   below. These six functions are one copy-assignment operator for the
//   derived growable vector of pointers, instantiated six times on a
//   contiguous 0x80 address stride. Every byte outside the single
//   `operator new` call displacement is identical across all six, so the body
//   is written once as a macro and expanded per instantiation. Ordered
//   ascending by retail address.
//
// Phrasing note, inherited from the sibling families in
// vector_class_assign_family_methods.cpp and
// vector_copy_constructors.cpp: the allocation-failure path
// falls through to the plain `return *this;`, NOT to the Items=0/IsAllocated=
// false tail, so the reset has to be the `else` arm of `if (Capacity != 0)`.
// The three derived-member copies go outside the self-assignment guard, which
// is what inlining a base `operator=` that carries its own guard produces.

#include "dynamic_vector_assign_family_methods.h"

// FUNCTION: GAMEMD 0x0067A090
GG_DYNVEC_ASSIGN_BODY(0067A090)

// FUNCTION: GAMEMD 0x0067A110
GG_DYNVEC_ASSIGN_BODY(0067A110)

// FUNCTION: GAMEMD 0x0067A190
GG_DYNVEC_ASSIGN_BODY(0067A190)

// FUNCTION: GAMEMD 0x0067A210
GG_DYNVEC_ASSIGN_BODY(0067A210)

// FUNCTION: GAMEMD 0x0067A290
GG_DYNVEC_ASSIGN_BODY(0067A290)

// FUNCTION: GAMEMD 0x0067A310
GG_DYNVEC_ASSIGN_BODY(0067A310)
