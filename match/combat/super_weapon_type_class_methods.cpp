// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x6CEEB0  SuperWeaponTypeClass::FindFirstOfAction (__fastcall)
//   GLOBAL:   GAMEMD 0xA8E330  SuperWeaponTypeClass::Array

#include "super_weapon_type_class_methods.h"

// FUNCTION: GAMEMD 0x6CEEB0  (__fastcall)
// Scan the global Array for the first superweapon type whose Action matches the
// requested one. The argument arrives in ECX (fastcall); the loop hoists Items
// into EDI and walks a parallel pointer (EDX) for the `->Action` dereference,
// returning the indexed `Items[i]` on a hit, null otherwise.
SuperWeaponTypeClass* SuperWeaponTypeClass::FindFirstOfAction(int action)
{
    for (int i = 0; i < SuperWeaponTypeClass_Array.Count; ++i)
    {
        if (SuperWeaponTypeClass_Array.Items[i]->Action == action)
            return SuperWeaponTypeClass_Array.Items[i];
    }
    return 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8E330
SuperWeaponTypeVector SuperWeaponTypeClass_Array;
// END defined globals
