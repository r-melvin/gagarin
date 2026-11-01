// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 at each address
//   below. Each of these eight functions is the scalar-deleting destructor of
//   one vector instantiation whose elements are polymorphic objects: reseat
//   the vtable, array-delete the element block through the element type's own
//   slot-0 deleting destructor if this vector owns one, clear the bookkeeping,
//   and free the object itself when the caller asked for it. Per-instance
//   variation is the vtable constant at +0 and the CALL displacement to the
//   CRT free; everything else is identical, so the body is written once as a
//   macro. Ordered ascending by retail address.

#include "vector_polymorphic_sdd_family_methods.h"

// FUNCTION: GAMEMD 0x00765B60
GG_VECTOR_POLY_SDD_BODY(00765B60, 007F6F7C)

// FUNCTION: GAMEMD 0x00765C20
GG_VECTOR_POLY_SDD_BODY(00765C20, 007F6F7C)

// FUNCTION: GAMEMD 0x00766FC0
GG_VECTOR_POLY_SDD_BODY(00766FC0, 007F6FF4)

// FUNCTION: GAMEMD 0x00767080
GG_VECTOR_POLY_SDD_BODY(00767080, 007F6FF4)

// FUNCTION: GAMEMD 0x0076A5C0
GG_VECTOR_POLY_SDD_BODY(0076A5C0, 007F7184)

// FUNCTION: GAMEMD 0x0076A680
GG_VECTOR_POLY_SDD_BODY(0076A680, 007F7184)

// FUNCTION: GAMEMD 0x0076BBC0
GG_VECTOR_POLY_SDD_BODY(0076BBC0, 007F7230)

// FUNCTION: GAMEMD 0x0076BC10
GG_VECTOR_POLY_SDD_BODY(0076BC10, 007F7230)
