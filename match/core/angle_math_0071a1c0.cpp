// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x71A1C0-0x71A370: a further copy of the angle-table setup (same shapes as
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
// GLOBAL: GAMEMD 0x007F5108
extern "C" const double DAT_007F5108;
// GLOBAL: GAMEMD 0x00B0EC40
extern "C" double DAT_00B0EC40;
// GLOBAL: GAMEMD 0x00B0EC58
extern "C" short DAT_00B0EC58;
// GLOBAL: GAMEMD 0x00B0EC5A
extern "C" short DAT_00B0EC5A;
// GLOBAL: GAMEMD 0x00B0EC78
extern "C" double DAT_00B0EC78;
// GLOBAL: GAMEMD 0x00B0EC80
extern "C" double DAT_00B0EC80;
// GLOBAL: GAMEMD 0x00B0EC88
extern "C" double DAT_00B0EC88;
// GLOBAL: GAMEMD 0x00B0EC90
extern "C" int DAT_00B0EC90;
// GLOBAL: GAMEMD 0x00B0EC94
extern "C" int DAT_00B0EC94;
// GLOBAL: GAMEMD 0x00B0EC98
extern "C" int DAT_00B0EC98;
// GLOBAL: GAMEMD 0x00B0ECA0
extern "C" double DAT_00B0ECA0;
// GLOBAL: GAMEMD 0x00B0ECA8
extern "C" double DAT_00B0ECA8;
// GLOBAL: GAMEMD 0x00B0ECC4
extern "C" int DAT_00B0ECC4;
// GLOBAL: GAMEMD 0x00B0ECD0
extern "C" int DAT_00B0ECD0;

// FUNCTION: GAMEMD 0x71A1C0
extern "C" void FUN_0071A1C0()
{
    DAT_00B0EC78 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x71A230
extern "C" void FUN_0071A230()
{
    DAT_00B0ECA8 = DAT_007E1720 * DAT_007F5108;
}

// FUNCTION: GAMEMD 0x71A250
extern "C" void FUN_0071A250()
{
    DAT_00B0EC80 = DAT_007E1728 * DAT_007F5108;
}

// FUNCTION: GAMEMD 0x71A270
extern "C" void FUN_0071A270()
{
    DAT_00B0EC40 = DAT_007E1730 * DAT_007F5108;
}

// FUNCTION: GAMEMD 0x71A290
extern "C" void FUN_0071A290()
{
    DAT_00B0ECD0 = (int)(FUN_004CAD50(DAT_00B0EC40 - DAT_00B0EC80) * DAT_007E1738 * DAT_00B0EC78);
}

// FUNCTION: GAMEMD 0x71A2D0
extern "C" void FUN_0071A2D0()
{
    DAT_00B0EC88 = FUN_004CADE0(DAT_00B0ECD0 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x71A300
extern "C" void FUN_0071A300()
{
    DAT_00B0ECA0 = FUN_004CADE0((DAT_00B0ECD0 * 2) / DAT_00B0EC78);
}

// FUNCTION: GAMEMD 0x71A330
extern "C" void FUN_0071A330()
{
    DAT_00B0ECC4 = (int)(DAT_00B0ECD0 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x71A360
extern "C" void FUN_0071A360()
{
    DAT_00B0EC58 = 0;
    DAT_00B0EC5A = 0;
}

// FUNCTION: GAMEMD 0x71A370
extern "C" void FUN_0071A370()
{
    DAT_00B0EC90 = 0;
    DAT_00B0EC94 = 0;
    DAT_00B0EC98 = 0;
}
