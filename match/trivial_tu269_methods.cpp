// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu269_methods.h"

// FUNCTION: GAMEMD 0x7610D0
// Branching.
void Obj_007610D0::FUN_007610D0()
{
    unknown_1D0 += -6;
    if (unknown_1D0 < 0x20)
    {
        vf_62();
    }
}

// FUNCTION: GAMEMD 0x762060
// Empty function.
void __cdecl FUN_00762060()
{
}

// FUNCTION: GAMEMD 0x762AE0
// Empty function.
void __cdecl FUN_00762AE0()
{
}

