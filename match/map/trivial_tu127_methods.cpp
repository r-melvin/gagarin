// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu127_methods.h"

// FUNCTION: GAMEMD 0x561900
// Tail-forwards to another function.
void Obj_00561900::FUN_00561900()
{
    FUN_00561910();
}

// FUNCTION: GAMEMD 0x5638C0
// Tail-forwards to another function.
void Obj_005638C0::FUN_005638C0()
{
    FUN_005638D0();
}

// FUNCTION: GAMEMD 0x565080
// Tail-calls a method on a global object.
void FUN_00565080(int a1, int a2)
{
    FUN_0047BB60(DAT_00ABDC50, a2);
}

// FUNCTION: GAMEMD 0x56C200
// Returns a constant.
int __cdecl FUN_0056C200()
{
    return 1;
}

// FUNCTION: GAMEMD 0x56C500
// Empty function.
void __cdecl FUN_0056C500()
{
}
