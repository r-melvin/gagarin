// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu190_methods.h"
#include "_layout/rad_site_class.h"

// FUNCTION: GAMEMD 0x65B3A0
// Returns a constant. Vtable slot 12 of RadSiteClass (RTTI).
int RadSiteClass::vf_12()
{
    return 0x74;
}

// FUNCTION: GAMEMD 0x65B3C0
// Returns a constant. Vtable slot 11 of RadSiteClass (RTTI).
int RadSiteClass::vf_11()
{
    return 0x45;
}

// FUNCTION: GAMEMD 0x65B4B0
// Member getter (dword).
int Obj_0065B4B0::FUN_0065B4B0() const
{
    return unknown_44;
}
