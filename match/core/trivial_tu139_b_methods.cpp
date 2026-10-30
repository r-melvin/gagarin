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

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xABF239
unsigned char DAT_00ABF239;
// END defined globals
