// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu050_methods.h"

// FUNCTION: GAMEMD 0x483610
// Returns a computed value.
int Obj_00483610::FUN_00483610() const
{
    return (unknown_140 >> 8) & 1;
}

// FUNCTION: GAMEMD 0x484A80
// Updates one member in place.
void __stdcall FUN_00484A80(Arg1_00484A80* a1)
{
    a1->unknown_194++;
}

// FUNCTION: GAMEMD 0x484A90
// Branching.
void __stdcall FUN_00484A90(Arg1_00484A90* a1)
{
    if (DAT_00A8E9A0 != 0)
    {
        a1->unknown_194--;
    }
}

// FUNCTION: GAMEMD 0x486380
// Branching.
bool Obj_00486380::FUN_00486380()
{
    if (unknown_38 == 0xFFFF || unknown_38 == 0)
    {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4865B0
// Branching.
bool Obj_004865B0::FUN_004865B0()
{
    if (unknown_38 < DAT_00ABAD28 || unknown_38 >= DAT_00ABAD28 + 0x2A)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x486650
// Branching.
bool Obj_00486650::FUN_00486650()
{
    if (unknown_38 < DAT_00AA10A4 || unknown_38 >= DAT_00AA10A4 + 0xE)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x486670
// Branching.
bool Obj_00486670::FUN_00486670()
{
    if (unknown_38 < DAT_00ABC2B0 || unknown_38 >= DAT_00ABC2B0 + 0x10)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x4866D0
// Branching.
bool Obj_004866D0::FUN_004866D0()
{
    if (unknown_38 < DAT_00ABBEC8 || unknown_38 >= DAT_00ABBEC8 + 0xF)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x4866F0
// Branching.
bool Obj_004866F0::FUN_004866F0()
{
    if (unknown_38 < DAT_00ABBEC4 || unknown_38 >= DAT_00ABBEC4 + 4)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x486710
// Branching.
bool Obj_00486710::FUN_00486710()
{
    if (unknown_38 < DAT_00AA1094 || unknown_38 >= DAT_00AA1094 + 4)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x486730
// Branching.
bool Obj_00486730::FUN_00486730()
{
    if (unknown_38 < DAT_00AA0E20 || unknown_38 >= DAT_00AA0E20 + 0xE)
    {
        return false;
    }
    return true;
}

// FUNCTION: GAMEMD 0x486900
// Branching.
unsigned char Obj_00486900::FUN_00486900()
{
    if (unknown_38 == DAT_00ABC2C8)
    {
        return 1;
    }
    return (unknown_38 == (DAT_00ABC2C8 + 1)) ? true : false;
}

// FUNCTION: GAMEMD 0x487E60
// Returns a constant. Vtable slot 11 of CellClass (RTTI).
int Obj_00487E60::FUN_00487E60() const
{
    return 0xB;
}

// FUNCTION: GAMEMD 0x487E70
// Returns a constant. Vtable slot 12 of CellClass (RTTI).
int Obj_00487E70::FUN_00487E70() const
{
    return 0x148;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xAA0E20
int DAT_00AA0E20;
// GLOBAL: GAMEMD 0xAA1094
int DAT_00AA1094;
// GLOBAL: GAMEMD 0xAA10A4
int DAT_00AA10A4;
// GLOBAL: GAMEMD 0xABBEC4
int DAT_00ABBEC4;
// GLOBAL: GAMEMD 0xABBEC8
int DAT_00ABBEC8;
// GLOBAL: GAMEMD 0xABC2B0
int DAT_00ABC2B0;
// GLOBAL: GAMEMD 0xABC2C8
int DAT_00ABC2C8;
// END defined globals
