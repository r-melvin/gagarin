// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu263_methods.h"

// FUNCTION: GAMEMD 0x7518C0
// Stores to a global.
void FUN_007518C0(int a1)
{
    DAT_008464AC = a1;
}
