// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu180_methods.h"

// FUNCTION: GAMEMD 0x634800
// Returns the address of a member.
int* Obj_00634800::FUN_00634800()
{
    return &unknown_38;
}

// FUNCTION: GAMEMD 0x634950
// Stores its argument in a member.
void Obj_00634950::FUN_00634950()
{
    unknown_1C = 1;
}

// FUNCTION: GAMEMD 0x634960
// Member getter (byte).
unsigned char Obj_00634960::FUN_00634960() const
{
    return unknown_1C;
}

// FUNCTION: GAMEMD 0x636110
// Member getter (dword).
int Obj_00636110::FUN_00636110() const
{
    return unknown_00;
}

// FUNCTION: GAMEMD 0x636520
// Stores its argument in a member.
void Obj_00636520::FUN_00636520()
{
    unknown_1C = 1;
}

// FUNCTION: GAMEMD 0x636530
// Stores its argument in a member.
void Obj_00636530::FUN_00636530()
{
    unknown_1C = 0;
}

// FUNCTION: GAMEMD 0x636540
// Member getter (byte).
unsigned char Obj_00636540::FUN_00636540() const
{
    return unknown_1C;
}

// FUNCTION: GAMEMD 0x636550
// Branching.
int Obj_00636550::FUN_00636550()
{
    return unknown_00->unknown_AC == 0x1C || unknown_00->unknown_B4 == 0x1C;
}

// FUNCTION: GAMEMD 0x636570
// Branching.
int Obj_00636570::FUN_00636570()
{
    return unknown_14 > 0 && (unknown_8C == -1 || unknown_8C > 0);
}

// FUNCTION: GAMEMD 0x636DA0
// Branching.
unsigned char Obj_00636DA0::FUN_00636DA0(int a1)
{
    if (unknown_8C == -1)
    {
        return 0;
    }
    return a1 >= unknown_8C;
}

// FUNCTION: GAMEMD 0x636DD0
// Branching.
int Obj_00636DD0::FUN_00636DD0()
{
    if (unknown_8C == -1)
    {
        return unknown_14;
    }
    return unknown_8C;
}

// FUNCTION: GAMEMD 0x636DE0
// Branching.
int Obj_00636DE0::FUN_00636DE0()
{
    if (unknown_8C == -1)
    {
        return 0;
    }
    return unknown_14 - unknown_8C;
}

// FUNCTION: GAMEMD 0x636FA0
// Stores several members; pops its stack arguments.
void Obj_00636FA0::FUN_00636FA0(int a1, int a2)
{
    unknown_90 = a1;
    unknown_94 = a2;
    unknown_98 = 1;
}

// FUNCTION: GAMEMD 0x636FC0
// Member getter (dword).
int Obj_00636FC0::FUN_00636FC0() const
{
    return unknown_90;
}

// FUNCTION: GAMEMD 0x636FD0
// Member getter (dword).
int Obj_00636FD0::FUN_00636FD0() const
{
    return unknown_94;
}

// FUNCTION: GAMEMD 0x636FE0
// Branching.
int Obj_00636FE0::FUN_00636FE0()
{
    return unknown_94 > 0 || unknown_94 == 0;
}

// FUNCTION: GAMEMD 0x637000
// Returns a comparison result.
bool Obj_00637000::FUN_00637000() const
{
    return unknown_94 > 0;
}

// FUNCTION: GAMEMD 0x637010
// Returns a comparison result.
bool Obj_00637010::FUN_00637010() const
{
    return unknown_94 == 0;
}

// FUNCTION: GAMEMD 0x637020
// Member getter (byte).
unsigned char Obj_00637020::FUN_00637020() const
{
    return unknown_98;
}

// FUNCTION: GAMEMD 0x637030
// Member getter (byte).
unsigned char Obj_00637030::FUN_00637030() const
{
    return unknown_99;
}

// FUNCTION: GAMEMD 0x637060
// Stores to a global.
void FUN_00637060(int a1)
{
    DAT_00AC4B80 = a1;
}

// FUNCTION: GAMEMD 0x637DB0
// Branching.
bool FUN_00637DB0(int a1)
{
    if (DAT_00AC4CF4 == 0 || a1 != 4)
    {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x638B50
// Branching.
int FUN_00638B50(int a1)
{
    return (unsigned char)a1 == 9 || (unsigned char)a1 == 6 || (unsigned char)a1 == 7;
}

// FUNCTION: GAMEMD 0x638C20
// Branching.
int FUN_00638C20(int a1)
{
    return a1 == 7 || a1 == 8 || a1 == 9;
}

// FUNCTION: GAMEMD 0x63A210
// Stores, then tail-calls.
void Obj_0063A210::FUN_0063A210()
{
    int c0 = FUN_00734E60(this, 0, DAT_00836BD4, 0xCA1);
    FUN_00730A90(c0, 0x1E0);
}

// FUNCTION: GAMEMD 0x63A4A0
// Stores to a global.
void FUN_0063A4A0(int a1)
{
    DAT_00AC4C90 = a1;
}

// FUNCTION: GAMEMD 0x63AD30
// Stores to a global.
void FUN_0063AD30(int a1)
{
    DAT_00AC4C38 = a1;
}

// FUNCTION: GAMEMD 0x63AD40
// Returns a global (dword).
int __cdecl FUN_0063AD40()
{
    return DAT_00AC4C38;
}

// FUNCTION: GAMEMD 0x63D500
// Branching.
int Obj_0063D500::FUN_0063D500()
{
    int c0 = vf_97();
    if (c0 == 0xB)
    {
        return FUN_00731CE0();
    }
    return -1;
}

// FUNCTION: GAMEMD 0x63D520
// Branching.
int Obj_0063D520::FUN_0063D520()
{
    int c0 = vf_301();
    if (c0 == 0x1D)
    {
        return FUN_00731CD0();
    }
    return -1;
}
