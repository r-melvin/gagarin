// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu043_methods.h"

// FUNCTION: GAMEMD 0x46D350
// Stores its argument in a member.
void Obj_0046D350::FUN_0046D350()
{
    unknown_00 = 0x7E4AAC;
}

// FUNCTION: GAMEMD 0x46D480
// Stores its argument in a member.
void FUN_0046D480(Obj_0046D480* a1, int a2)
{
    a1->unknown_89E000 = a2;
}

// FUNCTION: GAMEMD 0x46D490
// Member getter (byte).
unsigned char Obj_0046D490::FUN_0046D490() const
{
    return unknown_89E000;
}

// FUNCTION: GAMEMD 0x470C30
// Stores its argument in a member.
void Obj_00470C30::FUN_00470C30()
{
    unknown_00 = 0x7E4AB8;
}

// FUNCTION: GAMEMD 0x471400
// Branching.
void __cdecl FUN_00471400()
{
    if (DAT_0089E020 > 1)
    {
        FUN_007C8B48(DAT_0089DFE0, DAT_0089E020, 4, 0x46DC90);
    }
}
