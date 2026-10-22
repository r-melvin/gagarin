// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu275_methods.h"

// FUNCTION: GAMEMD 0x767EC0
// Stores, then tail-calls.
void Obj_00767EC0::FUN_00767EC0()
{
    unknown_00 = 0x7F7104;
    FUN_005CB6C0();
}

// FUNCTION: GAMEMD 0x769C20
// Stores several members; pops its stack arguments.
Obj_00769C20* Obj_00769C20::FUN_00769C20(Arg1_00769C20* a1)
{
    unknown_04 = a1->unknown_04;
    unknown_08 = a1->unknown_08;
    return this;
}

// FUNCTION: GAMEMD 0x769C40
// Returns its receiver.
Obj_00769C40* Obj_00769C40::FUN_00769C40()
{
    return this;
}

// FUNCTION: GAMEMD 0x769D70
// Stores several members.
Obj_00769D70* FUN_00769D70(Obj_00769D70* a1, int a2)
{
    a1->unknown_04 = a2;
    a1->unknown_08 = 0;
    a1->unknown_00 = 0x7F71CC;
    return a1;
}

// FUNCTION: GAMEMD 0x76A5A0
// Updates one member in place. Vtable slot 2 of VectorCursor<H::V?$TRect::V?$VectorClass::TRect<int>> (RTTI).
Obj_0076A5A0* Obj_0076A5A0::FUN_0076A5A0()
{
    unknown_08++;
    return this;
}

// FUNCTION: GAMEMD 0x76A5B0
// Updates one member in place. Vtable slot 3 of VectorCursor<H::V?$TRect::V?$VectorClass::TRect<int>> (RTTI).
Obj_0076A5B0* Obj_0076A5B0::FUN_0076A5B0()
{
    unknown_08--;
    return this;
}
