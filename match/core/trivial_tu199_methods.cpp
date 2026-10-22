// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu199_methods.h"

// FUNCTION: GAMEMD 0x679EC0
// Tail-calls a method on a global object.
void FUN_00679EC0(int a1, int a2)
{
    FUN_00476D80(DAT_00887180, a2);
}

// FUNCTION: GAMEMD 0x679ED0
// Tail-calls a method on a global object.
void FUN_00679ED0(int a1, int a2)
{
    FUN_00476D80(DAT_00887128, a2);
}
