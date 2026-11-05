// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu086_methods.h"
#include "_layout/foot_class.h"

// FUNCTION: GAMEMD 0x4D94A0
// Stores its argument in a member; pops its stack arguments. Vtable slot 287 of FootClass (RTTI) and 3 derived vtable(s).
void Obj_004D94A0::FUN_004D94A0(int a1)
{
    unknown_5A0 = a1;
}

// FUNCTION: GAMEMD 0x4D9C00
// Vtable slot 329 of FootClass (RTTI). Returns zero.
int FootClass::vf_329()
{
    return 0;
}

// FUNCTION: GAMEMD 0x4DA020
// Stores its argument in a member; pops its stack arguments.
Arg1_004DA020* __stdcall FUN_004DA020(Arg1_004DA020* a1, Arg2_004DA020* a2)
{
    a1->unknown_00 = a2->unknown_00;
    return a1;
}

// FUNCTION: GAMEMD 0x4DA2A0
// Calls other functions.
bool Obj_004DA2A0::FUN_004DA2A0()
{
    return (vf_97() == 7) ? true : false;
}

// FUNCTION: GAMEMD 0x4DBA30
// Vtable slot 338 of FootClass (RTTI). Empty.
void FootClass::vf_338()
{
}

// FUNCTION: GAMEMD 0x4DBA40
// Vtable slot 339 of FootClass (RTTI). Empty.
void FootClass::vf_339()
{
}

// FUNCTION: GAMEMD 0x4DDC40
// Vtable slot 47 of FootClass (RTTI). Refuses while in a tube; otherwise the ObjectClass slot.
bool FootClass::vf_47(AbstractClass* a1)
{
    if (TubeIndex >= 0)
    {
        return false;
    }
    return ObjectClass::vf_47(a1);
}

// FUNCTION: GAMEMD 0x4DE750
// Vtable slot 309 of FootClass (RTTI). Empty; pops its argument.
void FootClass::vf_309(int a1)
{
}

// FUNCTION: GAMEMD 0x4DE760
// Vtable slot 310 of FootClass (RTTI). Empty; pops its argument.
void FootClass::vf_310(FootClass* a1)
{
}

// FUNCTION: GAMEMD 0x4DF1A0
// Vtable slot 298 of FootClass (RTTI). Clears the mega-mission state.
void FootClass::vf_298()
{
    MegaMission = -1;
    MegaDestination = 0;
    MegaTarget = 0;
    HaveAttackMoveTarget = 0;
}

// FUNCTION: GAMEMD 0x4DF1C0
// Vtable slot 299 of FootClass (RTTI). Whether a mega mission is set.
bool FootClass::vf_299()
{
    return MegaMission != -1;
}

// FUNCTION: GAMEMD 0x4DF1D0
// Vtable slot 300 of FootClass (RTTI). Member getter (byte).
bool FootClass::vf_300()
{
    return HaveAttackMoveTarget;
}

// FUNCTION: GAMEMD 0x4DF1E0
// Vtable slot 301 of FootClass (RTTI). Member getter (dword).
int FootClass::vf_301()
{
    return MegaMission;
}

// FUNCTION: GAMEMD 0x4DF310
// Vtable slot 305 of FootClass (RTTI). Returns a comparison result.
bool FootClass::vf_305()
{
    return MegaMission == 0x1D;
}

// FUNCTION: GAMEMD 0x4DFA50
// Branching. Vtable slot 78 of FootClass (RTTI) and 3 derived vtable(s).
unsigned char FUN_004DFA50(Obj_004DFA50* a1, int a2)
{
    if (a1->unknown_6AD != 0)
    {
        return 0;
    }
    return FUN_005F6C30(a1, a2);
}

// FUNCTION: GAMEMD 0x4E0C30
// Empty function.
void __cdecl FUN_004E0C30()
{
}
