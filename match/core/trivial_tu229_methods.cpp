// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu229_methods.h"

// FUNCTION: GAMEMD 0x6D1B00
// Empty function.
void __cdecl FUN_006D1B00()
{
}

// FUNCTION: GAMEMD 0x6D2B50
// Empty function that pops its stack arguments.
void __stdcall FUN_006D2B50(int a1, int a2)
{
}

// FUNCTION: GAMEMD 0x6D4E00
// Stores several members.
void Obj_006D4E00::FUN_006D4E00()
{
    unknown_A4 = -1;
    unknown_24 = 0;
}

// FUNCTION: GAMEMD 0x6D6170
// Stores several members; pops its stack arguments.
Arg1_006D6170* Obj_006D6170::FUN_006D6170(Arg1_006D6170* a1)
{
    a1->unknown_00 = unknown_D64;
    a1->unknown_04 = unknown_D68;
    return a1;
}

// FUNCTION: GAMEMD 0x6D8630
// Empty function.
void __cdecl FUN_006D8630()
{
}

// FUNCTION: GAMEMD 0x6DA350
// Empty function.
void __cdecl FUN_006DA350()
{
}

// FUNCTION: GAMEMD 0x6DA370
// Empty function that pops its stack arguments.
void __stdcall FUN_006DA370(int a1)
{
}

// FUNCTION: GAMEMD 0x6DC400
// Empty function.
void __cdecl FUN_006DC400()
{
}

// FUNCTION: GAMEMD 0x6DC410
// Empty function.
void __cdecl FUN_006DC410()
{
}

// FUNCTION: GAMEMD 0x6DC450
// Returns a constant. Vtable slot 11 of Tactical (RTTI).
int Obj_006DC450::FUN_006DC450() const
{
    return 0x38;
}

// FUNCTION: GAMEMD 0x6DC460
// Returns a constant. Vtable slot 12 of Tactical (RTTI).
int Obj_006DC460::FUN_006DC460() const
{
    return 0xE18;
}
