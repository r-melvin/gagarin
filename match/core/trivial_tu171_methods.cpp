// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu171_methods.h"

// FUNCTION: GAMEMD 0x600550
// Tail-calls a method on a global object.
void FUN_00600550(int a1, int a2)
{
    FUN_006B9530(DAT_00AC4848, a2);
}

// FUNCTION: GAMEMD 0x600660
// Member getter (dword).
int Obj_00600660::FUN_00600660() const
{
    return unknown_00;
}

// FUNCTION: GAMEMD 0x603DB0
// Calls other functions.
void FUN_00603DB0(Obj_00603DB0* a1, int a2)
{
    SendMessageA(a1, 0x4E5, 0, a2 & 0xFF);
}

// FUNCTION: GAMEMD 0x6071D0
// Calls other functions.
void Obj_006071D0::FUN_006071D0()
{
    EnumChildWindows(this, 0x606800, 0);
}

// FUNCTION: GAMEMD 0x624080
// Stores its argument in a member.
Obj_00624080* Obj_00624080::FUN_00624080()
{
    unknown_00 = 0x7EF720;
    return this;
}

// FUNCTION: GAMEMD 0x624090
// Stores its argument in a member.
void Obj_00624090::FUN_00624090()
{
    unknown_00 = 0x7EF720;
}

// FUNCTION: GAMEMD 0x6241C0
// Member getter (byte). Vtable slot 2 of OwnerDraw::SimpleDialogControl (RTTI) and 4 derived vtable(s).
unsigned char Obj_006241C0::FUN_006241C0() const
{
    return unknown_08;
}

// FUNCTION: GAMEMD 0x6241E0
// Returns a constant boolean. Vtable slot 4 of OwnerDraw::SimpleDialogControl (RTTI) and 1 derived vtable(s).
bool Obj_006241E0::FUN_006241E0() const
{
    return false;
}
