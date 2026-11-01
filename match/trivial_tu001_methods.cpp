// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu001_methods.h"

// FUNCTION: GAMEMD 0x405490
// Member getter (dword).
int Obj_00405490::FUN_00405490() const
{
    return unknown_158;
}

// FUNCTION: GAMEMD 0x4059F0
// Stores its argument in a member.
int Obj_004059F0::FUN_004059F0()
{
    unknown_C0->unknown_1C = 4;
    return 0;
}

// FUNCTION: GAMEMD 0x406320
// Branching.
int Obj_00406320::FUN_00406320()
{
    return unknown_24->unknown_10 & 1 != 0 && unknown_24->unknown_4C == 0;
}

// FUNCTION: GAMEMD 0x406740
// Stores to a global.
void __cdecl FUN_00406740()
{
    DAT_00816108 = 1;
}

// FUNCTION: GAMEMD 0x406750
// Returns a global (dword).
int __cdecl FUN_00406750()
{
    return DAT_00816108;
}
