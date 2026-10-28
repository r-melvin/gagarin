// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x7AF0B0-0x7AF260: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F7910
extern "C" const double DAT_007F7910;
// GLOBAL: GAMEMD 0x00B77EB8
extern "C" double DAT_00B77EB8;
// GLOBAL: GAMEMD 0x00B77EE0
extern "C" short DAT_00B77EE0;
// GLOBAL: GAMEMD 0x00B77EE2
extern "C" short DAT_00B77EE2;
// GLOBAL: GAMEMD 0x00B77EE8
extern "C" double DAT_00B77EE8;
// GLOBAL: GAMEMD 0x00B77EF8
extern "C" double DAT_00B77EF8;
// GLOBAL: GAMEMD 0x00B77F00
extern "C" double DAT_00B77F00;
// GLOBAL: GAMEMD 0x00B77F10
extern "C" int DAT_00B77F10;
// GLOBAL: GAMEMD 0x00B77F14
extern "C" int DAT_00B77F14;
// GLOBAL: GAMEMD 0x00B77F18
extern "C" int DAT_00B77F18;
// GLOBAL: GAMEMD 0x00B77F28
extern "C" double DAT_00B77F28;
// GLOBAL: GAMEMD 0x00B77F38
extern "C" double DAT_00B77F38;
// GLOBAL: GAMEMD 0x00B77F80
extern "C" int DAT_00B77F80;
// GLOBAL: GAMEMD 0x00B77F90
extern "C" int DAT_00B77F90;

// FUNCTION: GAMEMD 0x7AF0B0
extern "C" void FUN_007AF0B0()
{
    DAT_00B77EE8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x7AF120
extern "C" void FUN_007AF120()
{
    DAT_00B77F38 = DAT_007E1720 * DAT_007F7910;
}

// FUNCTION: GAMEMD 0x7AF140
extern "C" void FUN_007AF140()
{
    DAT_00B77EF8 = DAT_007E1728 * DAT_007F7910;
}

// FUNCTION: GAMEMD 0x7AF160
extern "C" void FUN_007AF160()
{
    DAT_00B77EB8 = DAT_007E1730 * DAT_007F7910;
}

// FUNCTION: GAMEMD 0x7AF180
extern "C" void FUN_007AF180()
{
    DAT_00B77F90 = (int)(FUN_004CAD50(DAT_00B77EB8 - DAT_00B77EF8) * DAT_007E1738 * DAT_00B77EE8);
}

// FUNCTION: GAMEMD 0x7AF1C0
extern "C" void FUN_007AF1C0()
{
    DAT_00B77F00 = FUN_004CADE0(DAT_00B77F90 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x7AF1F0
extern "C" void FUN_007AF1F0()
{
    DAT_00B77F28 = FUN_004CADE0((DAT_00B77F90 * 2) / DAT_00B77EE8);
}

// FUNCTION: GAMEMD 0x7AF220
extern "C" void FUN_007AF220()
{
    DAT_00B77F80 = (int)(DAT_00B77F90 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x7AF250
extern "C" void FUN_007AF250()
{
    DAT_00B77EE0 = 0;
    DAT_00B77EE2 = 0;
}

// FUNCTION: GAMEMD 0x7AF260
extern "C" void FUN_007AF260()
{
    DAT_00B77F10 = 0;
    DAT_00B77F14 = 0;
    DAT_00B77F18 = 0;
}
