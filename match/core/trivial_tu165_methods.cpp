// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu165_methods.h"

// FUNCTION: GAMEMD 0x5F3D90
// Branching.
void Obj_005F3D90::FUN_005F3D90()
{
    if (unknown_A8 != 0)
    {
        unknown_A8->FUN_00556B30();
        unknown_A8 = 0;
    }
}

// FUNCTION: GAMEMD 0x5F5C10
// Empty function.
void __cdecl FUN_005F5C10()
{
}

// FUNCTION: GAMEMD 0x5F6CB0
// Branching.
void FUN_005F6CB0(Obj_005F6CB0* a1, int a2, int a3)
{
    a1->unknown_64 = a3;
    if (a3 == -1)
    {
        FUN_00405FD0(&a1->unknown_50, a2);
    }
}
