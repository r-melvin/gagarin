// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu284_methods.h"

// FUNCTION: GAMEMD 0x7754C0
// Member getter (dword).
int Obj_007754C0::FUN_007754C0() const
{
    return unknown_5C;
}

// FUNCTION: GAMEMD 0x775B30
// Returns a global (dword).
int __cdecl FUN_00775B30()
{
    return DAT_00B72F4C;
}

// FUNCTION: GAMEMD 0x775B40
// Returns zero; pops its stack arguments.
int __stdcall FUN_00775B40(int a1, int a2, int a3, int a4)
{
    return 0;
}
