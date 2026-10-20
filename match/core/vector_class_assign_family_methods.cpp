// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001. These twelve
//   functions are literally the same 108 bytes, `operator new` displacement
//   included, so the family has no per-instance variation whatsoever: one
//   macro body, expanded once per class. Ordered ascending by retail address.
//
// Phrasing note: the allocation-failure path falls through to the plain
// `return *this;`, NOT to the Items=0/IsAllocated=false tail — only a zero
// capacity reaches that. Writing the reset as the `else` arm of
// `if (Capacity != 0) { ... } else { ... }` is what lays the allocating arm
// inline and parks the reset block after the returning tail, which is retail's
// block order. Spelling it as a shared fallthrough tail costs exactly one
// instruction (a 97.6% plateau on both families).

#include "vector_class_assign_family_methods.h"

// FUNCTION: GAMEMD 0x00478720
GG_VECASSIGN_BODY(00478720)

// FUNCTION: GAMEMD 0x004787E0
GG_VECASSIGN_BODY(004787E0)

// FUNCTION: GAMEMD 0x00512BD0
GG_VECASSIGN_BODY(00512BD0)

// FUNCTION: GAMEMD 0x00512FA0
GG_VECASSIGN_BODY(00512FA0)

// FUNCTION: GAMEMD 0x00513370
GG_VECASSIGN_BODY(00513370)

// FUNCTION: GAMEMD 0x00525060
GG_VECASSIGN_BODY(00525060)

// FUNCTION: GAMEMD 0x0067AA80
GG_VECASSIGN_BODY(0067AA80)

// FUNCTION: GAMEMD 0x0067AE00
GG_VECASSIGN_BODY(0067AE00)

// FUNCTION: GAMEMD 0x0067B180
GG_VECASSIGN_BODY(0067B180)

// FUNCTION: GAMEMD 0x0067BFA0
GG_VECASSIGN_BODY(0067BFA0)

// FUNCTION: GAMEMD 0x006F2780
GG_VECASSIGN_BODY(006F2780)

// FUNCTION: GAMEMD 0x00717C00
GG_VECASSIGN_BODY(00717C00)

