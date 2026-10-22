// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu177_methods.h"

// FUNCTION: GAMEMD 0x631E10
// Calls other functions.
Obj_00631E10* FUN_00631E10(Obj_00631E10* a1, int a2)
{
    a1->unknown_00 = 0x7EFDA4;
    FUN_00631D40(a1, a2, 0);
    return a1;
}

// FUNCTION: GAMEMD 0x631F10
// Stores several members; pops its stack arguments.
void Obj_00631F10::FUN_00631F10(int a1, int a2)
{
    unknown_30 = a1;
    unknown_34 = a2;
}

// FUNCTION: GAMEMD 0x631F30
// Stores its argument in a member.
void Obj_00631F30::FUN_00631F30()
{
    unknown_00 = 0x7EFDA4;
}
