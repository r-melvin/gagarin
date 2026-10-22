// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu099_methods.h"

// FUNCTION: GAMEMD 0x51F620
// Branching. Vtable slot 135 of InfantryClass (RTTI).
void FUN_0051F620(Obj_0051F620* a1, int a2)
{
    int c0 = FUN_00521320(a1, a2);
    if (c0 == -1)
    {
        a1->FUN_004D5070();
    }
}

// FUNCTION: GAMEMD 0x51FAF0
// Member getter (dword). Vtable slot 34 of InfantryClass (RTTI).
int Obj_0051FAF0::FUN_0051FAF0() const
{
    return unknown_6C0;
}

// FUNCTION: GAMEMD 0x5216C0
// Tail-forwards to another function. Vtable slot 27 of InfantryClass (RTTI).
void FUN_005216C0(Obj_005216C0* a1, int a2)
{
    FUN_004DED70(a1, a2);
}

// FUNCTION: GAMEMD 0x521B20
// Branching. Vtable slot 338 of InfantryClass (RTTI).
void Obj_00521B20::FUN_00521B20()
{
    int t1 = unknown_6C4;
    if (t1 == 6)
    {
        unknown_6C4 = -1;
    }
    if (t1 == 3)
    {
        unknown_6C4 = -1;
    }
    if (t1 == 0x11)
    {
        unknown_6C4 = -1;
    }
}

// FUNCTION: GAMEMD 0x521B40
// Branching. Vtable slot 339 of InfantryClass (RTTI).
void Obj_00521B40::FUN_00521B40()
{
    if (unknown_6E4 != 0)
    {
        unknown_6E4 = 0;
        vf_342(0x1B, 0, 0);
    }
}

// FUNCTION: GAMEMD 0x521C40
// Branching. Vtable slot 327 of InfantryClass (RTTI).
Obj_00521C40_6C0* Obj_00521C40::FUN_00521C40()
{
    if (unknown_6C0->unknown_EBC == 0)
    {
        unknown_6D4 = 0;
    }
    return unknown_6C0;
}

// FUNCTION: GAMEMD 0x5220F0
// Stores its argument in a member. Vtable slot 325 of InfantryClass (RTTI).
void Obj_005220F0::FUN_005220F0()
{
    unknown_6D8 = 1;
}

// FUNCTION: GAMEMD 0x5224D0
// Member getter (byte). Vtable slot 204 of InfantryClass (RTTI).
unsigned char Obj_005224D0::FUN_005224D0() const
{
    return unknown_6C0->unknown_EC3;
}

// FUNCTION: GAMEMD 0x5224E0
// Member getter (byte).
unsigned char Obj_005224E0::FUN_005224E0() const
{
    return unknown_6C0->unknown_EC8;
}

// FUNCTION: GAMEMD 0x5224F0
// Returns a comparison result.
unsigned char Obj_005224F0::FUN_005224F0() const
{
    return unknown_6C0->unknown_6C4 > -1;
}

// FUNCTION: GAMEMD 0x522540
// Member getter (byte).
unsigned char Obj_00522540::FUN_00522540() const
{
    return unknown_6C0->unknown_6AC;
}

// FUNCTION: GAMEMD 0x5228B0
// Tail-forwards to another function. Vtable slot 303 of InfantryClass (RTTI).
void FUN_005228B0(Obj_005228B0* a1, int a2)
{
    FUN_0070F070(a1, a2);
}

// FUNCTION: GAMEMD 0x5228C0
// Tail-forwards to another function. Vtable slot 304 of InfantryClass (RTTI).
void FUN_005228C0(Obj_005228C0* a1, int a2)
{
    FUN_0070F090(a1, a2);
}

// FUNCTION: GAMEMD 0x522A50
// Empty function that pops its stack arguments.
void __stdcall FUN_00522A50(int a1)
{
}

// FUNCTION: GAMEMD 0x522D00
// Branching.
void Obj_00522D00::FUN_00522D00()
{
    if (unknown_AC != 0xA)
    {
        vf_122(0xA, 0);
    }
}

// FUNCTION: GAMEMD 0x522D20
// Calls other functions.
void Obj_00522D20::FUN_00522D20()
{
    vf_122(5, 0);
}

// FUNCTION: GAMEMD 0x5232F0
// Returns a constant. Vtable slot 12 of InfantryClass (RTTI).
int Obj_005232F0::FUN_005232F0() const
{
    return 0x6F0;
}

// FUNCTION: GAMEMD 0x523340
// Returns a constant. Vtable slot 11 of InfantryClass (RTTI).
int Obj_00523340::FUN_00523340() const
{
    return 0xF;
}
