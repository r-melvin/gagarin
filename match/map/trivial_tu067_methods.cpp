// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu067_methods.h"

// FUNCTION: GAMEMD 0x4A8D40
// Empty function.
void __cdecl FUN_004A8D40()
{
}

// FUNCTION: GAMEMD 0x4A8EA0
// Empty function.
void __cdecl FUN_004A8EA0()
{
}

// FUNCTION: GAMEMD 0x4AEB30
// Stores several members; pops its stack arguments.
void Obj_004AEB30::FUN_004AEB30(int a1)
{
    unknown_11A0 = a1;
    unknown_119C = a1 != 0;
}

// FUNCTION: GAMEMD 0x4AEBA0
// Returns zero. Vtable slot 17 of GadgetClass (RTTI) and 5 derived vtable(s).
int Obj_004AEBA0::FUN_004AEBA0() const
{
    return 0;
}

// FUNCTION: GAMEMD 0x4AEBD0
// Empty function that pops its stack arguments. Vtable slot 16 of GScreenClass (RTTI) and 2 derived vtable(s).
void GScreenClass::vf_16(bool forced)
{
}

// FUNCTION: GAMEMD 0x4AEBE0
// Returns a constant boolean. Vtable slot 26 of MapClass (RTTI) and 5 derived vtable(s).
bool MapClass::vf_26()
{
    return false;
}
