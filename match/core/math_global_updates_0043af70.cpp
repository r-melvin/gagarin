// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra
// Entry-bounded retail evidence: 0x43AF70 reads doubles at 0x89C820 and
// 0x7E3E78, then stores to 0x89C880; 0x43AF90 reads 0x7E1718 and 0x89C880,
// then stores to 0x89C868. Both complete entry spans are 19 bytes.
// Further entry-bounded operations through 0x43B130 are grouped here for
// organization only. The 0x7E inputs are read-only .rdata. Original owners,
// source-file boundaries and startup registration are not established.
// Helper declarations model the observed stack-double input and x87 result;
// float versus double in the original return declaration is not established.
#include "../_rt/gg_static_assert.h"
#include "mathtbl_init_shapes.h"
#include "../_layout/global_0089c818.h"
GG_STATIC_ASSERT(sizeof(double) == 8);
GG_STATIC_ASSERT(sizeof(int) == 4);

extern "C" double DAT_0089C820; // GLOBAL: GAMEMD 0x0089C820
extern "C" const double DAT_007E3E78; // GLOBAL: GAMEMD 0x007E3E78

extern "C" const double DAT_007E3E80; // GLOBAL: GAMEMD 0x007E3E80
extern "C" const double DAT_007E1720; // GLOBAL: GAMEMD 0x007E1720
extern "C" const double DAT_007E1728; // GLOBAL: GAMEMD 0x007E1728
extern "C" const double DAT_007E1730; // GLOBAL: GAMEMD 0x007E1730
extern "C" const double DAT_007E1738; // GLOBAL: GAMEMD 0x007E1738
extern "C" double __cdecl FUN_004CAD50(double value); // FUNCTION: GAMEMD 0x004CAD50 (decl; reloc)
extern "C" const double DAT_007E1740; // GLOBAL: GAMEMD 0x007E1740
extern "C" double __cdecl FUN_004CADE0(double value); // FUNCTION: GAMEMD 0x004CADE0 (decl; reloc)
// LIBRARY: GAMEMD 0x7C5F00 -- VC6 __ftol conversion helper.




// SYNTHETIC: GAMEMD 0x0043AF70
// GLOBAL: GAMEMD 0x0089C880
double DAT_0089C880 = DAT_0089C820 / DAT_007E3E78;

// SYNTHETIC: GAMEMD 0x0043AF90
// GLOBAL: GAMEMD 0x0089C868
double DAT_0089C868 = 1.0 / DAT_0089C880;

// SYNTHETIC: GAMEMD 0x0043AFB0
// GLOBAL: GAMEMD 0x0089C860
double DAT_0089C860 = DAT_007E1720 * DAT_007E3E80;

// SYNTHETIC: GAMEMD 0x0043AFD0
// GLOBAL: GAMEMD 0x0089C830
double DAT_0089C830 = DAT_007E1728 * DAT_007E3E80;

// SYNTHETIC: GAMEMD 0x0043AFF0
// GLOBAL: GAMEMD 0x0089C7F8
double DAT_0089C7F8 = DAT_007E1730 * DAT_007E3E80;

// SYNTHETIC: GAMEMD 0x0043B010
// GLOBAL: GAMEMD 0x0089C888
int DAT_0089C888 = (int)(FUN_004CAD50(DAT_0089C7F8 - DAT_0089C830) * DAT_007E1738 * DAT_0089C820);

// SYNTHETIC: GAMEMD 0x0043B050
// GLOBAL: GAMEMD 0x0089C840
double DAT_0089C840 = FUN_004CADE0((double)DAT_0089C888 * DAT_007E1740);

// SYNTHETIC: GAMEMD 0x0043B080
// GLOBAL: GAMEMD 0x0089C858
double DAT_0089C858 = FUN_004CADE0((double)(DAT_0089C888 * 2) / DAT_0089C820);

// SYNTHETIC: GAMEMD 0x0043B0B0
// GLOBAL: GAMEMD 0x0089C87C
int DAT_0089C87C = (int)(DAT_0089C888 * 4 + DAT_007E1738);

// SYNTHETIC: GAMEMD 0x0043B0E0
// GLOBAL: GAMEMD 0x0089C818
Global_0089C818_View DAT_0089C818;

// SYNTHETIC: GAMEMD 0x0043B0F0
// GLOBAL: GAMEMD 0x0089C848
MathTblZero3 DAT_0089C848;

// SYNTHETIC: GAMEMD 0x0043B110
// GLOBAL: GAMEMD 0x0089C870
MathTblCoord DAT_0089C870;
// SYNTHETIC: GAMEMD 0x0043B130
// GLOBAL: GAMEMD 0x0089C808
MathTblZero4 DAT_0089C808;
