// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu024_methods.h"

// FUNCTION: GAMEMD 0x423920
// Empty function.
void __cdecl FUN_00423920()
{
}

// FUNCTION: GAMEMD 0x426740
// Returns a constant.
int __cdecl FUN_00426740()
{
    return 0xB00;
}

// FUNCTION: GAMEMD 0x427290
// Returns the address of a member. Vtable slot 4 of AnimFile (RTTI).
int* Obj_00427290::FUN_00427290()
{
    return &unknown_50C;
}
