// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu157_methods.h"

// FUNCTION: GAMEMD 0x5D8C90
// Branching. Vtable slot 1 of MultiplayerTeam (RTTI) and 1 derived vtable(s).
bool Obj_005D8C90::FUN_005D8C90(int a1)
{
    if (a1 < 0 || a1 >= DAT_00A8DA84)
    {
        return false;
    }
    return true;
}
