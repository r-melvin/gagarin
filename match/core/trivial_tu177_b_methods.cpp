// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu177_b_methods.h"

// FUNCTION: GAMEMD 0x631E30
// Calls other functions.
Obj_00631E30* FUN_00631E30(Obj_00631E30* a1, int a2, int a3)
{
    a1->unknown_00 = 0x7EFDA4;
    FUN_00631D40(a1, a2, a3);
    return a1;
}
