// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu247_methods.h"
#include "_layout/tiberium_class.h"

// FUNCTION: GAMEMD 0x7236E0
// Returns a constant. Vtable slot 12 of TiberiumClass (RTTI).
int TiberiumClass::vf_12()
{
    return 0x128;
}

// FUNCTION: GAMEMD 0x7236F0
// Returns a constant. Vtable slot 11 of TiberiumClass (RTTI).
int TiberiumClass::vf_11()
{
    return 0x2E;
}

// FUNCTION: GAMEMD 0x723700
// Member getter (dword). Vtable slot 16 of TiberiumClass (RTTI).
int TiberiumClass::vf_16()
{
    return unknown_98;
}
