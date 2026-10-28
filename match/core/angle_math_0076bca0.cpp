// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x76BCA0-0x76BE50: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F7288
extern "C" const double DAT_007F7288;
// GLOBAL: GAMEMD 0x00B72990
extern "C" double DAT_00B72990;
// GLOBAL: GAMEMD 0x00B729A8
extern "C" short DAT_00B729A8;
// GLOBAL: GAMEMD 0x00B729AA
extern "C" short DAT_00B729AA;
// GLOBAL: GAMEMD 0x00B729B0
extern "C" double DAT_00B729B0;
// GLOBAL: GAMEMD 0x00B729B8
extern "C" double DAT_00B729B8;
// GLOBAL: GAMEMD 0x00B729C0
extern "C" double DAT_00B729C0;
// GLOBAL: GAMEMD 0x00B729C8
extern "C" int DAT_00B729C8;
// GLOBAL: GAMEMD 0x00B729CC
extern "C" int DAT_00B729CC;
// GLOBAL: GAMEMD 0x00B729D0
extern "C" int DAT_00B729D0;
// GLOBAL: GAMEMD 0x00B729D8
extern "C" double DAT_00B729D8;
// GLOBAL: GAMEMD 0x00B729E0
extern "C" double DAT_00B729E0;
// GLOBAL: GAMEMD 0x00B729FC
extern "C" int DAT_00B729FC;
// GLOBAL: GAMEMD 0x00B72A08
extern "C" int DAT_00B72A08;

// FUNCTION: GAMEMD 0x76BCA0
extern "C" void FUN_0076BCA0()
{
    DAT_00B729B0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x76BD10
extern "C" void FUN_0076BD10()
{
    DAT_00B729E0 = DAT_007E1720 * DAT_007F7288;
}

// FUNCTION: GAMEMD 0x76BD30
extern "C" void FUN_0076BD30()
{
    DAT_00B729B8 = DAT_007E1728 * DAT_007F7288;
}

// FUNCTION: GAMEMD 0x76BD50
extern "C" void FUN_0076BD50()
{
    DAT_00B72990 = DAT_007E1730 * DAT_007F7288;
}

// FUNCTION: GAMEMD 0x76BD70
extern "C" void FUN_0076BD70()
{
    DAT_00B72A08 = (int)(FUN_004CAD50(DAT_00B72990 - DAT_00B729B8) * DAT_007E1738 * DAT_00B729B0);
}

// FUNCTION: GAMEMD 0x76BDB0
extern "C" void FUN_0076BDB0()
{
    DAT_00B729C0 = FUN_004CADE0(DAT_00B72A08 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x76BDE0
extern "C" void FUN_0076BDE0()
{
    DAT_00B729D8 = FUN_004CADE0((DAT_00B72A08 * 2) / DAT_00B729B0);
}

// FUNCTION: GAMEMD 0x76BE10
extern "C" void FUN_0076BE10()
{
    DAT_00B729FC = (int)(DAT_00B72A08 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x76BE40
extern "C" void FUN_0076BE40()
{
    DAT_00B729A8 = 0;
    DAT_00B729AA = 0;
}

// FUNCTION: GAMEMD 0x76BE50
extern "C" void FUN_0076BE50()
{
    DAT_00B729C8 = 0;
    DAT_00B729CC = 0;
    DAT_00B729D0 = 0;
}
