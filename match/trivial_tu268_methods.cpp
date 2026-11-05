// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu268_methods.h"
#include "_layout/warhead_type_class.h"

// FUNCTION: GAMEMD 0x75E4F0
// Returns a constant. Vtable slot 12 of WarheadTypeClass (RTTI).
int WarheadTypeClass::vf_12()
{
    return 0x1D0;
}

// FUNCTION: GAMEMD 0x75E500
// Returns a constant. Vtable slot 11 of WarheadTypeClass (RTTI).
int WarheadTypeClass::vf_11()
{
    return 0x32;
}
