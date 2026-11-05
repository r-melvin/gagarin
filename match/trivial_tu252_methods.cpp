// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu252_methods.h"
#include "_layout/tube_class.h"

// FUNCTION: GAMEMD 0x7286B0
// Returns a constant. Vtable slot 12 of TubeClass (RTTI).
int TubeClass::vf_12()
{
    return 0x1C4;
}

// FUNCTION: GAMEMD 0x7286C0
// Returns a constant. Vtable slot 11 of TubeClass (RTTI).
int TubeClass::vf_11()
{
    return 0x35;
}
