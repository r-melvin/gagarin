// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu127_b_methods.h"

// FUNCTION: GAMEMD 0x567370
// Calls other functions.
void Obj_00567370::FUN_00567370(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    FUN_005673A0(a3, a4, a5, a6, a7, a8, a9, 1);
}
