// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu003_methods.h"

// FUNCTION: GAMEMD 0x40AFC0
// Tail-calls a method on a global object.
void FUN_0040AFC0(int a1, int a2)
{
    FUN_0042A900(DAT_0087E8B8, a2);
}
