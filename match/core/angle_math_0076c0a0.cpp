// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x76C0A0-0x76C250: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F72A8
extern "C" const double DAT_007F72A8;
// GLOBAL: GAMEMD 0x00B72A10
extern "C" double DAT_00B72A10;
// GLOBAL: GAMEMD 0x00B72A28
extern "C" short DAT_00B72A28;
// GLOBAL: GAMEMD 0x00B72A2A
extern "C" short DAT_00B72A2A;
// GLOBAL: GAMEMD 0x00B72A30
extern "C" double DAT_00B72A30;
// GLOBAL: GAMEMD 0x00B72A38
extern "C" double DAT_00B72A38;
// GLOBAL: GAMEMD 0x00B72A40
extern "C" double DAT_00B72A40;
// GLOBAL: GAMEMD 0x00B72A48
extern "C" int DAT_00B72A48;
// GLOBAL: GAMEMD 0x00B72A4C
extern "C" int DAT_00B72A4C;
// GLOBAL: GAMEMD 0x00B72A50
extern "C" int DAT_00B72A50;
// GLOBAL: GAMEMD 0x00B72A58
extern "C" double DAT_00B72A58;
// GLOBAL: GAMEMD 0x00B72A60
extern "C" double DAT_00B72A60;
// GLOBAL: GAMEMD 0x00B72A7C
extern "C" int DAT_00B72A7C;
// GLOBAL: GAMEMD 0x00B72A88
extern "C" int DAT_00B72A88;

// FUNCTION: GAMEMD 0x76C0A0
extern "C" void FUN_0076C0A0()
{
    DAT_00B72A30 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x76C110
extern "C" void FUN_0076C110()
{
    DAT_00B72A60 = DAT_007E1720 * DAT_007F72A8;
}

// FUNCTION: GAMEMD 0x76C130
extern "C" void FUN_0076C130()
{
    DAT_00B72A38 = DAT_007E1728 * DAT_007F72A8;
}

// FUNCTION: GAMEMD 0x76C150
extern "C" void FUN_0076C150()
{
    DAT_00B72A10 = DAT_007E1730 * DAT_007F72A8;
}

// FUNCTION: GAMEMD 0x76C170
extern "C" void FUN_0076C170()
{
    DAT_00B72A88 = (int)(FUN_004CAD50(DAT_00B72A10 - DAT_00B72A38) * DAT_007E1738 * DAT_00B72A30);
}

// FUNCTION: GAMEMD 0x76C1B0
extern "C" void FUN_0076C1B0()
{
    DAT_00B72A40 = FUN_004CADE0(DAT_00B72A88 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x76C1E0
extern "C" void FUN_0076C1E0()
{
    DAT_00B72A58 = FUN_004CADE0((DAT_00B72A88 * 2) / DAT_00B72A30);
}

// FUNCTION: GAMEMD 0x76C210
extern "C" void FUN_0076C210()
{
    DAT_00B72A7C = (int)(DAT_00B72A88 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x76C240
extern "C" void FUN_0076C240()
{
    DAT_00B72A28 = 0;
    DAT_00B72A2A = 0;
}

// FUNCTION: GAMEMD 0x76C250
extern "C" void FUN_0076C250()
{
    DAT_00B72A48 = 0;
    DAT_00B72A4C = 0;
    DAT_00B72A50 = 0;
}
