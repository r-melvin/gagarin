// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail static initialisers 0x6F0470-0x6F0660 and the hex parser at 0x6F0680 were read
// instruction by instruction from gamemd.exe v1.001; global addresses and constants confirmed.
#include <math.h>
#pragma intrinsic(pow)

// LIBRARY: GAMEMD 0x7C8FB0 -- VC6 x87 _CIpow emitted for intrinsic pow.
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- square-root helper.
extern double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- table helper.
extern double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- table helper.
extern double __cdecl FUN_004CADE0(double value);
// LIBRARY: GAMEMD 0x7C99B4 isxdigit, 0x7C998C isdigit, 0x7C97D3 toupper.
extern "C" int __cdecl FUN_007C99B4(int c);
extern "C" int __cdecl FUN_007C998C(int c);
extern "C" int __cdecl FUN_007C97D3(int c);

// GLOBAL: GAMEMD 0x007E1708 -- constant 2.0.
extern "C" const double DAT_007E1708;
// GLOBAL: GAMEMD 0x007E1710 -- constant 256.0.
extern "C" const double DAT_007E1710;
// GLOBAL: GAMEMD 0x007E1720 -- constant 45.0.
extern "C" const double DAT_007E1720;
// GLOBAL: GAMEMD 0x007E1728 -- constant 60.0.
extern "C" const double DAT_007E1728;
// GLOBAL: GAMEMD 0x007E1730 -- constant 90.0.
extern "C" const double DAT_007E1730;
// GLOBAL: GAMEMD 0x007E1738
extern "C" const double DAT_007E1738;
// GLOBAL: GAMEMD 0x007E1740
extern "C" const double DAT_007E1740;
// GLOBAL: GAMEMD 0x007F4798 -- radians per degree.
extern "C" const double DAT_007F4798;

// GLOBAL: GAMEMD 0x00B0E9D0
extern "C" double DAT_00B0E9D0;
// GLOBAL: GAMEMD 0x00B0EA00
extern "C" double DAT_00B0EA00;
// GLOBAL: GAMEMD 0x00B0E9D8
extern "C" double DAT_00B0E9D8;
// GLOBAL: GAMEMD 0x00B0E9B0
extern "C" double DAT_00B0E9B0;
// GLOBAL: GAMEMD 0x00B0EA28
extern "C" int DAT_00B0EA28;
// GLOBAL: GAMEMD 0x00B0E9E0
extern "C" double DAT_00B0E9E0;
// GLOBAL: GAMEMD 0x00B0E9F8
extern "C" double DAT_00B0E9F8;
// GLOBAL: GAMEMD 0x00B0EA1C
extern "C" int DAT_00B0EA1C;
// GLOBAL: GAMEMD 0x00B0E9C8
extern "C" short DAT_00B0E9C8;
// GLOBAL: GAMEMD 0x00B0E9CA
extern "C" short DAT_00B0E9CA;
// GLOBAL: GAMEMD 0x00B0E9E8
extern "C" int DAT_00B0E9E8;
// GLOBAL: GAMEMD 0x00B0E9EC
extern "C" int DAT_00B0E9EC;
// GLOBAL: GAMEMD 0x00B0E9F0
extern "C" int DAT_00B0E9F0;
// GLOBAL: GAMEMD 0x00B0EA10
extern "C" int DAT_00B0EA10;
// GLOBAL: GAMEMD 0x00B0EA14
extern "C" int DAT_00B0EA14;
// GLOBAL: GAMEMD 0x00B0EA18
extern "C" int DAT_00B0EA18;
// GLOBAL: GAMEMD 0x00B0E9B8
extern "C" int DAT_00B0E9B8;
// GLOBAL: GAMEMD 0x00B0E9BC
extern "C" int DAT_00B0E9BC;
// GLOBAL: GAMEMD 0x00B0E9C0
extern "C" int DAT_00B0E9C0;
// GLOBAL: GAMEMD 0x00B0E9C4
extern "C" int DAT_00B0E9C4;

// FUNCTION: GAMEMD 0x6F0470
extern "C" void FUN_006F0470()
{
    DAT_00B0E9D0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x6F04E0
extern "C" void FUN_006F04E0()
{
    DAT_00B0EA00 = DAT_007E1720 * DAT_007F4798;
}

// FUNCTION: GAMEMD 0x6F0500
extern "C" void FUN_006F0500()
{
    DAT_00B0E9D8 = DAT_007E1728 * DAT_007F4798;
}

// FUNCTION: GAMEMD 0x6F0520
extern "C" void FUN_006F0520()
{
    DAT_00B0E9B0 = DAT_007E1730 * DAT_007F4798;
}

// FUNCTION: GAMEMD 0x6F0540
extern "C" void FUN_006F0540()
{
    DAT_00B0EA28 = (int)(FUN_004CAD50(DAT_00B0E9B0 - DAT_00B0E9D8) * DAT_007E1738 * DAT_00B0E9D0);
}

// FUNCTION: GAMEMD 0x6F0580
extern "C" void FUN_006F0580()
{
    DAT_00B0E9E0 = FUN_004CADE0(DAT_00B0EA28 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x6F05B0
extern "C" void FUN_006F05B0()
{
    DAT_00B0E9F8 = FUN_004CADE0((DAT_00B0EA28 * 2) / DAT_00B0E9D0);
}

// FUNCTION: GAMEMD 0x6F05E0
extern "C" void FUN_006F05E0()
{
    DAT_00B0EA1C = (int)(DAT_00B0EA28 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x6F0610
extern "C" void FUN_006F0610()
{
    DAT_00B0E9C8 = 0;
    DAT_00B0E9CA = 0;
}

// FUNCTION: GAMEMD 0x6F0620
extern "C" void FUN_006F0620()
{
    DAT_00B0E9E8 = 0;
    DAT_00B0E9EC = 0;
    DAT_00B0E9F0 = 0;
}

// FUNCTION: GAMEMD 0x6F0640
extern "C" void FUN_006F0640()
{
    DAT_00B0EA18 = 0;
    DAT_00B0EA10 = 0x80;
    DAT_00B0EA14 = 0x80;
}

// FUNCTION: GAMEMD 0x6F0660
extern "C" void FUN_006F0660()
{
    DAT_00B0E9B8 = 0;
    DAT_00B0E9BC = 0;
    DAT_00B0E9C0 = 0;
    DAT_00B0E9C4 = 0;
}

// FUNCTION: GAMEMD 0x6F0680 -- parse a hexadecimal string.
int FUN_006F0680(const char* text)
{
    int value = 0;

    while (FUN_007C99B4(*text) != 0) {
        value <<= 4;
        if (FUN_007C998C(*text) != 0) {
            value += *text - 0x30;
        } else {
            value += FUN_007C97D3(*text) - 0x37;
        }
        text++;
    }

    return value;
}
