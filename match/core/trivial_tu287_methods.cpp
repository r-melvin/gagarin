// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu287_methods.h"

// FUNCTION: GAMEMD 0x77B280
// Branching.
int __cdecl FUN_0077B280()
{
    if (DAT_00A8B244 != 0)
    {
        if (DAT_00A8B244 != 6)
        {
            return (DAT_00A8B244 == 3) + 1;
        }
        return 0;
    }
    return 0;
}
