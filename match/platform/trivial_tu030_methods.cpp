// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu030_methods.h"

// FUNCTION: GAMEMD 0x431F30
// Branching. Vtable slot 6 of BufferIOFileClass (RTTI) and 1 derived vtable(s).
unsigned char Obj_00431F30::FUN_00431F30()
{
    if (unknown_25 != 0)
    {
        if (unknown_29 != 0)
        {
            return 1;
        }
        return unknown_14 != -1;
    }
    return unknown_14 != -1;
}
