// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Complete entry-origin spans 0x473FE0 through 0x4741D0 and global references.
// Names, linkage and double helper result are compiler ABI views; original
// declarations, ownership and startup role remain unestablished.
#include "../_rt/gg_static_assert.h"
GG_STATIC_ASSERT(sizeof(double) == 8);
#include <math.h>
#pragma intrinsic(pow)

// LIBRARY: GAMEMD 0x007C8FB0 — VC6 x87 _CIpow intrinsic runtime.
// FUNCTION: GAMEMD 0x004CAC40 (decl; reloc) — one-double square-root helper.
extern "C" double __cdecl FUN_004CAC40(double value);
// GLOBAL: GAMEMD 0x007E1710 (retail double constant 256.0)
extern "C" const double DAT_007E1710;
// GLOBAL: GAMEMD 0x007E1708 (retail double constant 2.0)
extern "C" const double DAT_007E1708;
// GLOBAL: GAMEMD 0x0089E2B0 (store at 0x473FFE)
extern "C" double DAT_0089E2B0;


// GLOBAL: GAMEMD 0x007E4C48 (binary value 0.017453292519943295)
extern "C" const double DAT_007E4C48;
// GLOBAL: GAMEMD 0x007E1728 (binary value 60.0)
extern "C" const double DAT_007E1728;
// GLOBAL: GAMEMD 0x0089E2B8
extern "C" double DAT_0089E2B8;

// GLOBAL: GAMEMD 0x0089E300
extern "C" double DAT_0089E300;
// GLOBAL: GAMEMD 0x0089E2E8
extern "C" double DAT_0089E2E8;
// GLOBAL: GAMEMD 0x0089E2E0
extern "C" double DAT_0089E2E0;
// GLOBAL: GAMEMD 0x0089E290
extern "C" double DAT_0089E290;
// GLOBAL: GAMEMD 0x007E4C40
extern "C" const double DAT_007E4C40;
// GLOBAL: GAMEMD 0x007E1718 (1.0)
extern "C" const double DAT_007E1718;
// GLOBAL: GAMEMD 0x007E1720 (45.0)
extern "C" const double DAT_007E1720;
// GLOBAL: GAMEMD 0x007E1730 (90.0)
extern "C" const double DAT_007E1730;

// FUNCTION: GAMEMD 0x004CAD50 (decl; reloc) 8-byte argument/x87 result; body in unowned_leaf_sweep_a.cpp
extern "C" double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x004CADE0 (8-byte argument/x87 result; original return type unknown)
extern "C" double __cdecl FUN_004CADE0(double value);
// LIBRARY: GAMEMD 0x007C5F00 -- VC6 __ftol conversion helper.
// GLOBAL: GAMEMD 0x007E1738 (double 0.5)
extern "C" const double DAT_007E1738;
// GLOBAL: GAMEMD 0x007E1740 (double 0.00390625)
extern "C" const double DAT_007E1740;
// GLOBAL: GAMEMD 0x0089E308
extern "C" int DAT_0089E308;
// GLOBAL: GAMEMD 0x0089E2FC
extern "C" int DAT_0089E2FC;
// GLOBAL: GAMEMD 0x0089E2C0
extern "C" double DAT_0089E2C0;
// GLOBAL: GAMEMD 0x0089E2D8
extern "C" double DAT_0089E2D8;
// GLOBAL: GAMEMD 0x0089E2A8
extern "C" unsigned short DAT_0089E2A8;
// GLOBAL: GAMEMD 0x0089E2AA
extern "C" unsigned short DAT_0089E2AA;
// GLOBAL: GAMEMD 0x0089E2C8
extern "C" int DAT_0089E2C8;
// GLOBAL: GAMEMD 0x0089E2CC
extern "C" int DAT_0089E2CC;
// GLOBAL: GAMEMD 0x0089E2D0
extern "C" int DAT_0089E2D0;
// GLOBAL: GAMEMD 0x0089E2F8
extern "C" int DAT_0089E2F8;
// GLOBAL: GAMEMD 0x0089E2F0
extern "C" int DAT_0089E2F0;
// GLOBAL: GAMEMD 0x0089E2F4
extern "C" int DAT_0089E2F4;
// GLOBAL: GAMEMD 0x0089E298
extern "C" int DAT_0089E298;
// GLOBAL: GAMEMD 0x0089E29C
extern "C" int DAT_0089E29C;
// GLOBAL: GAMEMD 0x0089E2A0
extern "C" int DAT_0089E2A0;
// GLOBAL: GAMEMD 0x0089E2A4
extern "C" int DAT_0089E2A4;
// Storage widths are instruction-confirmed; original owner/grouping is unknown.
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(unsigned short) == 2);

// FUNCTION: GAMEMD 0x00473FE0
extern "C" void FUN_00473FE0()
{
    DAT_0089E2B0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));
}

// FUNCTION: GAMEMD 0x00474010
extern "C" void FUN_00474010()
{
    DAT_0089E300 = DAT_0089E2B0 / DAT_007E4C40;
}

// FUNCTION: GAMEMD 0x00474030
extern "C" void FUN_00474030()
{
    DAT_0089E2E8 = DAT_007E1718 / DAT_0089E300;
}

// FUNCTION: GAMEMD 0x00474050
extern "C" void FUN_00474050()
{
    DAT_0089E2E0 = DAT_007E1720 * DAT_007E4C48;
}

// FUNCTION: GAMEMD 0x00474070
extern "C" void FUN_00474070()
{
    DAT_0089E2B8 = DAT_007E1728 * DAT_007E4C48;
}

// FUNCTION: GAMEMD 0x00474090
extern "C" void FUN_00474090()
{
    DAT_0089E290 = DAT_007E1730 * DAT_007E4C48;
}

// FUNCTION: GAMEMD 0x004740B0
extern "C" void FUN_004740B0()
{
    DAT_0089E308 = (int)(FUN_004CAD50(DAT_0089E290 - DAT_0089E2B8) * DAT_007E1738 * DAT_0089E2B0);
}

// FUNCTION: GAMEMD 0x004740F0
extern "C" void FUN_004740F0()
{
    DAT_0089E2C0 = FUN_004CADE0(DAT_0089E308 * DAT_007E1740);
}

// FUNCTION: GAMEMD 0x00474120
extern "C" void FUN_00474120()
{
    DAT_0089E2D8 = FUN_004CADE0((DAT_0089E308 * 2) / DAT_0089E2B0);
}

// FUNCTION: GAMEMD 0x00474150
extern "C" void FUN_00474150()
{
    DAT_0089E2FC = (int)(DAT_0089E308 * 4 + DAT_007E1738);
}

// FUNCTION: GAMEMD 0x00474180
extern "C" void FUN_00474180()
{
    DAT_0089E2A8 = 0;
    DAT_0089E2AA = 0;
}

// FUNCTION: GAMEMD 0x00474190
extern "C" void FUN_00474190()
{
    DAT_0089E2C8 = 0;
    DAT_0089E2CC = 0;
    DAT_0089E2D0 = 0;
}

// FUNCTION: GAMEMD 0x004741B0
extern "C" void FUN_004741B0()
{
    DAT_0089E2F8 = 0;
    DAT_0089E2F0 = 128;
    DAT_0089E2F4 = 128;
}

// FUNCTION: GAMEMD 0x004741D0
extern "C" void FUN_004741D0()
{
    DAT_0089E298 = 0;
    DAT_0089E29C = 0;
    DAT_0089E2A0 = 0;
    DAT_0089E2A4 = 0;
}
