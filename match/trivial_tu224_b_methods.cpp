// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu224_b_methods.h"

// FUNCTION: GAMEMD 0x6C9900
// Stores several members.
Obj_006C9900* Obj_006C9900::FUN_006C9900()
{
    unknown_00 = 0;
    unknown_04 = 0x4B0;
    unknown_08 = 0xFFFFFF;
    unknown_0C = 0xF;
    unknown_10 = 2;
    unknown_14 = 0;
    return this;
}
