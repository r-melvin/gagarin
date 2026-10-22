// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu256_methods.h"

// FUNCTION: GAMEMD 0x730AD0
// Returns a constant.
int __cdecl FUN_00730AD0()
{
    return 0x4046;
}

// FUNCTION: GAMEMD 0x730AE0
// Returns a constant.
int __cdecl FUN_00730AE0()
{
    return 0xF0;
}

// FUNCTION: GAMEMD 0x731A30
// Branching.
void FUN_00731A30(int a1, int a2)
{
    if (DAT_00A8B538 == 0)
    {
        FUN_004AC960(DAT_0087F7E8, a2, -1);
    }
}

// FUNCTION: GAMEMD 0x731A90
// Tail-forwards to another function.
void __cdecl FUN_00731A90()
{
    FUN_00637AA0();
}

// FUNCTION: GAMEMD 0x731BE0
// Stores to a global.
void __cdecl FUN_00731BE0()
{
    DAT_00B0FE58 = 0;
}

// FUNCTION: GAMEMD 0x731CF0
// Stores to a global.
void __cdecl FUN_00731CF0()
{
    DAT_00B0FE58 = 0;
}

// FUNCTION: GAMEMD 0x732CA0
// Branching.
void __cdecl FUN_00732CA0()
{
    if (DAT_00B0FE65 == 0)
    {
        unsigned char t1 = DAT_00B0FE65;
        DAT_00B0FE65 = 1;
        int c0 = timeGetTime();
        DAT_00B0FE68 = c0;
    }
}
