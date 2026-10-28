// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x717DF0-0x717FA0: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F4FD0
extern "C" const double DAT_007F4FD0;
// GLOBAL: GAMEMD 0x00B0EBC0
extern "C" double DAT_00B0EBC0;
// GLOBAL: GAMEMD 0x00B0EBD8
extern "C" short DAT_00B0EBD8;
// GLOBAL: GAMEMD 0x00B0EBDA
extern "C" short DAT_00B0EBDA;
// GLOBAL: GAMEMD 0x00B0EBE0
extern "C" double DAT_00B0EBE0;
// GLOBAL: GAMEMD 0x00B0EBE8
extern "C" double DAT_00B0EBE8;
// GLOBAL: GAMEMD 0x00B0EBF0
extern "C" double DAT_00B0EBF0;
// GLOBAL: GAMEMD 0x00B0EBF8
extern "C" int DAT_00B0EBF8;
// GLOBAL: GAMEMD 0x00B0EBFC
extern "C" int DAT_00B0EBFC;
// GLOBAL: GAMEMD 0x00B0EC00
extern "C" int DAT_00B0EC00;
// GLOBAL: GAMEMD 0x00B0EC08
extern "C" double DAT_00B0EC08;
// GLOBAL: GAMEMD 0x00B0EC10
extern "C" double DAT_00B0EC10;
// GLOBAL: GAMEMD 0x00B0EC2C
extern "C" int DAT_00B0EC2C;
// GLOBAL: GAMEMD 0x00B0EC38
extern "C" int DAT_00B0EC38;

// FUNCTION: GAMEMD 0x717DF0
extern "C" void FUN_00717DF0()
{
    DAT_00B0EBE0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x717E60
extern "C" void FUN_00717E60()
{
    DAT_00B0EC10 = DAT_007E1720 * DAT_007F4FD0;
}

// FUNCTION: GAMEMD 0x717E80
extern "C" void FUN_00717E80()
{
    DAT_00B0EBE8 = DAT_007E1728 * DAT_007F4FD0;
}

// FUNCTION: GAMEMD 0x717EA0
extern "C" void FUN_00717EA0()
{
    DAT_00B0EBC0 = DAT_007E1730 * DAT_007F4FD0;
}

// FUNCTION: GAMEMD 0x717EC0
extern "C" void FUN_00717EC0()
{
    DAT_00B0EC38 = (int)(FUN_004CAD50(DAT_00B0EBC0 - DAT_00B0EBE8) * DAT_007E1738 * DAT_00B0EBE0);
}

// FUNCTION: GAMEMD 0x717F00
extern "C" void FUN_00717F00()
{
    DAT_00B0EBF0 = FUN_004CADE0(DAT_00B0EC38 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x717F30
extern "C" void FUN_00717F30()
{
    DAT_00B0EC08 = FUN_004CADE0((DAT_00B0EC38 * 2) / DAT_00B0EBE0);
}

// FUNCTION: GAMEMD 0x717F60
extern "C" void FUN_00717F60()
{
    DAT_00B0EC2C = (int)(DAT_00B0EC38 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x717F90
extern "C" void FUN_00717F90()
{
    DAT_00B0EBD8 = 0;
    DAT_00B0EBDA = 0;
}

// FUNCTION: GAMEMD 0x717FA0
extern "C" void FUN_00717FA0()
{
    DAT_00B0EBF8 = 0;
    DAT_00B0EBFC = 0;
    DAT_00B0EC00 = 0;
}
