// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu152_b_methods.h"

// FUNCTION: GAMEMD 0x5CC6A0
// Stores several members; pops its stack arguments.
void Obj_005CC6A0::FUN_005CC6A0(int a1)
{
    unknown_40 = 0;
    unknown_28 = a1;
}
