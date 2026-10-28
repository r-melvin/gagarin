// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x7784F0-0x7786A0: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F74E8
extern "C" const double DAT_007F74E8;
// GLOBAL: GAMEMD 0x00B73578
extern "C" double DAT_00B73578;
// GLOBAL: GAMEMD 0x00B73594
extern "C" short DAT_00B73594;
// GLOBAL: GAMEMD 0x00B73596
extern "C" short DAT_00B73596;
// GLOBAL: GAMEMD 0x00B73598
extern "C" double DAT_00B73598;
// GLOBAL: GAMEMD 0x00B735A0
extern "C" double DAT_00B735A0;
// GLOBAL: GAMEMD 0x00B735A8
extern "C" double DAT_00B735A8;
// GLOBAL: GAMEMD 0x00B735B0
extern "C" int DAT_00B735B0;
// GLOBAL: GAMEMD 0x00B735B4
extern "C" int DAT_00B735B4;
// GLOBAL: GAMEMD 0x00B735B8
extern "C" int DAT_00B735B8;
// GLOBAL: GAMEMD 0x00B735C0
extern "C" double DAT_00B735C0;
// GLOBAL: GAMEMD 0x00B735C8
extern "C" double DAT_00B735C8;
// GLOBAL: GAMEMD 0x00B735E4
extern "C" int DAT_00B735E4;
// GLOBAL: GAMEMD 0x00B735F0
extern "C" int DAT_00B735F0;

// FUNCTION: GAMEMD 0x7784F0
extern "C" void FUN_007784F0()
{
    DAT_00B73598 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x778560
extern "C" void FUN_00778560()
{
    DAT_00B735C8 = DAT_007E1720 * DAT_007F74E8;
}

// FUNCTION: GAMEMD 0x778580
extern "C" void FUN_00778580()
{
    DAT_00B735A0 = DAT_007E1728 * DAT_007F74E8;
}

// FUNCTION: GAMEMD 0x7785A0
extern "C" void FUN_007785A0()
{
    DAT_00B73578 = DAT_007E1730 * DAT_007F74E8;
}

// FUNCTION: GAMEMD 0x7785C0
extern "C" void FUN_007785C0()
{
    DAT_00B735F0 = (int)(FUN_004CAD50(DAT_00B73578 - DAT_00B735A0) * DAT_007E1738 * DAT_00B73598);
}

// FUNCTION: GAMEMD 0x778600
extern "C" void FUN_00778600()
{
    DAT_00B735A8 = FUN_004CADE0(DAT_00B735F0 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x778630
extern "C" void FUN_00778630()
{
    DAT_00B735C0 = FUN_004CADE0((DAT_00B735F0 * 2) / DAT_00B73598);
}

// FUNCTION: GAMEMD 0x778660
extern "C" void FUN_00778660()
{
    DAT_00B735E4 = (int)(DAT_00B735F0 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x778690
extern "C" void FUN_00778690()
{
    DAT_00B73594 = 0;
    DAT_00B73596 = 0;
}

// FUNCTION: GAMEMD 0x7786A0
extern "C" void FUN_007786A0()
{
    DAT_00B735B0 = 0;
    DAT_00B735B4 = 0;
    DAT_00B735B8 = 0;
}
