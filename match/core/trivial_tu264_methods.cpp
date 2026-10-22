// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu264_methods.h"

// FUNCTION: GAMEMD 0x752AB0
// Branching.
void FUN_00752AB0(int a1)
{
    DAT_00846614 = a1;
    if (a1 >= 0xFF)
    {
        DAT_00846614 = 0xFF;
    }
}

// FUNCTION: GAMEMD 0x7533A0
// Returns a constant boolean.
bool __cdecl FUN_007533A0()
{
    return true;
}

// FUNCTION: GAMEMD 0x753570
// Stores to a global.
int __cdecl FUN_00753570()
{
    DAT_00B1D3D8++;
    return DAT_00B1D3D8;
}

// FUNCTION: GAMEMD 0x753A30
// Calls other functions.
void FUN_00753A30(int a1, int a2)
{
    FUN_0043AE50(DAT_00B2D93C, a2);
    DAT_00B2D928 = 0x7E2198;
}

// FUNCTION: GAMEMD 0x753AB0
// Calls other functions.
void FUN_00753AB0(int a1, int a2)
{
    FUN_0043AE50(DAT_00B2D804, a2);
    DAT_00B2D7F0 = 0x7E2198;
}

// FUNCTION: GAMEMD 0x753AD0
// Empty function.
void __cdecl FUN_00753AD0()
{
}

// FUNCTION: GAMEMD 0x753AE0
// Empty function.
void __cdecl FUN_00753AE0()
{
}

// FUNCTION: GAMEMD 0x753C60
// Returns the address of a global.
void* __cdecl FUN_00753C60()
{
    return DAT_00B2FF78;
}

// FUNCTION: GAMEMD 0x754900
// Returns its receiver.
Obj_00754900* Obj_00754900::FUN_00754900()
{
    return this;
}
