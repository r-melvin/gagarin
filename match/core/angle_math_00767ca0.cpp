// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x767CA0-0x767E50: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F70F8
extern "C" const double DAT_007F70F8;
// GLOBAL: GAMEMD 0x00B72890
extern "C" double DAT_00B72890;
// GLOBAL: GAMEMD 0x00B728A8
extern "C" short DAT_00B728A8;
// GLOBAL: GAMEMD 0x00B728AA
extern "C" short DAT_00B728AA;
// GLOBAL: GAMEMD 0x00B728B0
extern "C" double DAT_00B728B0;
// GLOBAL: GAMEMD 0x00B728B8
extern "C" double DAT_00B728B8;
// GLOBAL: GAMEMD 0x00B728C0
extern "C" double DAT_00B728C0;
// GLOBAL: GAMEMD 0x00B728C8
extern "C" int DAT_00B728C8;
// GLOBAL: GAMEMD 0x00B728CC
extern "C" int DAT_00B728CC;
// GLOBAL: GAMEMD 0x00B728D0
extern "C" int DAT_00B728D0;
// GLOBAL: GAMEMD 0x00B728D8
extern "C" double DAT_00B728D8;
// GLOBAL: GAMEMD 0x00B728E0
extern "C" double DAT_00B728E0;
// GLOBAL: GAMEMD 0x00B728FC
extern "C" int DAT_00B728FC;
// GLOBAL: GAMEMD 0x00B72908
extern "C" int DAT_00B72908;

// FUNCTION: GAMEMD 0x767CA0
extern "C" void FUN_00767CA0()
{
    DAT_00B728B0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x767D10
extern "C" void FUN_00767D10()
{
    DAT_00B728E0 = DAT_007E1720 * DAT_007F70F8;
}

// FUNCTION: GAMEMD 0x767D30
extern "C" void FUN_00767D30()
{
    DAT_00B728B8 = DAT_007E1728 * DAT_007F70F8;
}

// FUNCTION: GAMEMD 0x767D50
extern "C" void FUN_00767D50()
{
    DAT_00B72890 = DAT_007E1730 * DAT_007F70F8;
}

// FUNCTION: GAMEMD 0x767D70
extern "C" void FUN_00767D70()
{
    DAT_00B72908 = (int)(FUN_004CAD50(DAT_00B72890 - DAT_00B728B8) * DAT_007E1738 * DAT_00B728B0);
}

// FUNCTION: GAMEMD 0x767DB0
extern "C" void FUN_00767DB0()
{
    DAT_00B728C0 = FUN_004CADE0(DAT_00B72908 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x767DE0
extern "C" void FUN_00767DE0()
{
    DAT_00B728D8 = FUN_004CADE0((DAT_00B72908 * 2) / DAT_00B728B0);
}

// FUNCTION: GAMEMD 0x767E10
extern "C" void FUN_00767E10()
{
    DAT_00B728FC = (int)(DAT_00B72908 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x767E40
extern "C" void FUN_00767E40()
{
    DAT_00B728A8 = 0;
    DAT_00B728AA = 0;
}

// FUNCTION: GAMEMD 0x767E50
extern "C" void FUN_00767E50()
{
    DAT_00B728C8 = 0;
    DAT_00B728CC = 0;
    DAT_00B728D0 = 0;
}
