// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x6F28A0-0x6F2A50: the second copy of the angle-table setup (same
// shapes as 0x6F0470-0x6F0660 in angle_math_006f0470.cpp), read instruction by instruction from
// gamemd.exe v1.001.
//   0x6F28A0 0x6F2910 0x6F2930 0x6F2950 0x6F2970 0x6F29B0 0x6F29E0 0x6F2A10 0x6F2A40 0x6F2A50
#include <math.h>
#pragma intrinsic(pow)

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- square-root helper.
extern double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- table helper.
extern double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- table helper.
extern double __cdecl FUN_004CADE0(double value);

// GLOBAL: GAMEMD 0x007E1708 -- constant 2.0.
extern "C" const double DAT_007E1708;
// GLOBAL: GAMEMD 0x007E1710 -- constant 256.0.
extern "C" const double DAT_007E1710;
// GLOBAL: GAMEMD 0x007E1720 -- constant 45.0.
extern "C" const double DAT_007E1720;
// GLOBAL: GAMEMD 0x007E1728 -- constant 60.0.
extern "C" const double DAT_007E1728;
// GLOBAL: GAMEMD 0x007E1730 -- constant 90.0.
extern "C" const double DAT_007E1730;
// GLOBAL: GAMEMD 0x007E1738
extern "C" const double DAT_007E1738;
// GLOBAL: GAMEMD 0x007E1740
extern "C" const double DAT_007E1740;
// GLOBAL: GAMEMD 0x007F4888 -- radians per degree.
extern "C" const double DAT_007F4888;

// GLOBAL: GAMEMD 0x00B0EA58
extern "C" double DAT_00B0EA58;
// GLOBAL: GAMEMD 0x00B0EB08
extern "C" double DAT_00B0EB08;
// GLOBAL: GAMEMD 0x00B0EA60
extern "C" double DAT_00B0EA60;
// GLOBAL: GAMEMD 0x00B0EA30
extern "C" double DAT_00B0EA30;
// GLOBAL: GAMEMD 0x00B0EB34
extern "C" int DAT_00B0EB34;
// GLOBAL: GAMEMD 0x00B0EA68
extern "C" double DAT_00B0EA68;
// GLOBAL: GAMEMD 0x00B0EAA0
extern "C" double DAT_00B0EAA0;
// GLOBAL: GAMEMD 0x00B0EB24
extern "C" int DAT_00B0EB24;
// GLOBAL: GAMEMD 0x00B0EA50
extern "C" short DAT_00B0EA50;
// GLOBAL: GAMEMD 0x00B0EA52
extern "C" short DAT_00B0EA52;
// GLOBAL: GAMEMD 0x00B0EA90
extern "C" int DAT_00B0EA90;
// GLOBAL: GAMEMD 0x00B0EA94
extern "C" int DAT_00B0EA94;
// GLOBAL: GAMEMD 0x00B0EA98
extern "C" int DAT_00B0EA98;

// FUNCTION: GAMEMD 0x6F28A0
extern "C" void FUN_006F28A0()
{
    DAT_00B0EA58 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x6F2910
extern "C" void FUN_006F2910()
{
    DAT_00B0EB08 = DAT_007E1720 * DAT_007F4888;
}

// FUNCTION: GAMEMD 0x6F2930
extern "C" void FUN_006F2930()
{
    DAT_00B0EA60 = DAT_007E1728 * DAT_007F4888;
}

// FUNCTION: GAMEMD 0x6F2950
extern "C" void FUN_006F2950()
{
    DAT_00B0EA30 = DAT_007E1730 * DAT_007F4888;
}

// FUNCTION: GAMEMD 0x6F2970
extern "C" void FUN_006F2970()
{
    DAT_00B0EB34 = (int)(FUN_004CAD50(DAT_00B0EA30 - DAT_00B0EA60) * DAT_007E1738 * DAT_00B0EA58);
}

// FUNCTION: GAMEMD 0x6F29B0
extern "C" void FUN_006F29B0()
{
    DAT_00B0EA68 = FUN_004CADE0(DAT_00B0EB34 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x6F29E0
extern "C" void FUN_006F29E0()
{
    DAT_00B0EAA0 = FUN_004CADE0((DAT_00B0EB34 * 2) / DAT_00B0EA58);
}

// FUNCTION: GAMEMD 0x6F2A10
extern "C" void FUN_006F2A10()
{
    DAT_00B0EB24 = (int)(DAT_00B0EB34 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x6F2A40
extern "C" void FUN_006F2A40()
{
    DAT_00B0EA50 = 0;
    DAT_00B0EA52 = 0;
}

// FUNCTION: GAMEMD 0x6F2A50
extern "C" void FUN_006F2A50()
{
    DAT_00B0EA90 = 0;
    DAT_00B0EA94 = 0;
    DAT_00B0EA98 = 0;
}
