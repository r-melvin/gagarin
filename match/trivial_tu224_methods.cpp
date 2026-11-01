// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu224_methods.h"

// FUNCTION: GAMEMD 0x6C9930
// Branching.
void Obj_006C9930::FUN_006C9930()
{
    if (unknown_14 != 0)
    {
        FUN_007C8B3D(unknown_14);
    }
}

// FUNCTION: GAMEMD 0x6C9AC0
// Stores several members.
Obj_006C9AC0* Obj_006C9AC0::FUN_006C9AC0()
{
    unknown_00 = 0;
    unknown_04 = 0;
    unknown_08 = 0;
    unknown_0C = 0;
    unknown_10 = 0;
    unknown_14 = 0;
    unknown_18 = 0;
    unknown_1C = 0;
    unknown_20 = 0;
    return this;
}

// FUNCTION: GAMEMD 0x6C9D30
// Stores its argument in a member; pops its stack arguments.
void Obj_006C9D30::FUN_006C9D30(int a1)
{
    unknown_0C = a1;
}

// FUNCTION: GAMEMD 0x6CA7B0
// Calls other functions.
void FUN_006CA7B0(Obj_006CA7B0* a1, int a2)
{
    FUN_006C9960(a2, a2, a1);
}
