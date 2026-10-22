// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu280_methods.h"

// FUNCTION: GAMEMD 0x76FF20
// Stores its argument in a member; pops its stack arguments.
void Obj_0076FF20::FUN_0076FF20(int a1)
{
    unknown_2C = a1;
}

// FUNCTION: GAMEMD 0x76FF30
// Stores its argument in a member.
int Obj_0076FF30::FUN_0076FF30()
{
    int t1 = unknown_2C;
    unknown_2C = 0;
    return t1;
}
