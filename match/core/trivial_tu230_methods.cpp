// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu230_methods.h"

// FUNCTION: GAMEMD 0x6E0040
// Returns a constant boolean; pops its stack arguments.
bool __stdcall FUN_006E0040(int a1, int a2, int a3, int a4)
{
    return true;
}

// FUNCTION: GAMEMD 0x6E0250
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E0250::FUN_006E0250(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->unknown_34A7 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E0270
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E0270::FUN_006E0270(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->unknown_34A6 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E0290
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E0290::FUN_006E0290(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->unknown_34A8 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E0ED0
// Branching.
unsigned char Obj_006E0ED0::FUN_006E0ED0(Arg1_006E0ED0* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_54EC = unknown_90;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x6E0FA0
// Calls other functions.
bool Obj_006E0FA0::FUN_006E0FA0(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->FUN_00689670(unknown_90, 1);
    return true;
}

// FUNCTION: GAMEMD 0x6E0FC0
// Calls other functions.
bool Obj_006E0FC0::FUN_006E0FC0(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->FUN_00689670(unknown_90, 0);
    return true;
}

// FUNCTION: GAMEMD 0x6E1720
// Calls other functions.
bool Obj_006E1720::FUN_006E1720(int a1, int a2, int a3, int a4)
{
    FUN_005BF390(unknown_90, false);
    return true;
}

// FUNCTION: GAMEMD 0x6E1740
// Calls other functions.
bool Obj_006E1740::FUN_006E1740(int a1, int a2, int a3, int a4)
{
    FUN_005BF390(unknown_90, true);
    return true;
}

// FUNCTION: GAMEMD 0x6E1B90
// Calls other functions.
bool FUN_006E1B90(Obj_006E1B90* a1, int a2, int a3, int a4, int a5, int a6)
{
    FUN_00720B20(DAT_00A83D10, a2, a1->unknown_90);
    return true;
}

// FUNCTION: GAMEMD 0x6E1BB0
// Calls other functions.
bool Obj_006E1BB0::FUN_006E1BB0(int a1, int a2, int a3, int a4)
{
    FUN_00752480(unknown_90, 2, -1);
    return true;
}

// FUNCTION: GAMEMD 0x6E1F90
// Branching.
unsigned char Obj_006E1F90::FUN_006E1F90(int a1, int a2, int a3, int a4)
{
    if (unknown_30 != 0)
    {
        unknown_30->FUN_006F0A70();
        return 1;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x6E1FB0
// Branching.
unsigned char FUN_006E1FB0(Obj_006E1FB0* a1, int a2, int a3, int a4, int a5, int a6)
{
    if (a1->unknown_30 != 0)
    {
        return FUN_0065D8E0(a1->unknown_30, -1);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6E1FD0
// Branching.
unsigned char Obj_006E1FD0::FUN_006E1FD0(int a1, int a2, int a3, int a4)
{
    if (unknown_30 != 0)
    {
        if (unknown_44 != -1)
        {
            return FUN_0065D8E0(unknown_30, unknown_44);
        }
        return 0;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6E21D0
// Returns a constant boolean; pops its stack arguments.
bool __stdcall FUN_006E21D0(int a1, int a2, int a3, int a4)
{
    return true;
}

// FUNCTION: GAMEMD 0x6E2950
// Calls other functions.
bool FUN_006E2950(int a1, int a2, int a3, int a4, int a5, int a6)
{
    FUN_00577C90(DAT_0087F7E8, a2, a3);
    return true;
}

// FUNCTION: GAMEMD 0x6E2BE0
// Calls other functions.
bool Obj_006E2BE0::FUN_006E2BE0(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->FUN_00689910(unknown_90, 1);
    return true;
}

// FUNCTION: GAMEMD 0x6E2C00
// Calls other functions.
bool Obj_006E2C00::FUN_006E2C00(int a1, int a2, int a3, int a4)
{
    DAT_00A8B230->FUN_00689910(unknown_90, 0);
    return true;
}

// FUNCTION: GAMEMD 0x6E2E20
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E2E20::FUN_006E2E20(int a1, int a2, int a3, int a4)
{
    DAT_008871E0->unknown_1670 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E2E40
// Stores its argument in a member; pops its stack arguments.
bool Obj_006E2E40::FUN_006E2E40(int a1, int a2, int a3, int a4)
{
    DAT_008871E0->unknown_1668 = unknown_90;
    return true;
}

// FUNCTION: GAMEMD 0x6E3300
// Branching.
unsigned char Obj_006E3300::FUN_006E3300(Arg1_006E3300* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_565C = unknown_90;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x6E3320
// Branching.
unsigned char Obj_006E3320::FUN_006E3320(Arg1_006E3320* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_5660 = unknown_90;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x6E3340
// Branching.
unsigned char Obj_006E3340::FUN_006E3340(Arg1_006E3340* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_5664 = unknown_90;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x6E3360
// Branching.
unsigned char Obj_006E3360::FUN_006E3360(Arg1_006E3360* a1, int a2, int a3, int a4)
{
    if (a1 != 0)
    {
        a1->unknown_5668 = unknown_90;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x6E3890
// Branching.
unsigned char Obj_006E3890::FUN_006E3890(int a1, int a2, int a3, int a4)
{
    if (unknown_30 != 0)
    {
        if (unknown_44 != -1)
        {
            return FUN_0065EC30(unknown_30, unknown_44);
        }
        return 0;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6E3B20
// Stores its argument in a member; pops its stack arguments.
bool __stdcall FUN_006E3B20(int a1, int a2, int a3, int a4)
{
    bool t1 = DAT_00A8B230->unknown_34A5;
    DAT_00A8B230->unknown_34A5 = DAT_00A8B230->unknown_34A5 == 0;
    return true;
}

// FUNCTION: GAMEMD 0x6E3B40
// Branching.
unsigned char Obj_006E3B40::FUN_006E3B40(Arg1_006E3B40* a1, int a2, int a3, int a4)
{
    if (a1 == 0)
    {
        return 0;
    }
    a1->FUN_0050BCD0(unknown_90);
    return 1;
}

// FUNCTION: GAMEMD 0x6E4020
// Branching.
unsigned char FUN_006E4020(Obj_006E4020* a1, int a2, int a3, int a4, int a5, int a6)
{
    if (a1->unknown_30 != 0)
    {
        FUN_006F1F30(a1->unknown_30, a2, a1->unknown_90);
        return 1;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x6E4630
// Returns a constant. Vtable slot 12 of TActionClass (RTTI).
int Obj_006E4630::FUN_006E4630() const
{
    return 0x94;
}

// FUNCTION: GAMEMD 0x6E4640
// Returns a constant. Vtable slot 11 of TActionClass (RTTI).
int Obj_006E4640::FUN_006E4640() const
{
    return 0x2F;
}

// FUNCTION: GAMEMD 0x6E4650
// Member getter (dword). Vtable slot 16 of TActionClass (RTTI).
int Obj_006E4650::FUN_006E4650() const
{
    return unknown_24;
}
