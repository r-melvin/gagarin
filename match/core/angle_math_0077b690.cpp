// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x77B690-0x77B840: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F7518
extern "C" const double DAT_007F7518;
// GLOBAL: GAMEMD 0x00B73AC0
extern "C" double DAT_00B73AC0;
// GLOBAL: GAMEMD 0x00B75F50
extern "C" short DAT_00B75F50;
// GLOBAL: GAMEMD 0x00B75F52
extern "C" short DAT_00B75F52;
// GLOBAL: GAMEMD 0x00B75F60
extern "C" double DAT_00B75F60;
// GLOBAL: GAMEMD 0x00B761A0
extern "C" double DAT_00B761A0;
// GLOBAL: GAMEMD 0x00B76460
extern "C" double DAT_00B76460;
// GLOBAL: GAMEMD 0x00B76960
extern "C" int DAT_00B76960;
// GLOBAL: GAMEMD 0x00B76964
extern "C" int DAT_00B76964;
// GLOBAL: GAMEMD 0x00B76968
extern "C" int DAT_00B76968;
// GLOBAL: GAMEMD 0x00B76AF8
extern "C" double DAT_00B76AF8;
// GLOBAL: GAMEMD 0x00B778C0
extern "C" double DAT_00B778C0;
// GLOBAL: GAMEMD 0x00B77CD0
extern "C" int DAT_00B77CD0;
// GLOBAL: GAMEMD 0x00B77D74
extern "C" int DAT_00B77D74;

// FUNCTION: GAMEMD 0x77B690
extern "C" void FUN_0077B690()
{
    DAT_00B75F60 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x77B700
extern "C" void FUN_0077B700()
{
    DAT_00B778C0 = DAT_007E1720 * DAT_007F7518;
}

// FUNCTION: GAMEMD 0x77B720
extern "C" void FUN_0077B720()
{
    DAT_00B761A0 = DAT_007E1728 * DAT_007F7518;
}

// FUNCTION: GAMEMD 0x77B740
extern "C" void FUN_0077B740()
{
    DAT_00B73AC0 = DAT_007E1730 * DAT_007F7518;
}

// FUNCTION: GAMEMD 0x77B760
extern "C" void FUN_0077B760()
{
    DAT_00B77D74 = (int)(FUN_004CAD50(DAT_00B73AC0 - DAT_00B761A0) * DAT_007E1738 * DAT_00B75F60);
}

// FUNCTION: GAMEMD 0x77B7A0
extern "C" void FUN_0077B7A0()
{
    DAT_00B76460 = FUN_004CADE0(DAT_00B77D74 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x77B7D0
extern "C" void FUN_0077B7D0()
{
    DAT_00B76AF8 = FUN_004CADE0((DAT_00B77D74 * 2) / DAT_00B75F60);
}

// FUNCTION: GAMEMD 0x77B800
extern "C" void FUN_0077B800()
{
    DAT_00B77CD0 = (int)(DAT_00B77D74 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x77B830
extern "C" void FUN_0077B830()
{
    DAT_00B75F50 = 0;
    DAT_00B75F52 = 0;
}

// FUNCTION: GAMEMD 0x77B840
extern "C" void FUN_0077B840()
{
    DAT_00B76960 = 0;
    DAT_00B76964 = 0;
    DAT_00B76968 = 0;
}
