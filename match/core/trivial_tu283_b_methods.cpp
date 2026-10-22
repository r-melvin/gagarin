// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu283_b_methods.h"

// FUNCTION: GAMEMD 0x774070
// Branching.
int __cdecl FUN_00774070()
{
    return DAT_00B72D0C != 0 && DAT_00B72D0C->unknown_08 != 0 && DAT_00B72D0C->unknown_40C != 0;
}
