// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu002_methods.h"

// FUNCTION: GAMEMD 0x406E60
// Branching.
void FUN_00406E60(int a1, int a2)
{
    if (DAT_0087E728 != 0)
    {
        FUN_004033C0(DAT_0087E728, a2);
        DAT_0087E728 = 0;
    }
}

// FUNCTION: GAMEMD 0x407060
// Tail-forwards to another function.
void Obj_00407060::FUN_00407060()
{
    FUN_00407170(this, 0x4000);
}

// FUNCTION: GAMEMD 0x407090
// Returns a comparison result.
int Obj_00407090::FUN_00407090() const
{
    return unknown_04 != unknown_08;
}

// FUNCTION: GAMEMD 0x407F80
// Updates one member in place.
int Obj_00407F80::FUN_00407F80()
{
    unknown_88++;
    return unknown_88;
}

// FUNCTION: GAMEMD 0x4080A0
// Returns the address of a member.
int* Obj_004080A0::FUN_004080A0()
{
    return &unknown_A4;
}

// FUNCTION: GAMEMD 0x408EB0
// Stores its argument in a member.
int FUN_00408EB0(Obj_00408EB0* a1, int a2)
{
    a1->unknown_18 = a2;
    return 0;
}

// FUNCTION: GAMEMD 0x408EC0
// Member getter (dword).
int Obj_00408EC0::FUN_00408EC0() const
{
    return unknown_18;
}

// FUNCTION: GAMEMD 0x408ED0
// Member getter (dword).
int Obj_00408ED0::FUN_00408ED0() const
{
    return unknown_14;
}

// FUNCTION: GAMEMD 0x4090F0
// Member getter (dword).
int Obj_004090F0::FUN_004090F0() const
{
    return unknown_24;
}

// FUNCTION: GAMEMD 0x409330
// Member getter (dword).
int Obj_00409330::FUN_00409330() const
{
    return unknown_30;
}

// FUNCTION: GAMEMD 0x40AD80
// Tail-calls a method on a global object.
void __cdecl FUN_0040AD80()
{
    DAT_0087E8A8.FUN_00420130();
}
