// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu093_b_methods.h"

// FUNCTION: GAMEMD 0x4F3A90
// Branching.
void Obj_004F3A90::FUN_004F3A90(unsigned char a1)
{
    if (a1 != unknown_08)
    {
        unknown_08 = a1;
        vf_4(a1);
    }
}
