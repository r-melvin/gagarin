// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Complete entry-origin spans 0x473FE0 through 0x4741D0 and global references.
// Names, linkage and double helper result are compiler ABI views; original
// declarations, ownership and startup role remain unestablished.
#include "../_rt/gg_static_assert.h"
#include "mathtbl_init_shapes.h"
GG_STATIC_ASSERT(sizeof(double) == 8);
#include <math.h>

// LIBRARY: GAMEMD 0x007C8FB0 — VC6 x87 _CIpow intrinsic runtime.
// FUNCTION: GAMEMD 0x004CAC40 (decl; reloc) — one-double square-root helper.
extern "C" double __cdecl FUN_004CAC40(double value);
// GLOBAL: GAMEMD 0x007E1710 (retail double constant 256.0)
extern "C" const double DAT_007E1710;
// GLOBAL: GAMEMD 0x007E1708 (retail double constant 2.0)
extern "C" const double DAT_007E1708;
// GLOBAL: GAMEMD 0x0089E2B0 (store at 0x473FFE)


// GLOBAL: GAMEMD 0x007E4C48 (binary value 0.017453292519943295)
extern "C" const double DAT_007E4C48;
// GLOBAL: GAMEMD 0x007E1728 (binary value 60.0)
extern "C" const double DAT_007E1728;

// GLOBAL: GAMEMD 0x007E4C40
extern "C" const double DAT_007E4C40;
// GLOBAL: GAMEMD 0x007E1720 (45.0)
extern "C" const double DAT_007E1720;
// GLOBAL: GAMEMD 0x007E1730 (90.0)
extern "C" const double DAT_007E1730;

// FUNCTION: GAMEMD 0x004CAD50 (decl; reloc) 8-byte argument/x87 result; body in unowned_leaf_sweep_a.cpp
extern "C" double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x004CADE0 (decl; reloc) 8-byte argument/x87 result; body in trig_table_functions_004cac40.cpp
extern "C" double __cdecl FUN_004CADE0(double value);
// LIBRARY: GAMEMD 0x007C5F00 -- VC6 __ftol conversion helper.
// GLOBAL: GAMEMD 0x007E1738 (double 0.5)
extern "C" const double DAT_007E1738;
// GLOBAL: GAMEMD 0x007E1740 (double 0.00390625)
extern "C" const double DAT_007E1740;
// Storage widths are instruction-confirmed; original owner/grouping is unknown.
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(unsigned short) == 2);

// SYNTHETIC: GAMEMD 0x00473FE0
// GLOBAL: GAMEMD 0x0089E2B0
double DAT_0089E2B0 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));

// SYNTHETIC: GAMEMD 0x00474010
// GLOBAL: GAMEMD 0x0089E300
double DAT_0089E300 = DAT_0089E2B0 / DAT_007E4C40;

// SYNTHETIC: GAMEMD 0x00474030
// GLOBAL: GAMEMD 0x0089E2E8
double DAT_0089E2E8 = 1.0 / DAT_0089E300;

// SYNTHETIC: GAMEMD 0x00474050
// GLOBAL: GAMEMD 0x0089E2E0
double DAT_0089E2E0 = DAT_007E1720 * DAT_007E4C48;

// SYNTHETIC: GAMEMD 0x00474070
// GLOBAL: GAMEMD 0x0089E2B8
double DAT_0089E2B8 = DAT_007E1728 * DAT_007E4C48;

// SYNTHETIC: GAMEMD 0x00474090
// GLOBAL: GAMEMD 0x0089E290
double DAT_0089E290 = DAT_007E1730 * DAT_007E4C48;

// SYNTHETIC: GAMEMD 0x004740B0
// GLOBAL: GAMEMD 0x0089E308
int DAT_0089E308 = (int)(FUN_004CAD50(DAT_0089E290 - DAT_0089E2B8) * DAT_007E1738 * DAT_0089E2B0);

// SYNTHETIC: GAMEMD 0x004740F0
// GLOBAL: GAMEMD 0x0089E2C0
double DAT_0089E2C0 = FUN_004CADE0(DAT_0089E308 * DAT_007E1740);

// SYNTHETIC: GAMEMD 0x00474120
// GLOBAL: GAMEMD 0x0089E2D8
double DAT_0089E2D8 = FUN_004CADE0((DAT_0089E308 * 2) / DAT_0089E2B0);

// SYNTHETIC: GAMEMD 0x00474150
// GLOBAL: GAMEMD 0x0089E2FC
int DAT_0089E2FC = (int)(DAT_0089E308 * 4 + DAT_007E1738);

// SYNTHETIC: GAMEMD 0x00474180
// GLOBAL: GAMEMD 0x0089E2A8
MathTblShortPair DAT_0089E2A8;

// SYNTHETIC: GAMEMD 0x00474190
// GLOBAL: GAMEMD 0x0089E2C8
MathTblZero3 DAT_0089E2C8;

// SYNTHETIC: GAMEMD 0x004741B0
// GLOBAL: GAMEMD 0x0089E2F0
MathTblCoord DAT_0089E2F0;

// SYNTHETIC: GAMEMD 0x004741D0
// GLOBAL: GAMEMD 0x0089E298
MathTblZero4 DAT_0089E298;
