// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Four Clear() members of a growable vector over a polymorphic element type:
// zero the live count, release the element block through the element's own
// vector-deleting destructor when this vector owns it, and reset the
// bookkeeping. All four are byte-identical, so one body serves the family.
// Ordered ascending by retail address.

#include "polymorphic_vector_clear_family_methods.h"

// FUNCTION: GAMEMD 0x00765680
GG_PVEC_CLEAR_BODY(00765680)

// FUNCTION: GAMEMD 0x00766800
GG_PVEC_CLEAR_BODY(00766800)

// FUNCTION: GAMEMD 0x00769C50
GG_PVEC_CLEAR_BODY(00769C50)

// FUNCTION: GAMEMD 0x0076B710
GG_PVEC_CLEAR_BODY(0076B710)
