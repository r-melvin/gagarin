// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address. The allocate-and-construct helper
// is written out longhand per the family rule.

#include "small_misc15_methods.h"

// FUNCTION: GAMEMD 0x41CB20
char* Obj_0041CB20::FUN_0041CB20(int arg)
{
    void* p = FUN_007C8E17(0x6D8);

    if (p) {
        return ((Made_0041CB20*)p)->FUN_00413D20(this, arg);
    }

    return 0;
}

