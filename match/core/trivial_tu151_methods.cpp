// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu151_methods.h"

// FUNCTION: GAMEMD 0x5CB3E0
// Stores, then tail-calls.
void FUN_005CB3E0(Obj_005CB3E0* a1, int a2)
{
    a1->unknown_00 = 0x7EE814;
    FUN_005D5D20(a1, a2);
}

// FUNCTION: GAMEMD 0x5CB3F0
// Stores to a global. Vtable slot 4 of UnholyAlliance (RTTI).
bool Obj_005CB3F0::FUN_005CB3F0()
{
    DAT_00A8B258 = true;
    return true;
}

// FUNCTION: GAMEMD 0x5CB430
// Stores to a global. Vtable slot 6 of UnholyAlliance (RTTI).
bool Obj_005CB430::FUN_005CB430()
{
    DAT_00A8B258 = true;
    return true;
}
