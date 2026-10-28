// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x767910-0x767AC0: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F70D0
extern "C" const double DAT_007F70D0;
// GLOBAL: GAMEMD 0x00B72810
extern "C" double DAT_00B72810;
// GLOBAL: GAMEMD 0x00B72828
extern "C" short DAT_00B72828;
// GLOBAL: GAMEMD 0x00B7282A
extern "C" short DAT_00B7282A;
// GLOBAL: GAMEMD 0x00B72830
extern "C" double DAT_00B72830;
// GLOBAL: GAMEMD 0x00B72838
extern "C" double DAT_00B72838;
// GLOBAL: GAMEMD 0x00B72840
extern "C" double DAT_00B72840;
// GLOBAL: GAMEMD 0x00B72848
extern "C" int DAT_00B72848;
// GLOBAL: GAMEMD 0x00B7284C
extern "C" int DAT_00B7284C;
// GLOBAL: GAMEMD 0x00B72850
extern "C" int DAT_00B72850;
// GLOBAL: GAMEMD 0x00B72858
extern "C" double DAT_00B72858;
// GLOBAL: GAMEMD 0x00B72860
extern "C" double DAT_00B72860;
// GLOBAL: GAMEMD 0x00B7287C
extern "C" int DAT_00B7287C;
// GLOBAL: GAMEMD 0x00B72888
extern "C" int DAT_00B72888;

// FUNCTION: GAMEMD 0x767910
extern "C" void FUN_00767910()
{
    DAT_00B72830 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x767980
extern "C" void FUN_00767980()
{
    DAT_00B72860 = DAT_007E1720 * DAT_007F70D0;
}

// FUNCTION: GAMEMD 0x7679A0
extern "C" void FUN_007679A0()
{
    DAT_00B72838 = DAT_007E1728 * DAT_007F70D0;
}

// FUNCTION: GAMEMD 0x7679C0
extern "C" void FUN_007679C0()
{
    DAT_00B72810 = DAT_007E1730 * DAT_007F70D0;
}

// FUNCTION: GAMEMD 0x7679E0
extern "C" void FUN_007679E0()
{
    DAT_00B72888 = (int)(FUN_004CAD50(DAT_00B72810 - DAT_00B72838) * DAT_007E1738 * DAT_00B72830);
}

// FUNCTION: GAMEMD 0x767A20
extern "C" void FUN_00767A20()
{
    DAT_00B72840 = FUN_004CADE0(DAT_00B72888 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x767A50
extern "C" void FUN_00767A50()
{
    DAT_00B72858 = FUN_004CADE0((DAT_00B72888 * 2) / DAT_00B72830);
}

// FUNCTION: GAMEMD 0x767A80
extern "C" void FUN_00767A80()
{
    DAT_00B7287C = (int)(DAT_00B72888 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x767AB0
extern "C" void FUN_00767AB0()
{
    DAT_00B72828 = 0;
    DAT_00B7282A = 0;
}

// FUNCTION: GAMEMD 0x767AC0
extern "C" void FUN_00767AC0()
{
    DAT_00B72848 = 0;
    DAT_00B7284C = 0;
    DAT_00B72850 = 0;
}
