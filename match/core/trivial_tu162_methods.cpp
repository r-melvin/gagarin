// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu162_methods.h"

// FUNCTION: GAMEMD 0x5EF270
// Returns a constant.
int __cdecl FUN_005EF270()
{
    return 0x18;
}

// FUNCTION: GAMEMD 0x5EF280
// Tail-forwards to another function. Vtable slot 1 of NullModemConnClass (RTTI).
void Obj_005EF280::FUN_005EF280()
{
    FUN_0048BF10();
}
