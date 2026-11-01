// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu064_methods.h"

// FUNCTION: GAMEMD 0x4A3630
// Stores its argument in a member.
Obj_004A3630* Obj_004A3630::FUN_004A3630()
{
    unknown_18000 = 0;
    return this;
}

// FUNCTION: GAMEMD 0x4A3640
// Stores its argument in a member.
void Obj_004A3640::FUN_004A3640()
{
    unknown_18000 = 0;
}

// FUNCTION: GAMEMD 0x4A3650
// Empty function.
void __cdecl FUN_004A3650()
{
}

// FUNCTION: GAMEMD 0x4A3B30
// Returns zero.
int __cdecl FUN_004A3B30()
{
    return 0;
}

// FUNCTION: GAMEMD 0x4A3C00
// Stores its argument in a member.
void Obj_004A3C00::FUN_004A3C00()
{
    unknown_00 = 0;
}
