#include "mathtbl_init_shapes.h"
// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
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

// GLOBAL: GAMEMD 0x008B3B48
extern "C" unsigned short DAT_008B3B48;
// GLOBAL: GAMEMD 0x008B3B4A
extern "C" unsigned short DAT_008B3B4A;
// GLOBAL: GAMEMD 0x008B3B50
extern "C" double DAT_008B3B50;

// SYNTHETIC: GAMEMD 0x004CBA40
// GLOBAL: GAMEMD 0x008B3B58
double DAT_008B3B58 = DAT_007E1728 * DAT_007E89B0;

// SYNTHETIC: GAMEMD 0x004CBA60
// GLOBAL: GAMEMD 0x008B3B30
double DAT_008B3B30 = DAT_007E1730 * DAT_007E89B0;

// SYNTHETIC: GAMEMD 0x004CBA80
// GLOBAL: GAMEMD 0x008B3BA8
int DAT_008B3BA8 = (int)(FUN_004CAD50(DAT_008B3B30 - DAT_008B3B58) * DAT_007E1738 * DAT_008B3B50);

// SYNTHETIC: GAMEMD 0x004CBAC0
// GLOBAL: GAMEMD 0x008B3B60
double DAT_008B3B60 = FUN_004CADE0((double)DAT_008B3BA8 * DAT_007E1740);

// SYNTHETIC: GAMEMD 0x004CBAF0
// GLOBAL: GAMEMD 0x008B3B78
double DAT_008B3B78 = FUN_004CADE0((double)(DAT_008B3BA8 * 2) / DAT_008B3B50);

// SYNTHETIC: GAMEMD 0x004CBB20
// GLOBAL: GAMEMD 0x008B3B9C
int DAT_008B3B9C = (int)(DAT_008B3BA8 * 4 + DAT_007E1738);

// FUNCTION: GAMEMD 0x4CBB50
extern "C" void FUN_004CBB50()
{
    DAT_008B3B48 = 0;
    DAT_008B3B4A = 0;
}

// SYNTHETIC: GAMEMD 0x004CBB60
// GLOBAL: GAMEMD 0x008B3B68
MathTblZero3 DAT_008B3B68;

// SYNTHETIC: GAMEMD 0x004CBB80
// GLOBAL: GAMEMD 0x008B3B90
MathTblCoord DAT_008B3B90;
