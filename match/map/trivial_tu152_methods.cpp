// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu152_methods.h"

// FUNCTION: GAMEMD 0x5CC690
// Stores its argument in a member.
void Obj_005CC690::FUN_005CC690()
{
    unknown_40 = 0;
}

// FUNCTION: GAMEMD 0x5CC740
// Branching. Vtable slot 7 of MSOverlayAnim (RTTI).
int Obj_005CC740::FUN_005CC740()
{
    return unknown_0C == 0 || unknown_40 >= 4;
}

// FUNCTION: GAMEMD 0x5CD310
// Empty function.
void __cdecl FUN_005CD310()
{
}
