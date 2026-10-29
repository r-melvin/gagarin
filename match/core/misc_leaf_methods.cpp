// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "misc_leaf_methods.h"

// FUNCTION: GAMEMD 0x407020
// Acquire. The initialiser runs only on the transition from zero; the bump
// happens either way, so it sits outside the guard.
void __cdecl FUN_00407020()
{
    if (DAT_0087E730 == 0) {
        FUN_0040A940();
    }

    ++DAT_0087E730;
}

// FUNCTION: GAMEMD 0x409310
int Obj_00409300b::FUN_00409310()
{
    FUN_004091C0(this, 0);
    return unknown_08;
}

// FUNCTION: GAMEMD 0x422BC0
int AnimClass_00422B00::FUN_00422BC0()
{
    return FUN_005F6BD0(this) + unknown_104;
}

// FUNCTION: GAMEMD 0x437F30
Pair8 Obj_00437F00::FUN_00437F30() const
{
    Pair8 result;

    result.a = unknown_00;
    result.b = unknown_04;

    return result;
}

int DAT_00a8ef54;

// FUNCTION: GAMEMD 0x4DB250
void __stdcall FUN_004DB250(unsigned int unused1, unsigned int unused2)
{
}

// FUNCTION: GAMEMD 0x4F42A0
void __stdcall FUN_004F42A0(void)
{
    DAT_00a8ef54 = 0;
}

// FUNCTION: GAMEMD 0x4F42E0
void __stdcall FUN_004F42E0(void)
{
    DAT_00a8ef54 = 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87E730
int DAT_0087E730;
// END defined globals
