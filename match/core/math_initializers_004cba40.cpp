// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | original
// Retail constants and global addresses read from gamemd.exe v1.001.

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) — binary math helper.
extern double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) — binary math helper.
extern double __cdecl FUN_004CADE0(double value);
// LIBRARY: GAMEMD 0x7C5F00 — MSVC x87 conversion helper emitted for int casts.

// GLOBAL: GAMEMD 0x007E89B0 — radians per degree, numeric value 0.017453292519943295.
extern "C" const double DAT_007E89B0;
// GLOBAL: GAMEMD 0x007E1728 — numeric value 60.0.
extern "C" const double DAT_007E1728;
// GLOBAL: GAMEMD 0x007E1730 — numeric value 90.0.
extern "C" const double DAT_007E1730;
// GLOBAL: GAMEMD 0x007E1738 — numeric value 0.5.
extern "C" const double DAT_007E1738;
// GLOBAL: GAMEMD 0x007E1740 — numeric value 0.00390625.
extern "C" const double DAT_007E1740;

// GLOBAL: GAMEMD 0x008B3B30
extern "C" double DAT_008B3B30;
// GLOBAL: GAMEMD 0x008B3B48
extern "C" unsigned short DAT_008B3B48;
// GLOBAL: GAMEMD 0x008B3B4A
extern "C" unsigned short DAT_008B3B4A;
// GLOBAL: GAMEMD 0x008B3B50
extern "C" double DAT_008B3B50;
// GLOBAL: GAMEMD 0x008B3B58
extern "C" double DAT_008B3B58;
// GLOBAL: GAMEMD 0x008B3B60
extern "C" double DAT_008B3B60;
// GLOBAL: GAMEMD 0x008B3B68
extern "C" unsigned int DAT_008B3B68;
// GLOBAL: GAMEMD 0x008B3B6C
extern "C" unsigned int DAT_008B3B6C;
// GLOBAL: GAMEMD 0x008B3B70
extern "C" unsigned int DAT_008B3B70;
// GLOBAL: GAMEMD 0x008B3B78
extern "C" double DAT_008B3B78;
// GLOBAL: GAMEMD 0x008B3B90
extern "C" unsigned int DAT_008B3B90;
// GLOBAL: GAMEMD 0x008B3B94
extern "C" unsigned int DAT_008B3B94;
// GLOBAL: GAMEMD 0x008B3B98
extern "C" unsigned int DAT_008B3B98;
// GLOBAL: GAMEMD 0x008B3B9C
extern "C" int DAT_008B3B9C;
// GLOBAL: GAMEMD 0x008B3BA8
extern "C" int DAT_008B3BA8;

// FUNCTION: GAMEMD 0x4CBA40
extern "C" void FUN_004CBA40()
{
    DAT_008B3B58 = DAT_007E89B0 * DAT_007E1728;
}

// FUNCTION: GAMEMD 0x4CBA60
extern "C" void FUN_004CBA60()
{
    DAT_008B3B30 = DAT_007E89B0 * DAT_007E1730;
}

// FUNCTION: GAMEMD 0x4CBA80
extern "C" void FUN_004CBA80()
{
    DAT_008B3BA8 = (int)(FUN_004CAD50(DAT_008B3B30 - DAT_008B3B58)
                         * DAT_008B3B50 * DAT_007E1738);
}

// FUNCTION: GAMEMD 0x4CBAC0
extern "C" void FUN_004CBAC0()
{
    DAT_008B3B60 = FUN_004CADE0((double)DAT_008B3BA8 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x4CBAF0
extern "C" void FUN_004CBAF0()
{
    DAT_008B3B78 = FUN_004CADE0((double)(DAT_008B3BA8 * 2) / DAT_008B3B50);
}

// FUNCTION: GAMEMD 0x4CBB20
extern "C" void FUN_004CBB20()
{
    DAT_008B3B9C = (int)(DAT_008B3BA8 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x4CBB50
extern "C" void FUN_004CBB50()
{
    DAT_008B3B48 = 0;
    DAT_008B3B4A = 0;
}

// FUNCTION: GAMEMD 0x4CBB60
extern "C" void FUN_004CBB60()
{
    DAT_008B3B68 = 0;
    DAT_008B3B6C = 0;
    DAT_008B3B70 = 0;
}

// FUNCTION: GAMEMD 0x4CBB80
extern "C" void FUN_004CBB80()
{
    DAT_008B3B98 = 0;
    DAT_008B3B90 = 0x80;
    DAT_008B3B94 = 0x80;
}
