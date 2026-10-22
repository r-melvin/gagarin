// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu181_methods.h"

// FUNCTION: GAMEMD 0x63F7C0
// Calls other functions. Vtable slot 53 of PowerClass (RTTI).
int FUN_0063F7C0(Obj_0063F7C0* a1, int a2)
{
    FUN_00652E90(a1, a2);
    int c1 = FUN_004A38D0(DAT_00836D9C, DAT_00AC4E78);
    DAT_00AC4E74 = c1;
    return c1;
}
