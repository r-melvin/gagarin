// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu286_methods.h"

// FUNCTION: GAMEMD 0x7786E0
// Calls other functions.
void FUN_007786E0(int a1, int a2)
{
    FUN_007B4630(DAT_00B73590, a2, DAT_00849F58);
    FUN_007C978A(0x778700);
}

// FUNCTION: GAMEMD 0x778700
// Tail-calls a method on a global object.
void FUN_00778700(int a1, int a2)
{
    FUN_007B46F0(DAT_00B73590, a2);
}

// FUNCTION: GAMEMD 0x77A760
// Branching.
unsigned char Obj_0077A760::FUN_0077A760(unsigned char a1)
{
    if (a1 != unknown_38)
    {
        unsigned char t1 = unknown_38;
        unknown_38 = a1;
        unknown_08 = 1;
    }
    return a1;
}

// FUNCTION: GAMEMD 0x77A780
// Branching.
int Obj_0077A780::FUN_0077A780(int a1)
{
    if (a1 != unknown_1C)
    {
        int t1 = unknown_1C;
        unknown_1C = a1;
        unknown_08 = 1;
    }
    return a1;
}

// FUNCTION: GAMEMD 0x77A7A0
// Branching.
int Obj_0077A7A0::FUN_0077A7A0(int a1)
{
    if (a1 != unknown_20)
    {
        int t1 = unknown_20;
        unknown_20 = a1;
        unknown_08 = 1;
    }
    return a1;
}

// FUNCTION: GAMEMD 0x77A870
// Branching.
void Obj_0077A870::FUN_0077A870(int a1)
{
    if (unknown_2C != -1)
    {
        unknown_08 = 1;
        unknown_2C += a1;
    }
}

// FUNCTION: GAMEMD 0x77A890
// Branching.
void Obj_0077A890::FUN_0077A890(int a1)
{
    if (unknown_30 != -1)
    {
        unknown_08 = 1;
        unknown_30 += a1;
    }
}

// FUNCTION: GAMEMD 0x77A8B0
// Branching.
void Obj_0077A8B0::FUN_0077A8B0(int a1)
{
    if (unknown_34 != -1)
    {
        unknown_08 = 1;
        unknown_34 += a1;
    }
}
