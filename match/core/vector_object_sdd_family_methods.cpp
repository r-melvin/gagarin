// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001 at each address
//   below. Each of these eight functions is the scalar-deleting destructor of
//   one vector instantiation whose elements are objects: reseat the vtable,
//   release the element array through the array cookie if this vector owns
//   one, clear the bookkeeping, and free the object itself when the caller
//   asked for it. Per-instance variation is the vtable constant at +0 and the
//   two CALL displacements to the CRT free; everything else is identical, so
//   the body is written once as a macro. Ordered ascending by retail address.
//
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
//   This TU departs from the locked flag set: it must be compiled WITHOUT
//   /GX. With /GX on, cl declines to inline the vector destructor iterator and
//   emits an out-of-line call instead; with it off it inlines retail's exact
//   five instructions. That is worth 25.7% versus 100% across these eight
//   functions, and no source-level spelling reaches it with /GX on (a throw()
//   specification, an explicit inline, three element sizes, /Ob2 and /Oi were
//   all measured). scripts/vc6/vc6cl.sh reads the marker above, so the inner
//   loop and the regression gate both compile this file the same way.

#include "vector_object_sdd_family_methods.h"

// FUNCTION: GAMEMD 0x004E0D80
GG_VECTOR_OBJECT_SDD_BODY(004E0D80, 007E9264)

// FUNCTION: GAMEMD 0x004E0E20
GG_VECTOR_OBJECT_SDD_BODY(004E0E20, 007E9264)

// FUNCTION: GAMEMD 0x00510400
GG_VECTOR_OBJECT_SDD_BODY(00510400, 007EAAA4)

// FUNCTION: GAMEMD 0x005104A0
GG_VECTOR_OBJECT_SDD_BODY(005104A0, 007EAAA4)

// FUNCTION: GAMEMD 0x006F2680
GG_VECTOR_OBJECT_SDD_BODY(006F2680, 007F4840)

// FUNCTION: GAMEMD 0x006F2720
GG_VECTOR_OBJECT_SDD_BODY(006F2720, 007F4840)

// FUNCTION: GAMEMD 0x00763FF0
GG_VECTOR_OBJECT_SDD_BODY(00763FF0, 007F6EF4)

// FUNCTION: GAMEMD 0x00764050
GG_VECTOR_OBJECT_SDD_BODY(00764050, 007F6EF4)
