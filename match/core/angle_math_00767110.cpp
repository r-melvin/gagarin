// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x767110-0x7672C0: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F7080
extern "C" const double DAT_007F7080;
// GLOBAL: GAMEMD 0x00B72790
extern "C" double DAT_00B72790;
// GLOBAL: GAMEMD 0x00B727A8
extern "C" short DAT_00B727A8;
// GLOBAL: GAMEMD 0x00B727AA
extern "C" short DAT_00B727AA;
// GLOBAL: GAMEMD 0x00B727B0
extern "C" double DAT_00B727B0;
// GLOBAL: GAMEMD 0x00B727B8
extern "C" double DAT_00B727B8;
// GLOBAL: GAMEMD 0x00B727C0
extern "C" double DAT_00B727C0;
// GLOBAL: GAMEMD 0x00B727C8
extern "C" int DAT_00B727C8;
// GLOBAL: GAMEMD 0x00B727CC
extern "C" int DAT_00B727CC;
// GLOBAL: GAMEMD 0x00B727D0
extern "C" int DAT_00B727D0;
// GLOBAL: GAMEMD 0x00B727D8
extern "C" double DAT_00B727D8;
// GLOBAL: GAMEMD 0x00B727E0
extern "C" double DAT_00B727E0;
// GLOBAL: GAMEMD 0x00B727FC
extern "C" int DAT_00B727FC;
// GLOBAL: GAMEMD 0x00B72808
extern "C" int DAT_00B72808;

// FUNCTION: GAMEMD 0x767110
extern "C" void FUN_00767110()
{
    DAT_00B727B0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x767180
extern "C" void FUN_00767180()
{
    DAT_00B727E0 = DAT_007E1720 * DAT_007F7080;
}

// FUNCTION: GAMEMD 0x7671A0
extern "C" void FUN_007671A0()
{
    DAT_00B727B8 = DAT_007E1728 * DAT_007F7080;
}

// FUNCTION: GAMEMD 0x7671C0
extern "C" void FUN_007671C0()
{
    DAT_00B72790 = DAT_007E1730 * DAT_007F7080;
}

// FUNCTION: GAMEMD 0x7671E0
extern "C" void FUN_007671E0()
{
    DAT_00B72808 = (int)(FUN_004CAD50(DAT_00B72790 - DAT_00B727B8) * DAT_007E1738 * DAT_00B727B0);
}

// FUNCTION: GAMEMD 0x767220
extern "C" void FUN_00767220()
{
    DAT_00B727C0 = FUN_004CADE0(DAT_00B72808 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x767250
extern "C" void FUN_00767250()
{
    DAT_00B727D8 = FUN_004CADE0((DAT_00B72808 * 2) / DAT_00B727B0);
}

// FUNCTION: GAMEMD 0x767280
extern "C" void FUN_00767280()
{
    DAT_00B727FC = (int)(DAT_00B72808 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x7672B0
extern "C" void FUN_007672B0()
{
    DAT_00B727A8 = 0;
    DAT_00B727AA = 0;
}

// FUNCTION: GAMEMD 0x7672C0
extern "C" void FUN_007672C0()
{
    DAT_00B727C8 = 0;
    DAT_00B727CC = 0;
    DAT_00B727D0 = 0;
}
