// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu185_methods.h"

// FUNCTION: GAMEMD 0x645C50
// Stores several members; pops its stack arguments.
void Obj_00645C50::FUN_00645C50(int a1, int a2, int a3, int a4)
{
    unknown_00 = a1;
    unknown_04 = a2;
    unknown_08 = a3;
    unknown_0C = a4;
}
