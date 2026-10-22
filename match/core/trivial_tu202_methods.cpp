// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu202_methods.h"

// FUNCTION: GAMEMD 0x690150
// Empty function.
void __cdecl FUN_00690150()
{
}

// FUNCTION: GAMEMD 0x690F20
// Branching.
void Obj_00690F20::FUN_00690F20()
{
    if (unknown_00 != 0)
    {
        FUN_007C93E8(unknown_00);
    }
}
