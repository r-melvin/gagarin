// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; facts below were checked against the retail
// instructions and PE section bytes. The original source names are unknown.
// C linkage and void results are ABI bindings, not recovered declarations.
// Address grouping does not establish original ownership or startup role.
#include "../_rt/gg_static_assert.h"
GG_STATIC_ASSERT(sizeof(double) == 8);
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(unsigned short) == 2);

// GLOBAL: GAMEMD 0x0089E1A0 (read by 0x4731C0; writable .data storage)
extern "C" double DAT_0089E1A0;
// GLOBAL: GAMEMD 0x0089E1F0 (written by 0x4731C0; writable .data storage)
extern "C" double DAT_0089E1F0;
// GLOBAL: GAMEMD 0x0089E1D8 (written by 0x4731E0; writable .data storage)
extern "C" double DAT_0089E1D8;
// GLOBAL: GAMEMD 0x0089E1D0 (written by 0x473200; writable .data storage)
extern "C" double DAT_0089E1D0;
// GLOBAL: GAMEMD 0x0089E1A8 (written by 0x473220; writable .data storage)
extern "C" double DAT_0089E1A8;
// GLOBAL: GAMEMD 0x0089E180 (written by 0x473240; writable .data storage)
extern "C" double DAT_0089E180;

// GLOBAL: GAMEMD 0x007E4BE0 (double 60.0 in .rdata)
extern "C" const double DAT_007E4BE0;
// GLOBAL: GAMEMD 0x007E4BE8 (double 0.017453292519943295 in .rdata)
extern "C" const double DAT_007E4BE8;
// GLOBAL: GAMEMD 0x007E1720 (double 45.0 in .rdata)
extern "C" const double DAT_007E1720;
// GLOBAL: GAMEMD 0x007E1728 (double 60.0 in .rdata)
extern "C" const double DAT_007E1728;
// GLOBAL: GAMEMD 0x007E1730 (double 90.0 in .rdata)
extern "C" const double DAT_007E1730;

// GLOBAL: GAMEMD 0x0089E1F8 (written at 0x47328B, read at 0x4732A0 and 0x4732D1; .data dword)
extern "C" int DAT_0089E1F8;
// GLOBAL: GAMEMD 0x0089E1B0 (written at 0x4732B7; .data double)
extern "C" double DAT_0089E1B0;
// GLOBAL: GAMEMD 0x0089E1C8 (written at 0x4732F2; .data double)
extern "C" double DAT_0089E1C8;
// GLOBAL: GAMEMD 0x007E1738 (double 0.5 in .rdata)
extern "C" const double DAT_007E1738;
// GLOBAL: GAMEMD 0x007E1740 (double 0.00390625 in .rdata)
extern "C" const double DAT_007E1740;
// FUNCTION: GAMEMD 0x004CAD50 (decl; reloc; 8-byte argument, x87 result; return type is an ABI view)
extern "C" double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x004CADE0 (decl; reloc; 8-byte argument, x87 result; return type is an ABI view)
extern "C" double __cdecl FUN_004CADE0(double value);
// LIBRARY: GAMEMD 0x007C5F00 -- VC6 __ftol conversion helper.
// GLOBAL: GAMEMD 0x0089E1EC (dword written at 0x473320)
extern "C" int DAT_0089E1EC;
// GLOBAL: GAMEMD 0x0089E198 (word written at 0x473332)
extern "C" unsigned short DAT_0089E198;
// GLOBAL: GAMEMD 0x0089E19A (word written at 0x473338)
extern "C" unsigned short DAT_0089E19A;
// GLOBAL: GAMEMD 0x0089E1B8 (dword written at 0x473342)
extern "C" unsigned int DAT_0089E1B8;
// GLOBAL: GAMEMD 0x0089E1BC (dword written at 0x473347)
extern "C" unsigned int DAT_0089E1BC;
// GLOBAL: GAMEMD 0x0089E1C0 (dword written at 0x47334C)
extern "C" unsigned int DAT_0089E1C0;
// GLOBAL: GAMEMD 0x0089E1E0 (dword written at 0x47336F)
extern "C" unsigned int DAT_0089E1E0;
// GLOBAL: GAMEMD 0x0089E1E4 (dword written at 0x473374)
extern "C" unsigned int DAT_0089E1E4;
// GLOBAL: GAMEMD 0x0089E1E8 (dword written at 0x473365)
extern "C" unsigned int DAT_0089E1E8;
// GLOBAL: GAMEMD 0x0089E188 (dword written at 0x473382)
extern "C" unsigned int DAT_0089E188;
// GLOBAL: GAMEMD 0x0089E18C (dword written at 0x473387)
extern "C" unsigned int DAT_0089E18C;
// GLOBAL: GAMEMD 0x0089E190 (dword written at 0x47338C)
extern "C" unsigned int DAT_0089E190;
// GLOBAL: GAMEMD 0x0089E194 (dword written at 0x473391)
extern "C" unsigned int DAT_0089E194;

// FUNCTION: GAMEMD 0x004731C0
extern "C" void FUN_004731C0()
{
    DAT_0089E1F0 = DAT_0089E1A0 / DAT_007E4BE0;
}

// FUNCTION: GAMEMD 0x004731E0
extern "C" void FUN_004731E0()
{
    DAT_0089E1D8 = 1.0 / DAT_0089E1F0;
}

// FUNCTION: GAMEMD 0x00473200
extern "C" void FUN_00473200()
{
    DAT_0089E1D0 = DAT_007E1720 * DAT_007E4BE8;
}

// FUNCTION: GAMEMD 0x00473220
extern "C" void FUN_00473220()
{
    DAT_0089E1A8 = DAT_007E1728 * DAT_007E4BE8;
}

// FUNCTION: GAMEMD 0x00473240
extern "C" void FUN_00473240()
{
    DAT_0089E180 = DAT_007E1730 * DAT_007E4BE8;
}

// FUNCTION: GAMEMD 0x00473260
extern "C" void FUN_00473260()
{
    DAT_0089E1F8 = (int)(FUN_004CAD50(DAT_0089E180 - DAT_0089E1A8)
                         * DAT_007E1738 * DAT_0089E1A0);
}

// FUNCTION: GAMEMD 0x004732A0
extern "C" void FUN_004732A0()
{
    DAT_0089E1B0 = FUN_004CADE0((double)DAT_0089E1F8 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x004732D0
extern "C" void FUN_004732D0()
{
    DAT_0089E1C8 = FUN_004CADE0((double)(DAT_0089E1F8 * 2) / DAT_0089E1A0);
}

// FUNCTION: GAMEMD 0x00473300
extern "C" void FUN_00473300()
{
    DAT_0089E1EC = (int)(DAT_0089E1F8 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x00473330
extern "C" void FUN_00473330()
{
    DAT_0089E198 = 0;
    DAT_0089E19A = 0;
}

// FUNCTION: GAMEMD 0x00473340
extern "C" void FUN_00473340()
{
    DAT_0089E1B8 = 0;
    DAT_0089E1BC = 0;
    DAT_0089E1C0 = 0;
}

// FUNCTION: GAMEMD 0x00473360
extern "C" void FUN_00473360()
{
    DAT_0089E1E8 = 0;
    DAT_0089E1E0 = 0x80;
    DAT_0089E1E4 = 0x80;
}

// FUNCTION: GAMEMD 0x00473380
extern "C" void FUN_00473380()
{
    DAT_0089E188 = 0;
    DAT_0089E18C = 0;
    DAT_0089E190 = 0;
    DAT_0089E194 = 0;
}
