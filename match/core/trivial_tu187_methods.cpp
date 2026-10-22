// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu187_methods.h"

// FUNCTION: GAMEMD 0x6528C0
// Empty function.
void __cdecl FUN_006528C0()
{
}

// FUNCTION: GAMEMD 0x652910
// Empty function.
void __cdecl FUN_00652910()
{
}

// FUNCTION: GAMEMD 0x652CD0
// Stores several members.
void Obj_00652CD0::FUN_00652CD0()
{
    unknown_14AC = 4;
    unknown_14FC = 0x19;
}

// FUNCTION: GAMEMD 0x653750
// Empty function that pops its stack arguments.
void __stdcall FUN_00653750(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x653830
// Calls other functions. Vtable slot 37 of RadarClass (RTTI) and 5 derived vtable(s).
bool Obj_00653830::FUN_00653830(int a1, int a2, int a3)
{
    return (FUN_004A9CA0(this, a2, a1, a2, a3) != 0) ? true : false;
}

// FUNCTION: GAMEMD 0x656CA0
// Returns a comparison result.
bool Obj_00656CA0::FUN_00656CA0() const
{
    return unknown_14AC == 1;
}

// FUNCTION: GAMEMD 0x656DC0
// Branching.
int Obj_00656DC0::FUN_00656DC0()
{
    return unknown_14B0 == 1 && unknown_14AC == 1;
}

// FUNCTION: GAMEMD 0x656DE0
// Member getter (byte).
unsigned char Obj_00656DE0::FUN_00656DE0() const
{
    return unknown_14D8;
}

// FUNCTION: GAMEMD 0x656E70
// Branching.
int Obj_00656E70::FUN_00656E70()
{
    return unknown_14B0 == 3 && unknown_14AC == 1;
}
