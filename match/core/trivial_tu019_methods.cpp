// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu019_methods.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/aircraft_type_class.h"

GG_STATIC_ASSERT(offsetof(AircraftClass, Type) == 0x6C4);
GG_STATIC_ASSERT(sizeof(((AircraftClass*)0)->Type) == 4);
GG_STATIC_ASSERT(offsetof(AbstractTypeClass, UIName) == 0x60);
GG_STATIC_ASSERT(sizeof(((AbstractTypeClass*)0)->UIName) == 4);

// FUNCTION: GAMEMD 0x414A10
// Empty function that pops its stack arguments.
void __stdcall FUN_00414A10(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x41A140
// Empty function.
void __cdecl FUN_0041A140()
{
}

// FUNCTION: GAMEMD 0x41B900
// Empty function. Vtable slot 228 of AircraftClass (RTTI).
void Obj_0041B900::FUN_0041B900()
{
}

// FUNCTION: GAMEMD 0x41B910
// Tail-calls a virtual method of its receiver. Vtable slot 32 of AircraftClass (RTTI).
void Obj_0041B910::FUN_0041B910()
{
    vf_20();
}

// FUNCTION: GAMEMD 0x41B9E0
// Member getter (byte). Vtable slot 268 of AircraftClass (RTTI).
unsigned char Obj_0041B9E0::FUN_0041B9E0() const
{
    return unknown_6D5;
}

// FUNCTION: GAMEMD 0x41C050
// Returns a comparison result. Vtable slot 164 of FootClass (RTTI) and 3 derived vtable(s).
bool Obj_0041C050::FUN_0041C050() const
{
    return unknown_5D4 != 0;
}

// FUNCTION: GAMEMD 0x41C060
// Returns a constant boolean. Vtable slot 313 of FootClass (RTTI) and 2 derived vtable(s).
bool Obj_0041C060::FUN_0041C060() const
{
    return false;
}

// FUNCTION: GAMEMD 0x41C070
// Member getter (byte). Vtable slot 48 of FootClass (RTTI) and 3 derived vtable(s).
unsigned char Obj_0041C070::FUN_0041C070() const
{
    return unknown_6B6;
}

// FUNCTION: GAMEMD 0x41C080
// Returns a constant boolean. Vtable slot 318 of FootClass (RTTI) and 2 derived vtable(s).
bool Obj_0041C080::FUN_0041C080() const
{
    return false;
}

// FUNCTION: GAMEMD 0x41C0F0
// Empty function. Vtable slot 325 of FootClass (RTTI) and 2 derived vtable(s).
void Obj_0041C0F0::FUN_0041C0F0()
{
}

// FUNCTION: GAMEMD 0x41C100
// Empty function. Vtable slot 326 of FootClass (RTTI) and 2 derived vtable(s).
void Obj_0041C100::FUN_0041C100()
{
}

// FUNCTION: GAMEMD 0x41C110
// Empty function. Vtable slot 327 of FootClass (RTTI) and 2 derived vtable(s).
void Obj_0041C110::FUN_0041C110()
{
}

// FUNCTION: GAMEMD 0x41C120
// Empty function that pops its stack arguments. Vtable slot 328 of FootClass (RTTI) and 2 derived vtable(s).
void Obj_0041C120::FUN_0041C120(int a1)
{
}

// FUNCTION: GAMEMD 0x41C130
// Empty function that pops its stack arguments. Vtable slot 333 of FootClass (RTTI) and 2 derived vtable(s).
void Obj_0041C130::FUN_0041C130(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x41C140
// Empty function that pops its stack arguments. Vtable slot 336 of FootClass (RTTI) and 3 derived vtable(s).
void Obj_0041C140::FUN_0041C140(int a1)
{
}

// FUNCTION: GAMEMD 0x41C150
// Stores its argument in a member; pops its stack arguments. Vtable slot 189 of FootClass (RTTI) and 3 derived vtable(s).
Arg1_0041C150* Obj_0041C150::FUN_0041C150(Arg1_0041C150* a1)
{
    a1->unknown_00 = unknown_560;
    return a1;
}

// FUNCTION: GAMEMD 0x41C160
// Stores its argument in a member; pops its stack arguments. Vtable slot 190 of FootClass (RTTI) and 3 derived vtable(s).
void Obj_0041C160::FUN_0041C160(int a1)
{
    unknown_560 = a1;
}

// FUNCTION: GAMEMD 0x41C170
// Returns a constant. Vtable slot 12 of AircraftClass (RTTI).
int AircraftClass::vf_12()
{
    return 0x6D8;
}

// FUNCTION: GAMEMD 0x41C180
// Returns a constant. Vtable slot 11 of AircraftClass (RTTI).
int AircraftClass::vf_11()
{
    return 2;
}

// FUNCTION: GAMEMD 0x41C1D0
// Member getter (dword). Vtable slot 36 of AircraftClass (RTTI).
const wchar_t* AircraftClass::vf_36()
{
    return Type->UIName;
}

// FUNCTION: GAMEMD 0x41C200
// Member getter (dword). Vtable slot 34 of AircraftClass (RTTI).
ObjectTypeClass* AircraftClass::vf_34()
{
    return Type;
}
