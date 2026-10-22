// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu046_methods.h"

// FUNCTION: GAMEMD 0x473CD0
// Branching. Vtable slot 6 of CCFileClass (RTTI).
unsigned char Obj_00473CD0::FUN_00473CD0()
{
    if (unknown_58 != 0)
    {
        return 1;
    }
    return FUN_00431F30();
}
