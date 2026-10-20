// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Bytes matched against retail gamemd.exe v1.001.
//
// VectorClass<T>(size, array) over trivial element types, 41 remaining retail
// instantiations. Each body zeroes the element pointer, records the capacity,
// marks the vector valid and not-owning, installs its vtable, and then — only
// for a non-zero size — either adopts the caller's storage (no allocation, no
// ownership) or allocates its own array and takes ownership of it.
//
// The only per-instance variation is the vtable constant stored at +0 and the
// element width feeding `new T[size]` (4 bytes everywhere except 0x5ADAB0,
// which scales by 8). The shared body is GG_VECTOR_CTOR_POD_BODY; the bodies
// below are ordered ascending by retail address.
#include "vector_ctor_pod_family_methods.h"

// FUNCTION: GAMEMD 0x488080
// vtable constant: 0x7E4514
GG_VECTOR_CTOR_POD_BODY(VectorClass_00488080, PodElem4, 0x7E4514)

// FUNCTION: GAMEMD 0x48B070
// vtable constant: 0x7E5144
GG_VECTOR_CTOR_POD_BODY(VectorClass_0048B070, PodElem4, 0x7E5144)

// FUNCTION: GAMEMD 0x49F090
// vtable constant: 0x7E5C04
GG_VECTOR_CTOR_POD_BODY(VectorClass_0049F090, PodElem4, 0x7E5C04)

// FUNCTION: GAMEMD 0x4A4E30
// vtable constant: 0x7E5DEC
GG_VECTOR_CTOR_POD_BODY(VectorClass_004A4E30, PodElem4, 0x7E5DEC)

// FUNCTION: GAMEMD 0x4BA2F0
// vtable constant: 0x7E8500
GG_VECTOR_CTOR_POD_BODY(VectorClass_004BA2F0, PodElem4, 0x7E8500)

// FUNCTION: GAMEMD 0x4BA340
// vtable constant: 0x7E8520
GG_VECTOR_CTOR_POD_BODY(VectorClass_004BA340, PodElem4, 0x7E8520)

// FUNCTION: GAMEMD 0x4CABF0
// vtable constant: 0x7E8954
GG_VECTOR_CTOR_POD_BODY(VectorClass_004CABF0, PodElem4, 0x7E8954)

// FUNCTION: GAMEMD 0x4D0440
// vtable constant: 0x7E192C
GG_VECTOR_CTOR_POD_BODY(VectorClass_004D0440, PodElem4, 0x7E192C)

// FUNCTION: GAMEMD 0x4E0E80
// vtable constant: 0x7E920C
GG_VECTOR_CTOR_POD_BODY(VectorClass_004E0E80, PodElem4, 0x7E920C)

// FUNCTION: GAMEMD 0x4F2C00
// vtable constant: 0x7EA624
GG_VECTOR_CTOR_POD_BODY(VectorClass_004F2C00, PodElem4, 0x7EA624)

// FUNCTION: GAMEMD 0x510500
// vtable constant: 0x7EA504
GG_VECTOR_CTOR_POD_BODY(VectorClass_00510500, PodElem4, 0x7EA504)

// FUNCTION: GAMEMD 0x510550
// vtable constant: 0x7E9E44
GG_VECTOR_CTOR_POD_BODY(VectorClass_00510550, PodElem4, 0x7E9E44)

// FUNCTION: GAMEMD 0x5105F0
// vtable constant: 0x7E5D08
GG_VECTOR_CTOR_POD_BODY(VectorClass_005105F0, PodElem4, 0x7E5D08)

// FUNCTION: GAMEMD 0x510640
// vtable constant: 0x7EA5C4
GG_VECTOR_CTOR_POD_BODY(VectorClass_00510640, PodElem4, 0x7EA5C4)

// FUNCTION: GAMEMD 0x510690
// vtable constant: 0x7EA964
GG_VECTOR_CTOR_POD_BODY(VectorClass_00510690, PodElem4, 0x7EA964)

// FUNCTION: GAMEMD 0x538B30
// vtable constant: 0x7EB80C
GG_VECTOR_CTOR_POD_BODY(VectorClass_00538B30, PodElem4, 0x7EB80C)

// FUNCTION: GAMEMD 0x54A850
// vtable constant: 0x7ECD0C
GG_VECTOR_CTOR_POD_BODY(VectorClass_0054A850, PodElem4, 0x7ECD0C)

// FUNCTION: GAMEMD 0x54EBF0
// vtable constant: 0x7ECE9C
GG_VECTOR_CTOR_POD_BODY(VectorClass_0054EBF0, PodElem4, 0x7ECE9C)

// FUNCTION: GAMEMD 0x55BB40
// vtable constant: 0x7E9F84
GG_VECTOR_CTOR_POD_BODY(VectorClass_0055BB40, PodElem4, 0x7E9F84)

