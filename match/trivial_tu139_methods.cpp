// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu139_methods.h"

// FUNCTION: GAMEMD 0x5BC440
// Returns a global (dword).
int __cdecl FUN_005BC440()
{
    return DAT_00ABF23C;
}

// FUNCTION: GAMEMD 0x5BCC20
// Empty function.
void __cdecl FUN_005BCC20()
{
}

// FUNCTION: GAMEMD 0x5BCC30
// Member getter (dword).
int Obj_005BCC30::FUN_005BCC30() const
{
    return unknown_2718;
}

// FUNCTION: GAMEMD 0x5BCCE0
// Member getter (byte).
unsigned char Obj_005BCCE0::FUN_005BCCE0() const
{
    return unknown_2734;
}

// FUNCTION: GAMEMD 0x5BCD70
// Branching.
void Obj_005BCD70::FUN_005BCD70(int a1)
{
    if (DAT_00ABF23A != 0)
    {
        unknown_2710 = a1;
    }
}
