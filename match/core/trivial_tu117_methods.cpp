// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu117_methods.h"

// FUNCTION: GAMEMD 0x554350
// Branching.
void Obj_00554350::FUN_00554350(Arg1_00554350* a1)
{
    if (unknown_60 != 0)
    {
        a1->vf_1(unknown_60, 0, 1);
    }
}
