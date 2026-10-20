// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001. These nine
//   functions are one default constructor for a leaf class over a growable
//   vector of pointers, instantiated nine times. Every byte outside the single
//   `MOV dword ptr [EAX],imm32` vtable constant is identical across all nine,
//   so the body is written once as a macro and expanded per instantiation.
//   Ordered ascending by retail address.
//
// What it does: zero Items and Capacity, mark the vector initialised and not
// yet owning its storage, set the growth step to 10, clear the live count, and
// seat the leaf vtable.

#include "dynamic_vector_default_ctor_family_methods.h"

// FUNCTION: GAMEMD 0x00512960
GG_DYNVEC_DEFAULT_CTOR_BODY(007EABC8)

// FUNCTION: GAMEMD 0x005AC400
GG_DYNVEC_DEFAULT_CTOR_BODY(007ED90C)

// FUNCTION: GAMEMD 0x0067A390
GG_DYNVEC_DEFAULT_CTOR_BODY(007F0D3C)

// FUNCTION: GAMEMD 0x0067A470
GG_DYNVEC_DEFAULT_CTOR_BODY(007EB6D4)

// FUNCTION: GAMEMD 0x0067A4F0
GG_DYNVEC_DEFAULT_CTOR_BODY(007E4DD8)

// FUNCTION: GAMEMD 0x0067A600
GG_DYNVEC_DEFAULT_CTOR_BODY(007F0D1C)

// FUNCTION: GAMEMD 0x0067A820
GG_DYNVEC_DEFAULT_CTOR_BODY(007EAC08)

// FUNCTION: GAMEMD 0x0067A8B0
GG_DYNVEC_DEFAULT_CTOR_BODY(007F0CFC)

// FUNCTION: GAMEMD 0x00717AF0
GG_DYNVEC_DEFAULT_CTOR_BODY(007F4F9C)
