// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu156_methods.h"

// FUNCTION: GAMEMD 0x5D7580
// Stores its argument in a member.
Obj_005D7580* Obj_005D7580::FUN_005D7580()
{
    unknown_00 = 0x7EEE74;
    return this;
}

// FUNCTION: GAMEMD 0x5D7CD0
// Stores its argument in a member.
void Obj_005D7CD0::FUN_005D7CD0()
{
    unknown_00 = 0x7EEE74;
}
