// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x71D390-0x71D540: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F5420
extern "C" const double DAT_007F5420;
// GLOBAL: GAMEMD 0x00B0ED58
extern "C" double DAT_00B0ED58;
// GLOBAL: GAMEMD 0x00B0ED7C
extern "C" short DAT_00B0ED7C;
// GLOBAL: GAMEMD 0x00B0ED7E
extern "C" short DAT_00B0ED7E;
// GLOBAL: GAMEMD 0x00B0ED80
extern "C" double DAT_00B0ED80;
// GLOBAL: GAMEMD 0x00B0ED88
extern "C" double DAT_00B0ED88;
// GLOBAL: GAMEMD 0x00B0ED90
extern "C" double DAT_00B0ED90;
// GLOBAL: GAMEMD 0x00B0ED98
extern "C" int DAT_00B0ED98;
// GLOBAL: GAMEMD 0x00B0ED9C
extern "C" int DAT_00B0ED9C;
// GLOBAL: GAMEMD 0x00B0EDA0
extern "C" int DAT_00B0EDA0;
// GLOBAL: GAMEMD 0x00B0EDA8
extern "C" double DAT_00B0EDA8;
// GLOBAL: GAMEMD 0x00B0EDB0
extern "C" double DAT_00B0EDB0;
// GLOBAL: GAMEMD 0x00B0F13C
extern "C" int DAT_00B0F13C;
// GLOBAL: GAMEMD 0x00B0F148
extern "C" int DAT_00B0F148;

// FUNCTION: GAMEMD 0x71D390
extern "C" void FUN_0071D390()
{
    DAT_00B0ED80 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x71D400
extern "C" void FUN_0071D400()
{
    DAT_00B0EDB0 = DAT_007E1720 * DAT_007F5420;
}

// FUNCTION: GAMEMD 0x71D420
extern "C" void FUN_0071D420()
{
    DAT_00B0ED88 = DAT_007E1728 * DAT_007F5420;
}

// FUNCTION: GAMEMD 0x71D440
extern "C" void FUN_0071D440()
{
    DAT_00B0ED58 = DAT_007E1730 * DAT_007F5420;
}

// FUNCTION: GAMEMD 0x71D460
extern "C" void FUN_0071D460()
{
    DAT_00B0F148 = (int)(FUN_004CAD50(DAT_00B0ED58 - DAT_00B0ED88) * DAT_007E1738 * DAT_00B0ED80);
}

// FUNCTION: GAMEMD 0x71D4A0
extern "C" void FUN_0071D4A0()
{
    DAT_00B0ED90 = FUN_004CADE0(DAT_00B0F148 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x71D4D0
extern "C" void FUN_0071D4D0()
{
    DAT_00B0EDA8 = FUN_004CADE0((DAT_00B0F148 * 2) / DAT_00B0ED80);
}

// FUNCTION: GAMEMD 0x71D500
extern "C" void FUN_0071D500()
{
    DAT_00B0F13C = (int)(DAT_00B0F148 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x71D530
extern "C" void FUN_0071D530()
{
    DAT_00B0ED7C = 0;
    DAT_00B0ED7E = 0;
}

// FUNCTION: GAMEMD 0x71D540
extern "C" void FUN_0071D540()
{
    DAT_00B0ED98 = 0;
    DAT_00B0ED9C = 0;
    DAT_00B0EDA0 = 0;
}
