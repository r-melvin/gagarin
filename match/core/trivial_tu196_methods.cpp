// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu196_methods.h"

// FUNCTION: GAMEMD 0x65FA60
// Empty function.
void __cdecl FUN_0065FA60()
{
}

// FUNCTION: GAMEMD 0x65FB60
// Calls other functions.
void FUN_0065FB60(Obj_0065FB60* a1, int a2)
{
    FUN_006562D0(DAT_0087F7E8, a2, a1);
}
