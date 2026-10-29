// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra; facts below were checked against the retail
// instructions and PE section bytes. The original source names are unknown.
// C linkage and void results are ABI bindings, not recovered declarations.
// Address grouping does not establish original ownership or startup role.
#include "../_rt/gg_static_assert.h"
#include "mathtbl_init_shapes.h"
GG_STATIC_ASSERT(sizeof(double) == 8);
GG_STATIC_ASSERT(sizeof(int) == 4);
GG_STATIC_ASSERT(sizeof(unsigned short) == 2);

// GLOBAL: GAMEMD 0x0089E1A0 (read by 0x4731C0; writable .data storage)
extern "C" double DAT_0089E1A0;
// GLOBAL: GAMEMD 0x0089E1F0 (written by 0x4731C0; writable .data storage)
// GLOBAL: GAMEMD 0x0089E1D8 (written by 0x4731E0; writable .data storage)
// GLOBAL: GAMEMD 0x0089E1D0 (written by 0x473200; writable .data storage)
// GLOBAL: GAMEMD 0x0089E1A8 (written by 0x473220; writable .data storage)
// GLOBAL: GAMEMD 0x0089E180 (written by 0x473240; writable .data storage)

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
// GLOBAL: GAMEMD 0x0089E1B0 (written at 0x4732B7; .data double)
// GLOBAL: GAMEMD 0x0089E1C8 (written at 0x4732F2; .data double)
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
// GLOBAL: GAMEMD 0x0089E1B8 (dword written at 0x473342)
// GLOBAL: GAMEMD 0x0089E1BC (dword written at 0x473347)
// GLOBAL: GAMEMD 0x0089E1C0 (dword written at 0x47334C)
// GLOBAL: GAMEMD 0x0089E1E0 (dword written at 0x47336F)
// GLOBAL: GAMEMD 0x0089E1E4 (dword written at 0x473374)
// GLOBAL: GAMEMD 0x0089E1E8 (dword written at 0x473365)
// GLOBAL: GAMEMD 0x0089E188 (dword written at 0x473382)
// GLOBAL: GAMEMD 0x0089E18C (dword written at 0x473387)
// GLOBAL: GAMEMD 0x0089E190 (dword written at 0x47338C)
// GLOBAL: GAMEMD 0x0089E194 (dword written at 0x473391)

// SYNTHETIC: GAMEMD 0x004731C0
// GLOBAL: GAMEMD 0x0089E1F0
double DAT_0089E1F0 = DAT_0089E1A0 / DAT_007E4BE0;

// SYNTHETIC: GAMEMD 0x004731E0
// GLOBAL: GAMEMD 0x0089E1D8
double DAT_0089E1D8 = 1.0 / DAT_0089E1F0;

// SYNTHETIC: GAMEMD 0x00473200
// GLOBAL: GAMEMD 0x0089E1D0
double DAT_0089E1D0 = DAT_007E1720 * DAT_007E4BE8;

// SYNTHETIC: GAMEMD 0x00473220
// GLOBAL: GAMEMD 0x0089E1A8
double DAT_0089E1A8 = DAT_007E1728 * DAT_007E4BE8;

// SYNTHETIC: GAMEMD 0x00473240
// GLOBAL: GAMEMD 0x0089E180
double DAT_0089E180 = DAT_007E1730 * DAT_007E4BE8;

// SYNTHETIC: GAMEMD 0x00473260
// GLOBAL: GAMEMD 0x0089E1F8
int DAT_0089E1F8 = (int)(FUN_004CAD50(DAT_0089E180 - DAT_0089E1A8) * DAT_007E1738 * DAT_0089E1A0);

// SYNTHETIC: GAMEMD 0x004732A0
// GLOBAL: GAMEMD 0x0089E1B0
double DAT_0089E1B0 = FUN_004CADE0((double)DAT_0089E1F8 * DAT_007E1740);

// SYNTHETIC: GAMEMD 0x004732D0
// GLOBAL: GAMEMD 0x0089E1C8
double DAT_0089E1C8 = FUN_004CADE0((double)(DAT_0089E1F8 * 2) / DAT_0089E1A0);

// SYNTHETIC: GAMEMD 0x00473300
// GLOBAL: GAMEMD 0x0089E1EC
int DAT_0089E1EC = (int)(DAT_0089E1F8 * 4 + DAT_007E1738);

// SYNTHETIC: GAMEMD 0x00473330
// GLOBAL: GAMEMD 0x0089E198
MathTblShortPair DAT_0089E198;

// SYNTHETIC: GAMEMD 0x00473340
// GLOBAL: GAMEMD 0x0089E1B8
MathTblZero3 DAT_0089E1B8;

// SYNTHETIC: GAMEMD 0x00473360
// GLOBAL: GAMEMD 0x0089E1E0
MathTblCoord DAT_0089E1E0;

// SYNTHETIC: GAMEMD 0x00473380
// GLOBAL: GAMEMD 0x0089E188
MathTblZero4 DAT_0089E188;
