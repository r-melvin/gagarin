// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x71B5A0-0x71B750: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F51E8
extern "C" const double DAT_007F51E8;
// GLOBAL: GAMEMD 0x00B0ECD8
extern "C" double DAT_00B0ECD8;
// GLOBAL: GAMEMD 0x00B0ECF0
extern "C" short DAT_00B0ECF0;
// GLOBAL: GAMEMD 0x00B0ECF2
extern "C" short DAT_00B0ECF2;
// GLOBAL: GAMEMD 0x00B0ECF8
extern "C" double DAT_00B0ECF8;
// GLOBAL: GAMEMD 0x00B0ED00
extern "C" double DAT_00B0ED00;
// GLOBAL: GAMEMD 0x00B0ED08
extern "C" double DAT_00B0ED08;
// GLOBAL: GAMEMD 0x00B0ED10
extern "C" int DAT_00B0ED10;
// GLOBAL: GAMEMD 0x00B0ED14
extern "C" int DAT_00B0ED14;
// GLOBAL: GAMEMD 0x00B0ED18
extern "C" int DAT_00B0ED18;
// GLOBAL: GAMEMD 0x00B0ED20
extern "C" double DAT_00B0ED20;
// GLOBAL: GAMEMD 0x00B0ED28
extern "C" double DAT_00B0ED28;
// GLOBAL: GAMEMD 0x00B0ED44
extern "C" int DAT_00B0ED44;
// GLOBAL: GAMEMD 0x00B0ED50
extern "C" int DAT_00B0ED50;

// FUNCTION: GAMEMD 0x71B5A0
extern "C" void FUN_0071B5A0()
{
    DAT_00B0ECF8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x71B610
extern "C" void FUN_0071B610()
{
    DAT_00B0ED28 = DAT_007E1720 * DAT_007F51E8;
}

// FUNCTION: GAMEMD 0x71B630
extern "C" void FUN_0071B630()
{
    DAT_00B0ED00 = DAT_007E1728 * DAT_007F51E8;
}

// FUNCTION: GAMEMD 0x71B650
extern "C" void FUN_0071B650()
{
    DAT_00B0ECD8 = DAT_007E1730 * DAT_007F51E8;
}

// FUNCTION: GAMEMD 0x71B670
extern "C" void FUN_0071B670()
{
    DAT_00B0ED50 = (int)(FUN_004CAD50(DAT_00B0ECD8 - DAT_00B0ED00) * DAT_007E1738 * DAT_00B0ECF8);
}

// FUNCTION: GAMEMD 0x71B6B0
extern "C" void FUN_0071B6B0()
{
    DAT_00B0ED08 = FUN_004CADE0(DAT_00B0ED50 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x71B6E0
extern "C" void FUN_0071B6E0()
{
    DAT_00B0ED20 = FUN_004CADE0((DAT_00B0ED50 * 2) / DAT_00B0ECF8);
}

// FUNCTION: GAMEMD 0x71B710
extern "C" void FUN_0071B710()
{
    DAT_00B0ED44 = (int)(DAT_00B0ED50 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x71B740
extern "C" void FUN_0071B740()
{
    DAT_00B0ECF0 = 0;
    DAT_00B0ECF2 = 0;
}

// FUNCTION: GAMEMD 0x71B750
extern "C" void FUN_0071B750()
{
    DAT_00B0ED10 = 0;
    DAT_00B0ED14 = 0;
    DAT_00B0ED18 = 0;
}
