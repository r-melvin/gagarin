// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu207_methods.h"

// FUNCTION: GAMEMD 0x697B60
// Empty function.
void __cdecl FUN_00697B60()
{
}

// FUNCTION: GAMEMD 0x69ACC0
// Member getter (dword).
int Obj_0069ACC0::FUN_0069ACC0() const
{
    return unknown_18C->unknown_00;
}

// FUNCTION: GAMEMD 0x69ADE0
// Stores its argument in a member; pops its stack arguments.
void Obj_0069ADE0::FUN_0069ADE0(unsigned char a1)
{
    unknown_17C = a1;
}

// FUNCTION: GAMEMD 0x69B700
// Branching.
int Obj_0069B700::FUN_0069B700()
{
    if (unknown_178 != -2)
    {
        return unknown_174;
    }
    return -2;
}

// FUNCTION: GAMEMD 0x69B740
// Branching.
int Obj_0069B740::FUN_0069B740()
{
    if (unknown_168 != -2)
    {
        return unknown_164;
    }
    return -2;
}

// FUNCTION: GAMEMD 0x69B8B0
// Empty function that pops its stack arguments.
void __stdcall FUN_0069B8B0(int a1, int a2)
{
}
