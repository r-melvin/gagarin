// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu291_methods.h"

// FUNCTION: GAMEMD 0x7B2720
// Stores to a global.
void FUN_007B2720(int a1)
{
    DAT_00B780A0 = a1;
}
