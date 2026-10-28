// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x723A90-0x723C40: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F57A0
extern "C" const double DAT_007F57A0;
// GLOBAL: GAMEMD 0x00B0F518
extern "C" double DAT_00B0F518;
// GLOBAL: GAMEMD 0x00B0F530
extern "C" short DAT_00B0F530;
// GLOBAL: GAMEMD 0x00B0F532
extern "C" short DAT_00B0F532;
// GLOBAL: GAMEMD 0x00B0F538
extern "C" double DAT_00B0F538;
// GLOBAL: GAMEMD 0x00B0F540
extern "C" double DAT_00B0F540;
// GLOBAL: GAMEMD 0x00B0F548
extern "C" double DAT_00B0F548;
// GLOBAL: GAMEMD 0x00B0F550
extern "C" int DAT_00B0F550;
// GLOBAL: GAMEMD 0x00B0F554
extern "C" int DAT_00B0F554;
// GLOBAL: GAMEMD 0x00B0F558
extern "C" int DAT_00B0F558;
// GLOBAL: GAMEMD 0x00B0F560
extern "C" double DAT_00B0F560;
// GLOBAL: GAMEMD 0x00B0F568
extern "C" double DAT_00B0F568;
// GLOBAL: GAMEMD 0x00B0F584
extern "C" int DAT_00B0F584;
// GLOBAL: GAMEMD 0x00B0F590
extern "C" int DAT_00B0F590;

// FUNCTION: GAMEMD 0x723A90
extern "C" void FUN_00723A90()
{
    DAT_00B0F538 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x723B00
extern "C" void FUN_00723B00()
{
    DAT_00B0F568 = DAT_007E1720 * DAT_007F57A0;
}

// FUNCTION: GAMEMD 0x723B20
extern "C" void FUN_00723B20()
{
    DAT_00B0F540 = DAT_007E1728 * DAT_007F57A0;
}

// FUNCTION: GAMEMD 0x723B40
extern "C" void FUN_00723B40()
{
    DAT_00B0F518 = DAT_007E1730 * DAT_007F57A0;
}

// FUNCTION: GAMEMD 0x723B60
extern "C" void FUN_00723B60()
{
    DAT_00B0F590 = (int)(FUN_004CAD50(DAT_00B0F518 - DAT_00B0F540) * DAT_007E1738 * DAT_00B0F538);
}

// FUNCTION: GAMEMD 0x723BA0
extern "C" void FUN_00723BA0()
{
    DAT_00B0F548 = FUN_004CADE0(DAT_00B0F590 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x723BD0
extern "C" void FUN_00723BD0()
{
    DAT_00B0F560 = FUN_004CADE0((DAT_00B0F590 * 2) / DAT_00B0F538);
}

// FUNCTION: GAMEMD 0x723C00
extern "C" void FUN_00723C00()
{
    DAT_00B0F584 = (int)(DAT_00B0F590 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x723C30
extern "C" void FUN_00723C30()
{
    DAT_00B0F530 = 0;
    DAT_00B0F532 = 0;
}

// FUNCTION: GAMEMD 0x723C40
extern "C" void FUN_00723C40()
{
    DAT_00B0F550 = 0;
    DAT_00B0F554 = 0;
    DAT_00B0F558 = 0;
}
