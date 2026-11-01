// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu253_methods.h"

// FUNCTION: GAMEMD 0x728A50
// Returns a comparison result; pops its stack arguments. Vtable slot 4 of TunnelLocomotionClass (RTTI).
bool Obj_00728A50::FUN_00728A50(Arg1_00728A50* a1) const
{
    return (a1->unknown_14 != 0) ? true : false;
}

// FUNCTION: GAMEMD 0x7291D0
// Branching. Vtable slot 13 of TunnelLocomotionClass (RTTI).
int Obj_007291D0::FUN_007291D0(Arg1_007291D0* a1, unsigned char a2)
{
    if (a1->unknown_14 == 4)
    {
        return (a2 != 0) + 4;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x72A1E0
// Branching. Vtable slot 38 of TunnelLocomotionClass (RTTI).
int Obj_0072A1E0::FUN_0072A1E0(Arg1_0072A1E0* a1)
{
    return a1->unknown_14 == 5 || a1->unknown_14 == 6;
}

// FUNCTION: GAMEMD 0x72A200
// Returns a constant. Vtable slot 9 of TunnelLocomotionClass (RTTI).
int Obj_0072A200::FUN_0072A200() const
{
    return 0x3C;
}
