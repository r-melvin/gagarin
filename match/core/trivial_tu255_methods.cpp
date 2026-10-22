// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu255_methods.h"

// FUNCTION: GAMEMD 0x72DAB0
// Returns a global (dword).
int __cdecl FUN_0072DAB0()
{
    return DAT_00B0FBBC;
}

// FUNCTION: GAMEMD 0x72DAF0
// Returns a global (dword).
int __cdecl FUN_0072DAF0()
{
    return DAT_00B0FBC0;
}

// FUNCTION: GAMEMD 0x72E270
// Returns a global (dword).
int __cdecl FUN_0072E270()
{
    return DAT_00B0FBC8;
}

// FUNCTION: GAMEMD 0x72E290
// Returns a global (dword).
int __cdecl FUN_0072E290()
{
    return DAT_00B0FBD0;
}

// FUNCTION: GAMEMD 0x72E2B0
// Returns a global (dword).
int __cdecl FUN_0072E2B0()
{
    return DAT_00B0FBD8;
}

// FUNCTION: GAMEMD 0x72F4C0
// Returns a global (dword).
int __cdecl FUN_0072F4C0()
{
    return DAT_00B0FC04;
}

// FUNCTION: GAMEMD 0x72F4F0
// Returns a global (dword).
int __cdecl FUN_0072F4F0()
{
    return DAT_00B0FC00;
}

// FUNCTION: GAMEMD 0x72F500
// Returns a global (dword).
int __cdecl FUN_0072F500()
{
    return DAT_00B0FBF4;
}

// FUNCTION: GAMEMD 0x72F520
// Returns a global (dword).
int __cdecl FUN_0072F520()
{
    return DAT_00B0FBEC;
}

// FUNCTION: GAMEMD 0x72F530
// Returns a global (dword).
int __cdecl FUN_0072F530()
{
    return DAT_00B0FBF0;
}

// FUNCTION: GAMEMD 0x730660
// Stores, then tail-calls.
void FUN_00730660(Obj_00730660* a1, int a2)
{
    FUN_00730100(a1, a2);
    FUN_0072FA10();
}

// FUNCTION: GAMEMD 0x730740
// Returns a global (dword).
int __cdecl FUN_00730740()
{
    return DAT_00A8EB84;
}

// FUNCTION: GAMEMD 0x730750
// Returns a global (dword).
int __cdecl FUN_00730750()
{
    return DAT_00A8EB88;
}
