// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu139_b_methods.h"

// FUNCTION: GAMEMD 0x5BC400
// Branching.
void __cdecl FUN_005BC400()
{
    DAT_00ABF239 = 0;
    if (DAT_00ABF240 != 0)
    {
        DAT_00ABF23A = 0;
        ShowWindow(DAT_00ABF240, 0);
    }
}

// FUNCTION: GAMEMD 0x5BCC40
// Stores several members; pops its stack arguments.
void Obj_005BCC40::FUN_005BCC40(int a1, int a2)
{
    unknown_271C = a1;
    unknown_2720 = a2;
}

// FUNCTION: GAMEMD 0x5BCC60
// Stores several members; pops its stack arguments.
void Obj_005BCC60::FUN_005BCC60(int a1, int a2, int a3, int a4)
{
    unknown_2724 = a1;
    unknown_2728 = a2;
    unknown_272C = a3;
    unknown_2730 = a4;
}

// FUNCTION: GAMEMD 0x5BD570
// Branching.
Obj_005BD570* FUN_005BD570(Obj_005BD570* a1, int a2, int a3)
{
    a1->unknown_00 = 0;
    a1->unknown_04 = 0;
    a1->unknown_08 = 0;
    a1->unknown_0C = 0;
    int c0 = FUN_005BD5C0(a1, a2, a3);
    if (c0 == 0)
    {
        a1->unknown_00 = 1;
    }
    return a1;
}
