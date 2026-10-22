// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu171_d_methods.h"

// FUNCTION: GAMEMD 0x60AF40
// Calls other functions.
void Obj_0060AF40::FUN_0060AF40()
{
    EnumChildWindows(this, 0x60AAB0, 0);
}
