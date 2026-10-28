// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x754910-0x754AC0: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F6948
extern "C" const double DAT_007F6948;
// GLOBAL: GAMEMD 0x00B43ED8
extern "C" double DAT_00B43ED8;
// GLOBAL: GAMEMD 0x00B43EF0
extern "C" short DAT_00B43EF0;
// GLOBAL: GAMEMD 0x00B43EF2
extern "C" short DAT_00B43EF2;
// GLOBAL: GAMEMD 0x00B43EF8
extern "C" double DAT_00B43EF8;
// GLOBAL: GAMEMD 0x00B43F00
extern "C" double DAT_00B43F00;
// GLOBAL: GAMEMD 0x00B43F08
extern "C" double DAT_00B43F08;
// GLOBAL: GAMEMD 0x00B44300
extern "C" int DAT_00B44300;
// GLOBAL: GAMEMD 0x00B44304
extern "C" int DAT_00B44304;
// GLOBAL: GAMEMD 0x00B44308
extern "C" int DAT_00B44308;
// GLOBAL: GAMEMD 0x00B44310
extern "C" double DAT_00B44310;
// GLOBAL: GAMEMD 0x00B44498
extern "C" double DAT_00B44498;
// GLOBAL: GAMEMD 0x00B45178
extern "C" int DAT_00B45178;
// GLOBAL: GAMEMD 0x00B45578
extern "C" int DAT_00B45578;

// FUNCTION: GAMEMD 0x754910
extern "C" void FUN_00754910()
{
    DAT_00B43EF8 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x754980
extern "C" void FUN_00754980()
{
    DAT_00B44498 = DAT_007E1720 * DAT_007F6948;
}

// FUNCTION: GAMEMD 0x7549A0
extern "C" void FUN_007549A0()
{
    DAT_00B43F00 = DAT_007E1728 * DAT_007F6948;
}

// FUNCTION: GAMEMD 0x7549C0
extern "C" void FUN_007549C0()
{
    DAT_00B43ED8 = DAT_007E1730 * DAT_007F6948;
}

// FUNCTION: GAMEMD 0x7549E0
extern "C" void FUN_007549E0()
{
    DAT_00B45578 = (int)(FUN_004CAD50(DAT_00B43ED8 - DAT_00B43F00) * DAT_007E1738 * DAT_00B43EF8);
}

// FUNCTION: GAMEMD 0x754A20
extern "C" void FUN_00754A20()
{
    DAT_00B43F08 = FUN_004CADE0(DAT_00B45578 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x754A50
extern "C" void FUN_00754A50()
{
    DAT_00B44310 = FUN_004CADE0((DAT_00B45578 * 2) / DAT_00B43EF8);
}

// FUNCTION: GAMEMD 0x754A80
extern "C" void FUN_00754A80()
{
    DAT_00B45178 = (int)(DAT_00B45578 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x754AB0
extern "C" void FUN_00754AB0()
{
    DAT_00B43EF0 = 0;
    DAT_00B43EF2 = 0;
}

// FUNCTION: GAMEMD 0x754AC0
extern "C" void FUN_00754AC0()
{
    DAT_00B44300 = 0;
    DAT_00B44304 = 0;
    DAT_00B44308 = 0;
}
