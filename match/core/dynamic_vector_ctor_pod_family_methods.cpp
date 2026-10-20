// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Bytes matched against retail gamemd.exe v1.001.
//
// DynamicVectorClass<T>(size, array) over 4-byte element types, 8 remaining retail
// instantiations. Each body runs the inlined VectorClass base constructor —
// zero the element pointer, record the capacity, mark the vector valid and
// not-owning, install the base vtable, then for a non-zero size either adopt
// the caller's storage or allocate and take ownership — and afterwards seats
// the derived vtable, sets the growth step to 10 and clears the active count.
//
// Per-instance variation is the two vtable constants only. Bodies are ordered
// ascending by retail address.
#include "dynamic_vector_ctor_pod_family_methods.h"

// FUNCTION: GAMEMD 0x0049ECD0
// VTABLE: GAMEMD 0x7E5C04
// VTABLE: GAMEMD 0x7E5BE4
GG_DYNVECTOR_CTOR_POD_BODY(DynamicVectorClass_0049ECD0, 0x7E5C04, 0x7E5BE4)

// FUNCTION: GAMEMD 0x005D86D0
// VTABLE: GAMEMD 0x7EED40
// VTABLE: GAMEMD 0x7EED20
GG_DYNVECTOR_CTOR_POD_BODY(DynamicVectorClass_005D86D0, 0x7EED40, 0x7EED20)

// FUNCTION: GAMEMD 0x0063DEC0
// VTABLE: GAMEMD 0x7EFF04
// VTABLE: GAMEMD 0x7EFEE4
GG_DYNVECTOR_CTOR_POD_BODY(DynamicVectorClass_0063DEC0, 0x7EFF04, 0x7EFEE4)

// FUNCTION: GAMEMD 0x0063E1D0
// VTABLE: GAMEMD 0x7EFF24
// VTABLE: GAMEMD 0x7EFEC4
GG_DYNVECTOR_CTOR_POD_BODY(DynamicVectorClass_0063E1D0, 0x7EFF24, 0x7EFEC4)

// FUNCTION: GAMEMD 0x006B83A0
// VTABLE: GAMEMD 0x7F36D4
// VTABLE: GAMEMD 0x7F36B4
GG_DYNVECTOR_CTOR_POD_BODY(DynamicVectorClass_006B83A0, 0x7F36D4, 0x7F36B4)

// FUNCTION: GAMEMD 0x006F2230
// VTABLE: GAMEMD 0x7EA9E4
// VTABLE: GAMEMD 0x7EAAE8
GG_DYNVECTOR_CTOR_POD_BODY(DynamicVectorClass_006F2230, 0x7EA9E4, 0x7EAAE8)

// FUNCTION: GAMEMD 0x007342D0
// VTABLE: GAMEMD 0x7E180C
// VTABLE: GAMEMD 0x7E17AC
GG_DYNVECTOR_CTOR_POD_BODY(DynamicVectorClass_007342D0, 0x7E180C, 0x7E17AC)

// FUNCTION: GAMEMD 0x007632D0
// VTABLE: GAMEMD 0x7ED480
// VTABLE: GAMEMD 0x7ED9BC
GG_DYNVECTOR_CTOR_POD_BODY(DynamicVectorClass_007632D0, 0x7ED480, 0x7ED9BC)
