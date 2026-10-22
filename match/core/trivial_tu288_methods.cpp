// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu288_methods.h"

// FUNCTION: GAMEMD 0x77D200
// Tail-forwards to another function. Vtable slot 4 of SimpleWonlineDialogControl (RTTI) and 2 derived vtable(s).
void FUN_0077D200(Obj_0077D200* a1, int a2)
{
    FUN_0077F900(a1, a2);
}

// FUNCTION: GAMEMD 0x785360
// Tail-calls a method on a global object.
void __cdecl FUN_00785360()
{
    FUN_00783C80(0, 0);
}

// FUNCTION: GAMEMD 0x796B20
// Empty function.
void __cdecl FUN_00796B20()
{
}

// FUNCTION: GAMEMD 0x7AB330
// Returns zero; pops its stack arguments. Vtable slot 12 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AB330::FUN_007AB330(int a1, int a2, int a3, int a4) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AB340
// Returns zero; pops its stack arguments. Vtable slot 25 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AB340::FUN_007AB340(int a1, int a2, int a3) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AC4A0
// Returns zero; pops its stack arguments. Vtable slot 38 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AC4A0::FUN_007AC4A0(int a1, int a2, int a3) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AC4B0
// Returns zero; pops its stack arguments. Vtable slot 39 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AC4B0::FUN_007AC4B0(int a1, int a2, int a3) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AC4C0
// Returns zero; pops its stack arguments. Vtable slot 45 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AC4C0::FUN_007AC4C0(int a1, int a2, int a3) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AC4D0
// Returns zero; pops its stack arguments. Vtable slot 46 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AC4D0::FUN_007AC4D0(int a1, int a2, int a3) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AC4E0
// Returns zero; pops its stack arguments. Vtable slot 47 of CChatEventSink (RTTI) and 1 derived vtable(s).
int Obj_007AC4E0::FUN_007AC4E0(int a1, int a2, int a3) const
{
    return 0;
}

// FUNCTION: GAMEMD 0x7AC4F0
// Empty function.
void __cdecl FUN_007AC4F0()
{
}

// FUNCTION: GAMEMD 0x7AD610
// Returns zero; pops its stack arguments. Vtable slot 6 of ATL::CComObject<CDownloadEventSink> (RTTI).
int Obj_007AD610::FUN_007AD610(int a1) const
{
    return 0;
}
