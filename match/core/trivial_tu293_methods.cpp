// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu293_methods.h"

// FUNCTION: GAMEMD 0x7B7D80
// Calls other functions.
void Obj_007B7D80::FUN_007B7D80()
{
    FUN_007CB9B8(unknown_00, 0, 0xA);
}

// FUNCTION: GAMEMD 0x7B84D0
// Branching.
void FUN_007B84D0(int a1, int a2)
{
    if (DAT_00B7816C == 0)
    {
        if (DAT_00B78164 != 0)
        {
            FUN_007BA090(DAT_00B78164, a2);
        }
    }
}
