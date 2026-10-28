// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x730780-0x730930: a further copy of the angle-table setup (same shapes as
// 0x6F0470-0x6F0660 in angle_math_006f0470.cpp), read instruction by instruction from gamemd.exe v1.001.
#include <math.h>
#pragma intrinsic(pow)

// FUNCTION: GAMEMD 0x004CAC40 (decl; reloc)
extern double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x004CAD50 (decl; reloc)
extern double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x004CADE0 (decl; reloc)
extern double __cdecl FUN_004CADE0(double value);

// GLOBAL: GAMEMD 0x007E1708
extern "C" const double DAT_007E1708;
// GLOBAL: GAMEMD 0x007E1710
extern "C" const double DAT_007E1710;
// GLOBAL: GAMEMD 0x007E1720
extern "C" const double DAT_007E1720;
// GLOBAL: GAMEMD 0x007E1728
extern "C" const double DAT_007E1728;
// GLOBAL: GAMEMD 0x007E1730
extern "C" const double DAT_007E1730;
// GLOBAL: GAMEMD 0x007E1738
extern "C" const double DAT_007E1738;
// GLOBAL: GAMEMD 0x007E1740
extern "C" const double DAT_007E1740;
// GLOBAL: GAMEMD 0x007F5C10
extern "C" const double DAT_007F5C10;
// GLOBAL: GAMEMD 0x00B0FDD8
extern "C" double DAT_00B0FDD8;
// GLOBAL: GAMEMD 0x00B0FDF0
extern "C" short DAT_00B0FDF0;
// GLOBAL: GAMEMD 0x00B0FDF2
extern "C" short DAT_00B0FDF2;
// GLOBAL: GAMEMD 0x00B0FDF8
extern "C" double DAT_00B0FDF8;
// GLOBAL: GAMEMD 0x00B0FE00
extern "C" double DAT_00B0FE00;
// GLOBAL: GAMEMD 0x00B0FE08
extern "C" double DAT_00B0FE08;
// GLOBAL: GAMEMD 0x00B0FE10
extern "C" int DAT_00B0FE10;
// GLOBAL: GAMEMD 0x00B0FE14
extern "C" int DAT_00B0FE14;
// GLOBAL: GAMEMD 0x00B0FE18
extern "C" int DAT_00B0FE18;
// GLOBAL: GAMEMD 0x00B0FE20
extern "C" double DAT_00B0FE20;
// GLOBAL: GAMEMD 0x00B0FE28
extern "C" double DAT_00B0FE28;
// GLOBAL: GAMEMD 0x00B0FE44
extern "C" int DAT_00B0FE44;
// GLOBAL: GAMEMD 0x00B0FE50
extern "C" int DAT_00B0FE50;

// FUNCTION: GAMEMD 0x730780
extern "C" void FUN_00730780()
{
    DAT_00B0FDF8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x7307F0
extern "C" void FUN_007307F0()
{
    DAT_00B0FE28 = DAT_007E1720 * DAT_007F5C10;
}

// FUNCTION: GAMEMD 0x730810
extern "C" void FUN_00730810()
{
    DAT_00B0FE00 = DAT_007E1728 * DAT_007F5C10;
}

// FUNCTION: GAMEMD 0x730830
extern "C" void FUN_00730830()
{
    DAT_00B0FDD8 = DAT_007E1730 * DAT_007F5C10;
}

// FUNCTION: GAMEMD 0x730850
extern "C" void FUN_00730850()
{
    DAT_00B0FE50 = (int)(FUN_004CAD50(DAT_00B0FDD8 - DAT_00B0FE00) * DAT_007E1738 * DAT_00B0FDF8);
}

// FUNCTION: GAMEMD 0x730890
extern "C" void FUN_00730890()
{
    DAT_00B0FE08 = FUN_004CADE0(DAT_00B0FE50 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x7308C0
extern "C" void FUN_007308C0()
{
    DAT_00B0FE20 = FUN_004CADE0((DAT_00B0FE50 * 2) / DAT_00B0FDF8);
}

// FUNCTION: GAMEMD 0x7308F0
extern "C" void FUN_007308F0()
{
    DAT_00B0FE44 = (int)(DAT_00B0FE50 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x730920
extern "C" void FUN_00730920()
{
    DAT_00B0FDF0 = 0;
    DAT_00B0FDF2 = 0;
}

// FUNCTION: GAMEMD 0x730930
extern "C" void FUN_00730930()
{
    DAT_00B0FE10 = 0;
    DAT_00B0FE14 = 0;
    DAT_00B0FE18 = 0;
}
