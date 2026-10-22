// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu057_methods.h"

// FUNCTION: GAMEMD 0x49B420
// Tail-calls a method on a global object.
void FUN_0049B420(int a1, int a2)
{
    FUN_0049E510(DAT_0089F518, a2);
}
