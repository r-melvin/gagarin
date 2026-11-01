// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

// 0x403470/0x403480 pass ECX+0x68 to timer entries 0x407150/0x407170.
#include "trivial_tu000_methods.h"

// FUNCTION: GAMEMD 0x401FB0
// Member getter (dword).
int Obj_00401FB0::FUN_00401FB0() const
{
    return unknown_0C;
}

// FUNCTION: GAMEMD 0x402020
// Member getter (dword).
int Obj_00402020::FUN_00402020() const
{
    return unknown_14;
}

// FUNCTION: GAMEMD 0x402850
// Stores several members.
void Obj_00402850::FUN_00402850()
{
    unknown_08 = 0;
    unknown_04 = 0;
}

// FUNCTION: GAMEMD 0x403460
// Returns a constant.
int __cdecl FUN_00403460()
{
    return 0x80040000;
}

// FUNCTION: GAMEMD 0x403470
// Tail-forwards to another function.
void FUN_00403470(int a1, int a2)
{
    FUN_00407150(reinterpret_cast<Timer_00401000*>(a1 + 0x68), a2);
}

// FUNCTION: GAMEMD 0x403480
// Tail-forwards to another function.
void FUN_00403480(int a1, int a2)
{
    FUN_00407170(reinterpret_cast<Timer_00401000*>(a1 + 0x68), a2);
}

// FUNCTION: GAMEMD 0x403490
// Member getter (dword).
int Obj_00403490::FUN_00403490() const
{
    return unknown_F4;
}

// FUNCTION: GAMEMD 0x4034A0
// Member getter (dword).
int Obj_004034A0::FUN_004034A0() const
{
    return unknown_F0;
}
