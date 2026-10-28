// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x75A8A0-0x75AA50: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F69C8
extern "C" const double DAT_007F69C8;
// GLOBAL: GAMEMD 0x00B45BB0
extern "C" double DAT_00B45BB0;
// GLOBAL: GAMEMD 0x00B45BC8
extern "C" short DAT_00B45BC8;
// GLOBAL: GAMEMD 0x00B45BCA
extern "C" short DAT_00B45BCA;
// GLOBAL: GAMEMD 0x00B45BD0
extern "C" double DAT_00B45BD0;
// GLOBAL: GAMEMD 0x00B45BD8
extern "C" double DAT_00B45BD8;
// GLOBAL: GAMEMD 0x00B45BE0
extern "C" double DAT_00B45BE0;
// GLOBAL: GAMEMD 0x00B45BE8
extern "C" int DAT_00B45BE8;
// GLOBAL: GAMEMD 0x00B45BEC
extern "C" int DAT_00B45BEC;
// GLOBAL: GAMEMD 0x00B45BF0
extern "C" int DAT_00B45BF0;
// GLOBAL: GAMEMD 0x00B45BF8
extern "C" double DAT_00B45BF8;
// GLOBAL: GAMEMD 0x00B45C00
extern "C" double DAT_00B45C00;
// GLOBAL: GAMEMD 0x00B45C1C
extern "C" int DAT_00B45C1C;
// GLOBAL: GAMEMD 0x00B45C28
extern "C" int DAT_00B45C28;

// FUNCTION: GAMEMD 0x75A8A0
extern "C" void FUN_0075A8A0()
{
    DAT_00B45BD0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x75A910
extern "C" void FUN_0075A910()
{
    DAT_00B45C00 = DAT_007E1720 * DAT_007F69C8;
}

// FUNCTION: GAMEMD 0x75A930
extern "C" void FUN_0075A930()
{
    DAT_00B45BD8 = DAT_007E1728 * DAT_007F69C8;
}

// FUNCTION: GAMEMD 0x75A950
extern "C" void FUN_0075A950()
{
    DAT_00B45BB0 = DAT_007E1730 * DAT_007F69C8;
}

// FUNCTION: GAMEMD 0x75A970
extern "C" void FUN_0075A970()
{
    DAT_00B45C28 = (int)(FUN_004CAD50(DAT_00B45BB0 - DAT_00B45BD8) * DAT_007E1738 * DAT_00B45BD0);
}

// FUNCTION: GAMEMD 0x75A9B0
extern "C" void FUN_0075A9B0()
{
    DAT_00B45BE0 = FUN_004CADE0(DAT_00B45C28 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x75A9E0
extern "C" void FUN_0075A9E0()
{
    DAT_00B45BF8 = FUN_004CADE0((DAT_00B45C28 * 2) / DAT_00B45BD0);
}

// FUNCTION: GAMEMD 0x75AA10
extern "C" void FUN_0075AA10()
{
    DAT_00B45C1C = (int)(DAT_00B45C28 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x75AA40
extern "C" void FUN_0075AA40()
{
    DAT_00B45BC8 = 0;
    DAT_00B45BCA = 0;
}

// FUNCTION: GAMEMD 0x75AA50
extern "C" void FUN_0075AA50()
{
    DAT_00B45BE8 = 0;
    DAT_00B45BEC = 0;
    DAT_00B45BF0 = 0;
}
