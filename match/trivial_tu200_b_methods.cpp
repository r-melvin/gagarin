// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu200_b_methods.h"

// FUNCTION: GAMEMD 0x6810D0
// Calls other functions.
void Obj_006810D0::FUN_006810D0(int a1)
{
    unknown_186 = 0;
    FUN_007CA422(&unknown_108, a1, 0x3F);
}

// FUNCTION: GAMEMD 0x681150
// Calls other functions.
void Obj_00681150::FUN_00681150(int a1)
{
    unknown_293 = 0;
    FUN_007C91D0(&unknown_190, a1, 0x103);
}

// FUNCTION: GAMEMD 0x6811C0
// Calls other functions.
void Obj_006811C0::FUN_006811C0(int a1)
{
    unknown_3D7 = 0;
    FUN_007C91D0(&unknown_2D4, a1, 0x103);
}

// FUNCTION: GAMEMD 0x681200
// Stores several members; pops its stack arguments.
void Obj_00681200::FUN_00681200(Arg1_00681200* a1)
{
    unknown_3D8 = a1->unknown_00;
    unknown_3DC = a1->unknown_04;
}

// FUNCTION: GAMEMD 0x681240
// Stores several members; pops its stack arguments.
void Obj_00681240::FUN_00681240(Arg1_00681240* a1)
{
    unknown_3E0 = a1->unknown_00;
    unknown_3E4 = a1->unknown_04;
}

// FUNCTION: GAMEMD 0x681280
// Stores several members; pops its stack arguments.
void Obj_00681280::FUN_00681280(Arg1_00681280* a1)
{
    unknown_3E8 = a1->unknown_00;
    unknown_3EC = a1->unknown_04;
}
