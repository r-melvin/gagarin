// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu285_methods.h"

// FUNCTION: GAMEMD 0x777AB0
// Empty function.
void __cdecl FUN_00777AB0()
{
}

// FUNCTION: GAMEMD 0x778130
// Branching.
void __cdecl FUN_00778130()
{
    if (DAT_00B7355C != 0)
    {
        FUN_007C8A3A(DAT_00B7355C, 0);
    }
}

// FUNCTION: GAMEMD 0x778150
// Branching.
void __cdecl FUN_00778150()
{
    if (DAT_00B7355C != 0)
    {
        FUN_007C8A3A(DAT_00B7355C, 1);
    }
}
