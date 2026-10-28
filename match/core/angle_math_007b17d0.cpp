// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x7B17D0-0x7B1980: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F79B0
extern "C" const double DAT_007F79B0;
// GLOBAL: GAMEMD 0x00B78020
extern "C" double DAT_00B78020;
// GLOBAL: GAMEMD 0x00B78038
extern "C" short DAT_00B78038;
// GLOBAL: GAMEMD 0x00B7803A
extern "C" short DAT_00B7803A;
// GLOBAL: GAMEMD 0x00B78040
extern "C" double DAT_00B78040;
// GLOBAL: GAMEMD 0x00B78048
extern "C" double DAT_00B78048;
// GLOBAL: GAMEMD 0x00B78050
extern "C" double DAT_00B78050;
// GLOBAL: GAMEMD 0x00B78058
extern "C" int DAT_00B78058;
// GLOBAL: GAMEMD 0x00B7805C
extern "C" int DAT_00B7805C;
// GLOBAL: GAMEMD 0x00B78060
extern "C" int DAT_00B78060;
// GLOBAL: GAMEMD 0x00B78068
extern "C" double DAT_00B78068;
// GLOBAL: GAMEMD 0x00B78070
extern "C" double DAT_00B78070;
// GLOBAL: GAMEMD 0x00B7808C
extern "C" int DAT_00B7808C;
// GLOBAL: GAMEMD 0x00B78098
extern "C" int DAT_00B78098;

// FUNCTION: GAMEMD 0x7B17D0
extern "C" void FUN_007B17D0()
{
    DAT_00B78040 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x7B1840
extern "C" void FUN_007B1840()
{
    DAT_00B78070 = DAT_007E1720 * DAT_007F79B0;
}

// FUNCTION: GAMEMD 0x7B1860
extern "C" void FUN_007B1860()
{
    DAT_00B78048 = DAT_007E1728 * DAT_007F79B0;
}

// FUNCTION: GAMEMD 0x7B1880
extern "C" void FUN_007B1880()
{
    DAT_00B78020 = DAT_007E1730 * DAT_007F79B0;
}

// FUNCTION: GAMEMD 0x7B18A0
extern "C" void FUN_007B18A0()
{
    DAT_00B78098 = (int)(FUN_004CAD50(DAT_00B78020 - DAT_00B78048) * DAT_007E1738 * DAT_00B78040);
}

// FUNCTION: GAMEMD 0x7B18E0
extern "C" void FUN_007B18E0()
{
    DAT_00B78050 = FUN_004CADE0(DAT_00B78098 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x7B1910
extern "C" void FUN_007B1910()
{
    DAT_00B78068 = FUN_004CADE0((DAT_00B78098 * 2) / DAT_00B78040);
}

// FUNCTION: GAMEMD 0x7B1940
extern "C" void FUN_007B1940()
{
    DAT_00B7808C = (int)(DAT_00B78098 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x7B1970
extern "C" void FUN_007B1970()
{
    DAT_00B78038 = 0;
    DAT_00B7803A = 0;
}

// FUNCTION: GAMEMD 0x7B1980
extern "C" void FUN_007B1980()
{
    DAT_00B78058 = 0;
    DAT_00B7805C = 0;
    DAT_00B78060 = 0;
}
