// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "guarded_forward_methods.h"

// FUNCTION: GAMEMD 0x437FC0
void Obj_00437FC0::FUN_00437FC0()
{
    if (Held) {
        IFACE_CALL(Held, 0x8);
    }
}