// FUNCTION: GAMEMD 0x5AD6F0
// vtable constant: 0x7E5C24
GG_VECTOR_CTOR_POD_BODY(VectorClass_005AD6F0, PodElem4, 0x7E5C24)

// FUNCTION: GAMEMD 0x5AD740
// vtable constant: 0x7ED878
GG_VECTOR_CTOR_POD_BODY(VectorClass_005AD740, PodElem4, 0x7ED878)

// FUNCTION: GAMEMD 0x5AD820
// vtable constant: 0x7ED480
GG_VECTOR_CTOR_POD_BODY(VectorClass_005AD820, PodElem4, 0x7ED480)

// FUNCTION: GAMEMD 0x5ADAB0
// vtable constant: 0x7EDA4C
GG_VECTOR_CTOR_POD_BODY(VectorClass_005ADAB0, PodElem8, 0x7EDA4C)

// FUNCTION: GAMEMD 0x5C59E0
// vtable constant: 0x7EE3D0
GG_VECTOR_CTOR_POD_BODY(VectorClass_005C59E0, PodElem4, 0x7EE3D0)

// FUNCTION: GAMEMD 0x5C5A30
// vtable constant: 0x7EE390
GG_VECTOR_CTOR_POD_BODY(VectorClass_005C5A30, PodElem4, 0x7EE390)

// FUNCTION: GAMEMD 0x5D8950
// vtable constant: 0x7EA2C4
GG_VECTOR_CTOR_POD_BODY(VectorClass_005D8950, PodElem4, 0x7EA2C4)

// FUNCTION: GAMEMD 0x5D89A0
// vtable constant: 0x7EA344
GG_VECTOR_CTOR_POD_BODY(VectorClass_005D89A0, PodElem4, 0x7EA344)

// FUNCTION: GAMEMD 0x5D89F0
// vtable constant: 0x7EED40
GG_VECTOR_CTOR_POD_BODY(VectorClass_005D89F0, PodElem4, 0x7EED40)

// FUNCTION: GAMEMD 0x5EF0B0
// vtable constant: 0x7EEF50
GG_VECTOR_CTOR_POD_BODY(VectorClass_005EF0B0, PodElem4, 0x7EEF50)

// FUNCTION: GAMEMD 0x67C310
// vtable constant: 0x7F0D5C
GG_VECTOR_CTOR_POD_BODY(VectorClass_0067C310, PodElem4, 0x7F0D5C)

// FUNCTION: GAMEMD 0x67C3A0
// vtable constant: 0x7F0D7C
GG_VECTOR_CTOR_POD_BODY(VectorClass_0067C3A0, PodElem4, 0x7F0D7C)

// FUNCTION: GAMEMD 0x67C430
// vtable constant: 0x7F0D9C
GG_VECTOR_CTOR_POD_BODY(VectorClass_0067C430, PodElem4, 0x7F0D9C)

// FUNCTION: GAMEMD 0x69D770
// vtable constant: 0x7F1274
GG_VECTOR_CTOR_POD_BODY(VectorClass_0069D770, PodElem4, 0x7F1274)

// FUNCTION: GAMEMD 0x69D870
// vtable constant: 0x7E9F04
GG_VECTOR_CTOR_POD_BODY(VectorClass_0069D870, PodElem4, 0x7E9F04)

// FUNCTION: GAMEMD 0x6B1AB0
// vtable constant: 0x7F324C
GG_VECTOR_CTOR_POD_BODY(VectorClass_006B1AB0, PodElem4, 0x7F324C)

// FUNCTION: GAMEMD 0x6B8880
// vtable constant: 0x7F36D4
GG_VECTOR_CTOR_POD_BODY(VectorClass_006B8880, PodElem4, 0x7F36D4)

// FUNCTION: GAMEMD 0x6CABA0
// vtable constant: 0x7F3F8C
GG_VECTOR_CTOR_POD_BODY(VectorClass_006CABA0, PodElem4, 0x7F3F8C)

// FUNCTION: GAMEMD 0x7343E0
// vtable constant: 0x7EE0D4
GG_VECTOR_CTOR_POD_BODY(VectorClass_007343E0, PodElem4, 0x7EE0D4)

// FUNCTION: GAMEMD 0x76F1C0
// vtable constant: 0x7EEC24
GG_VECTOR_CTOR_POD_BODY(VectorClass_0076F1C0, PodElem4, 0x7EEC24)

// FUNCTION: GAMEMD 0x76F210
// vtable constant: 0x7EEAF4
GG_VECTOR_CTOR_POD_BODY(VectorClass_0076F210, PodElem4, 0x7EEAF4)

// FUNCTION: GAMEMD 0x7AECD0
// vtable constant: 0x7F78A4
GG_VECTOR_CTOR_POD_BODY(VectorClass_007AECD0, PodElem4, 0x7F78A4)
