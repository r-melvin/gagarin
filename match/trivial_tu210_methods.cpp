// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu210_methods.h"

// FUNCTION: GAMEMD 0x6A4910
// Returns a constant. Vtable slot 12 of SideClass (RTTI).
int Obj_006A4910::FUN_006A4910() const
{
    return 0xB4;
}

// FUNCTION: GAMEMD 0x6A4920
// Returns a constant. Vtable slot 11 of SideClass (RTTI).
int Obj_006A4920::FUN_006A4920() const
{
    return 0x1C;
}
