// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu188_methods.h"

// FUNCTION: GAMEMD 0x659490
// Stores its argument in a member; pops its stack arguments.
void Obj_00659490::FUN_00659490(int a1)
{
    unknown_0C = a1;
}

// FUNCTION: GAMEMD 0x6594E0
// Stores its argument in a member; pops its stack arguments.
void Obj_006594E0::FUN_006594E0(int a1)
{
    unknown_3C = a1;
}

// FUNCTION: GAMEMD 0x6594F0
// Stores several members; pops its stack arguments.
void Obj_006594F0::FUN_006594F0(int a1, int a2)
{
    unknown_40 = a1;
    unknown_44 = a2;
}

// FUNCTION: GAMEMD 0x659510
// Stores several members; pops its stack arguments.
void Obj_00659510::FUN_00659510(int a1, int a2)
{
    unknown_48 = a1;
    unknown_4C = a2;
}

// FUNCTION: GAMEMD 0x659530
// Stores its argument in a member; pops its stack arguments.
void Obj_00659530::FUN_00659530(int a1)
{
    unknown_50 = a1;
}

// FUNCTION: GAMEMD 0x659540
// Stores its argument in a member; pops its stack arguments.
void Obj_00659540::FUN_00659540(int a1)
{
    unknown_54 = a1;
}

// FUNCTION: GAMEMD 0x659560
// Stores its argument in a member.
void Obj_00659560::FUN_00659560()
{
    unknown_09 = 0;
}

// FUNCTION: GAMEMD 0x659570
// Member getter (byte).
unsigned char Obj_00659570::FUN_00659570() const
{
    return unknown_09;
}
