// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu019_methods.h"
#include "_layout/aircraft_class.h"
#include "_layout/aircraft_type_class.h"

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
// Vtable slot 164 of FootClass (RTTI). Whether a team is set.
bool FootClass::vf_164()
{
    return Team != 0;
}

// FUNCTION: GAMEMD 0x41C060
// Vtable slot 313 of FootClass (RTTI). Returns false.
bool FootClass::vf_313()
{
    return false;
}

// FUNCTION: GAMEMD 0x41C070
// Vtable slot 48 of FootClass (RTTI). Member getter (byte).
bool FootClass::vf_48()
{
    return FrozenStill;
}

// FUNCTION: GAMEMD 0x41C080
// Vtable slot 318 of FootClass (RTTI). Returns false.
bool FootClass::vf_318()
{
    return false;
}

// FUNCTION: GAMEMD 0x41C0F0
// Vtable slot 325 of FootClass (RTTI). Empty.
void FootClass::vf_325()
{
}

// FUNCTION: GAMEMD 0x41C100
// Vtable slot 326 of FootClass (RTTI). Empty.
void FootClass::vf_326()
{
}

// FUNCTION: GAMEMD 0x41C110
// Vtable slot 327 of FootClass (RTTI). Empty.
void FootClass::vf_327()
{
}

// FUNCTION: GAMEMD 0x41C120
// Vtable slot 328 of FootClass (RTTI). Empty; pops its argument.
void FootClass::vf_328(int a1)
{
}

// FUNCTION: GAMEMD 0x41C130
// Vtable slot 333 of FootClass (RTTI). Empty; pops its arguments.
void FootClass::vf_333(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x41C140
// Vtable slot 336 of FootClass (RTTI). Empty; pops its argument.
void FootClass::vf_336(int a1)
{
}

// FUNCTION: GAMEMD 0x41C150
// Vtable slot 189 of FootClass (RTTI). Copies the cell at +0x560 to the caller's result.
CellStruct FootClass::vf_189()
{
    return LastFlightMapCoords;
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
