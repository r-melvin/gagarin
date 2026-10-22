// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu209_methods.h"

// FUNCTION: GAMEMD 0x6A3DA0
// Empty function.
void __cdecl FUN_006A3DA0()
{
}

// FUNCTION: GAMEMD 0x6A3EA0
// Returns zero; pops its stack arguments. Vtable slot 14 of ShipLocomotionClass (RTTI).
int Obj_006A3EA0::FUN_006A3EA0(int a1) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x6A4250
// Member getter (dword); pops its stack arguments. Vtable slot 49 of ShipLocomotionClass (RTTI).
int Obj_006A4250::FUN_006A4250(Arg1_006A4250* a1) const
{
    return a1->unknown_48;
}

// FUNCTION: GAMEMD 0x6A4280
// Returns a comparison result; pops its stack arguments. Vtable slot 7 of ShipLocomotionClass (RTTI).
bool Obj_006A4280::FUN_006A4280(Arg1_006A4280* a1) const
{
    return a1->unknown_50 != 0;
}

// FUNCTION: GAMEMD 0x6A42A0
// Returns a constant. Vtable slot 9 of ShipLocomotionClass (RTTI).
int Obj_006A42A0::FUN_006A42A0() const
{
    return 0x70;
}
