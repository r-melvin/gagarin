// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra
#include <math.h>
#include "mathtbl_init_shapes.h"
#pragma intrinsic(pow)

// Retail instructions at 0x4CB990 confirm four zeroed dword globals.


// SYNTHETIC: GAMEMD 0x004CB990
// GLOBAL: GAMEMD 0x008B3B38
MathTblZero4 DAT_008B3B38;

// GLOBAL: GAMEMD 0x7E89A8
extern "C" const double DAT_007E89A8;
// GLOBAL: GAMEMD 0x7E1718
// GLOBAL: GAMEMD 0x7E89B0
extern "C" const double DAT_007E89B0;
// GLOBAL: GAMEMD 0x7E1720
extern "C" const double DAT_007E1720;

// GLOBAL: GAMEMD 0x7E1710 — retail constant 256.0.
extern "C" const double DAT_007E1710;
// GLOBAL: GAMEMD 0x7E1708 — retail constant 2.0.
extern "C" const double DAT_007E1708;
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) — square-root helper.
extern double __cdecl FUN_004CAC40(double value);
// LIBRARY: GAMEMD 0x7C8FB0 — x87 _CIpow; emitted by VC6's pow intrinsic.

// SYNTHETIC: GAMEMD 0x004CB9B0
// GLOBAL: GAMEMD 0x008B3B50
double DAT_008B3B50 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));

// SYNTHETIC: GAMEMD 0x004CB9E0
// GLOBAL: GAMEMD 0x008B3BA0
double DAT_008B3BA0 = DAT_008B3B50 / DAT_007E89A8;

// SYNTHETIC: GAMEMD 0x004CBA00
// GLOBAL: GAMEMD 0x008B3B88
double DAT_008B3B88 = 1.0 / DAT_008B3BA0;

// SYNTHETIC: GAMEMD 0x004CBA20
// GLOBAL: GAMEMD 0x008B3B80
double DAT_008B3B80 = DAT_007E1720 * DAT_007E89B0;
