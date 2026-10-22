// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu130_methods.h"

// FUNCTION: GAMEMD 0x58B760
// Tail-calls a method on a global object.
void FUN_0058B760(int a1, int a2)
{
    FUN_005958E0(DAT_00ABDFD8, a2);
}

// FUNCTION: GAMEMD 0x58B770
// Calls other functions.
void __cdecl FUN_0058B770()
{
    DAT_00ABE890.FUN_0065C6D0(0);
}

// FUNCTION: GAMEMD 0x58B7B0
// Empty function.
void __cdecl FUN_0058B7B0()
{
}

// FUNCTION: GAMEMD 0x58B7C0
// Empty function.
void __cdecl FUN_0058B7C0()
{
}

// FUNCTION: GAMEMD 0x58B7E0
// Returns a global (dword).
int __cdecl FUN_0058B7E0()
{
    return DAT_00ABDFD4;
}

// FUNCTION: GAMEMD 0x58B7F0
// Returns a global (dword).
int __cdecl FUN_0058B7F0()
{
    return DAT_00ABDFD0;
}

// FUNCTION: GAMEMD 0x58B800
// Returns a global (dword).
int __cdecl FUN_0058B800()
{
    return DAT_00ABEC90;
}

// FUNCTION: GAMEMD 0x58B810
// Returns a global (dword).
int __cdecl FUN_0058B810()
{
    return DAT_00ABECD0;
}

// FUNCTION: GAMEMD 0x58BCD0
// Branching.
int FUN_0058BCD0(int a1)
{
    return a1 == 1 || a1 == 3 || a1 == 4;
}

// FUNCTION: GAMEMD 0x58BD20
// Branching.
int FUN_0058BD20(int a1)
{
    return a1 == 3 || a1 == 4;
}

// FUNCTION: GAMEMD 0x58BD40
// Branching.
int FUN_0058BD40(int a1)
{
    return a1 == 4 || a1 == 3;
}

// FUNCTION: GAMEMD 0x58BD60
// Branching.
int FUN_0058BD60(int a1)
{
    return a1 == 3 || a1 == 4;
}

// FUNCTION: GAMEMD 0x597D40
// Tail-forwards to another function.
void Obj_00597D40::FUN_00597D40()
{
    FUN_00558840();
}

// FUNCTION: GAMEMD 0x597F80
// Calls other functions. Vtable slot 5 of MapSeedClass (RTTI).
void Obj_00597F80::FUN_00597F80()
{
    FUN_00734E60(DAT_0082BC3C, 0, DAT_0082BA48, 0x15C4);
}

// FUNCTION: GAMEMD 0x597FA0
// Calls other functions. Vtable slot 6 of MapSeedClass (RTTI).
void Obj_00597FA0::FUN_00597FA0()
{
    FUN_00734E60(DAT_0082BC4C, 0, DAT_0082BA48, 0x15CA);
}

// FUNCTION: GAMEMD 0x597FC0
// Calls other functions. Vtable slot 7 of MapSeedClass (RTTI).
void Obj_00597FC0::FUN_00597FC0()
{
    FUN_00734E60(DAT_0082BC5C, 0, DAT_0082BA48, 0x15D0);
}

// FUNCTION: GAMEMD 0x597FE0
// Calls other functions. Vtable slot 8 of MapSeedClass (RTTI).
void Obj_00597FE0::FUN_00597FE0()
{
    FUN_00734E60(DAT_0082BC70, 0, DAT_0082BA48, 0x15D6);
}

// FUNCTION: GAMEMD 0x5A9C20
// Calls other functions.
void FUN_005A9C20(Obj_005A9C20* a1, int a2)
{
    FUN_005A9C40(a1, a2);
    FUN_007C978A(0x5AC190);
}
