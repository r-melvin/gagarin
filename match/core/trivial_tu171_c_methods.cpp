// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu171_c_methods.h"

// FUNCTION: GAMEMD 0x60A5A0
// Calls other functions.
void Obj_0060A5A0::FUN_0060A5A0()
{
    EnumChildWindows(this, 0x60A330, 0);
}
