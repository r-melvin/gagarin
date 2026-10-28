// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x735180-0x735330: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F5C30
extern "C" const double DAT_007F5C30;
// GLOBAL: GAMEMD 0x00B1CFA0
extern "C" double DAT_00B1CFA0;
// GLOBAL: GAMEMD 0x00B1CFB8
extern "C" short DAT_00B1CFB8;
// GLOBAL: GAMEMD 0x00B1CFBA
extern "C" short DAT_00B1CFBA;
// GLOBAL: GAMEMD 0x00B1CFD0
extern "C" double DAT_00B1CFD0;
// GLOBAL: GAMEMD 0x00B1CFD8
extern "C" double DAT_00B1CFD8;
// GLOBAL: GAMEMD 0x00B1CFE0
extern "C" double DAT_00B1CFE0;
// GLOBAL: GAMEMD 0x00B1CFE8
extern "C" int DAT_00B1CFE8;
// GLOBAL: GAMEMD 0x00B1CFEC
extern "C" int DAT_00B1CFEC;
// GLOBAL: GAMEMD 0x00B1CFF0
extern "C" int DAT_00B1CFF0;
// GLOBAL: GAMEMD 0x00B1CFF8
extern "C" double DAT_00B1CFF8;
// GLOBAL: GAMEMD 0x00B1D000
extern "C" double DAT_00B1D000;
// GLOBAL: GAMEMD 0x00B1D0AC
extern "C" int DAT_00B1D0AC;
// GLOBAL: GAMEMD 0x00B1D0B8
extern "C" int DAT_00B1D0B8;

// FUNCTION: GAMEMD 0x735180
extern "C" void FUN_00735180()
{
    DAT_00B1CFD0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x7351F0
extern "C" void FUN_007351F0()
{
    DAT_00B1D000 = DAT_007E1720 * DAT_007F5C30;
}

// FUNCTION: GAMEMD 0x735210
extern "C" void FUN_00735210()
{
    DAT_00B1CFD8 = DAT_007E1728 * DAT_007F5C30;
}

// FUNCTION: GAMEMD 0x735230
extern "C" void FUN_00735230()
{
    DAT_00B1CFA0 = DAT_007E1730 * DAT_007F5C30;
}

// FUNCTION: GAMEMD 0x735250
extern "C" void FUN_00735250()
{
    DAT_00B1D0B8 = (int)(FUN_004CAD50(DAT_00B1CFA0 - DAT_00B1CFD8) * DAT_007E1738 * DAT_00B1CFD0);
}

// FUNCTION: GAMEMD 0x735290
extern "C" void FUN_00735290()
{
    DAT_00B1CFE0 = FUN_004CADE0(DAT_00B1D0B8 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x7352C0
extern "C" void FUN_007352C0()
{
    DAT_00B1CFF8 = FUN_004CADE0((DAT_00B1D0B8 * 2) / DAT_00B1CFD0);
}

// FUNCTION: GAMEMD 0x7352F0
extern "C" void FUN_007352F0()
{
    DAT_00B1D0AC = (int)(DAT_00B1D0B8 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x735320
extern "C" void FUN_00735320()
{
    DAT_00B1CFB8 = 0;
    DAT_00B1CFBA = 0;
}

// FUNCTION: GAMEMD 0x735330
extern "C" void FUN_00735330()
{
    DAT_00B1CFE8 = 0;
    DAT_00B1CFEC = 0;
    DAT_00B1CFF0 = 0;
}
