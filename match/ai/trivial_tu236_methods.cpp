// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu236_methods.h"

// FUNCTION: GAMEMD 0x6F20A0
// Returns a constant. Vtable slot 11 of TeamTypeClass (RTTI).
int Obj_006F20A0::FUN_006F20A0() const
{
    return 0x23;
}

// FUNCTION: GAMEMD 0x6F20B0
// Returns a constant. Vtable slot 12 of TeamTypeClass (RTTI).
int Obj_006F20B0::FUN_006F20B0() const
{
    return 0xF8;
}

// FUNCTION: GAMEMD 0x6F20C0
// Member getter (dword). Vtable slot 16 of TeamTypeClass (RTTI).
int Obj_006F20C0::FUN_006F20C0() const
{
    return unknown_98;
}

// FUNCTION: GAMEMD 0x6F25D0
// Empty function.
void __cdecl FUN_006F25D0()
{
}
