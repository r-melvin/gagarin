// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu111_methods.h"

// FUNCTION: GAMEMD 0x54AE50
// Member getter (byte); pops its stack arguments. Vtable slot 4 of JumpjetLocomotionClass (RTTI).
unsigned char Obj_0054AE50::FUN_0054AE50(Arg1_0054AE50* a1) const
{
    return a1->unknown_48;
}

// FUNCTION: GAMEMD 0x54D0C0
// Empty function.
void __cdecl FUN_0054D0C0()
{
}

// FUNCTION: GAMEMD 0x54D0D0
// Branching. Vtable slot 32 of JumpjetLocomotionClass (RTTI).
bool Obj_0054D0D0::FUN_0054D0D0(Arg1_0054D0D0* a1)
{
    if (a1->unknown_4C == 0 || a1->unknown_4C == 2)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x54DF70
// Returns a comparison result; pops its stack arguments. Vtable slot 7 of JumpjetLocomotionClass (RTTI).
bool Obj_0054DF70::FUN_0054DF70(Arg1_0054DF70* a1) const
{
    return a1->unknown_7C != 0;
}

// FUNCTION: GAMEMD 0x54DF90
// Returns a constant. Vtable slot 9 of JumpjetLocomotionClass (RTTI).
int Obj_0054DF90::FUN_0054DF90() const
{
    return 0x98;
}
