// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Complete 0x473FE0/0x474070 entry spans and observed global references.
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
    DAT_0089E2E0 = DAT_007E4C48 * DAT_007E1720;
}

// FUNCTION: GAMEMD 0x00474070
extern "C" void FUN_00474070()
{
    DAT_0089E2B8 = DAT_007E4C48 * DAT_007E1728;
}

// FUNCTION: GAMEMD 0x00474090
extern "C" void FUN_00474090()
{
    DAT_0089E290 = DAT_007E4C48 * DAT_007E1730;
}
