// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu099_b_methods.h"

// FUNCTION: GAMEMD 0x51F640
// Branching. Vtable slot 136 of InfantryClass (RTTI).
void FUN_0051F640(Obj_0051F640* a1, int a2)
{
    int c0 = FUN_00521320(a1, a2);
    if (c0 == -1)
    {
        a1->FUN_004D6AA0();
    }
}
