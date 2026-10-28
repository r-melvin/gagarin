// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x76F720-0x76F8D0: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F7328
extern "C" const double DAT_007F7328;
// GLOBAL: GAMEMD 0x00B72B10
extern "C" double DAT_00B72B10;
// GLOBAL: GAMEMD 0x00B72B28
extern "C" short DAT_00B72B28;
// GLOBAL: GAMEMD 0x00B72B2A
extern "C" short DAT_00B72B2A;
// GLOBAL: GAMEMD 0x00B72B30
extern "C" double DAT_00B72B30;
// GLOBAL: GAMEMD 0x00B72B38
extern "C" double DAT_00B72B38;
// GLOBAL: GAMEMD 0x00B72B40
extern "C" double DAT_00B72B40;
// GLOBAL: GAMEMD 0x00B72B48
extern "C" int DAT_00B72B48;
// GLOBAL: GAMEMD 0x00B72B4C
extern "C" int DAT_00B72B4C;
// GLOBAL: GAMEMD 0x00B72B50
extern "C" int DAT_00B72B50;
// GLOBAL: GAMEMD 0x00B72B58
extern "C" double DAT_00B72B58;
// GLOBAL: GAMEMD 0x00B72B60
extern "C" double DAT_00B72B60;
// GLOBAL: GAMEMD 0x00B72B7C
extern "C" int DAT_00B72B7C;
// GLOBAL: GAMEMD 0x00B72B88
extern "C" int DAT_00B72B88;

// FUNCTION: GAMEMD 0x76F720
extern "C" void FUN_0076F720()
{
    DAT_00B72B30 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x76F790
extern "C" void FUN_0076F790()
{
    DAT_00B72B60 = DAT_007E1720 * DAT_007F7328;
}

// FUNCTION: GAMEMD 0x76F7B0
extern "C" void FUN_0076F7B0()
{
    DAT_00B72B38 = DAT_007E1728 * DAT_007F7328;
}

// FUNCTION: GAMEMD 0x76F7D0
extern "C" void FUN_0076F7D0()
{
    DAT_00B72B10 = DAT_007E1730 * DAT_007F7328;
}

// FUNCTION: GAMEMD 0x76F7F0
extern "C" void FUN_0076F7F0()
{
    DAT_00B72B88 = (int)(FUN_004CAD50(DAT_00B72B10 - DAT_00B72B38) * DAT_007E1738 * DAT_00B72B30);
}

// FUNCTION: GAMEMD 0x76F830
extern "C" void FUN_0076F830()
{
    DAT_00B72B40 = FUN_004CADE0(DAT_00B72B88 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x76F860
extern "C" void FUN_0076F860()
{
    DAT_00B72B58 = FUN_004CADE0((DAT_00B72B88 * 2) / DAT_00B72B30);
}

// FUNCTION: GAMEMD 0x76F890
extern "C" void FUN_0076F890()
{
    DAT_00B72B7C = (int)(DAT_00B72B88 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x76F8C0
extern "C" void FUN_0076F8C0()
{
    DAT_00B72B28 = 0;
    DAT_00B72B2A = 0;
}

// FUNCTION: GAMEMD 0x76F8D0
extern "C" void FUN_0076F8D0()
{
    DAT_00B72B48 = 0;
    DAT_00B72B4C = 0;
    DAT_00B72B50 = 0;
}
