// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Static initialisers of the TU168 overlay math table (retail 0x5fc170-0x5fc2e0), disassembled
//   from the user's retail gamemd.exe v1.001 via the local Ghidra CLI. Kept beside
//   tu168_overlay_class.cpp (which defines 0x5fc1a0/0x5fc1c0 and reads DAT_00AC1530 as an extern)
//   so that file's _$E numbering is left alone. Same shape as the 0x438340 table in core.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

#include <math.h>

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1708
extern const double DAT_007E1708;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// GLOBAL: GAMEMD 0x7E1720
extern const double DAT_007E1720;
// GLOBAL: GAMEMD 0x7E1728
extern const double DAT_007E1728;
// GLOBAL: GAMEMD 0x7E1730
extern const double DAT_007E1730;
// GLOBAL: GAMEMD 0x7E1738
extern const double DAT_007E1738;
// GLOBAL: GAMEMD 0x7E1740
extern const double DAT_007E1740;
// GLOBAL: GAMEMD 0x7EF398
extern const double DAT_007EF398;

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x5FC170
// GLOBAL: GAMEMD 0xAC1530
double DAT_00AC1530 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));

// SYNTHETIC: GAMEMD 0x5FC1E0
// GLOBAL: GAMEMD 0xAC15B8
double DAT_00AC15B8 = DAT_007E1720 * DAT_007EF398;

// SYNTHETIC: GAMEMD 0x5FC200
// GLOBAL: GAMEMD 0xAC1538
double DAT_00AC1538 = DAT_007E1728 * DAT_007EF398;

// SYNTHETIC: GAMEMD 0x5FC220
// GLOBAL: GAMEMD 0xAC1510
double DAT_00AC1510 = DAT_007E1730 * DAT_007EF398;

// SYNTHETIC: GAMEMD 0x5FC240
// GLOBAL: GAMEMD 0xAC15E0
int DAT_00AC15E0 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00AC1510 - DAT_00AC1538) * DAT_00AC1530));

// SYNTHETIC: GAMEMD 0x5FC280
// GLOBAL: GAMEMD 0xAC1540
double DAT_00AC1540 = FUN_004CADE0((double)DAT_00AC15E0 * DAT_007E1740);

// SYNTHETIC: GAMEMD 0x5FC2B0
// GLOBAL: GAMEMD 0xAC1580
double DAT_00AC1580 = FUN_004CADE0((double)(DAT_00AC15E0 * 2) / DAT_00AC1530);

// SYNTHETIC: GAMEMD 0x5FC2E0
// GLOBAL: GAMEMD 0xAC15D4
int DAT_00AC15D4 = (int)((double)(DAT_00AC15E0 * 4) + DAT_007E1738);

// Small POD members whose constructors the compiler inlined into the static initialisers below.
struct OverlayStaticShortPair
{
    short X;
    short Y;
    OverlayStaticShortPair() : X(0), Y(0) {}
};

struct OverlayStaticZero3
{
    int A;
    int B;
    int C;
    OverlayStaticZero3() : A(0), B(0), C(0) {}
};

struct OverlayStaticCoord
{
    int X;
    int Y;
    int Z;
    OverlayStaticCoord() : X(128), Y(128), Z(0) {}
};

struct OverlayStaticZero4
{
    int A;
    int B;
    int C;
    int D;
    OverlayStaticZero4() : A(0), B(0), C(0), D(0) {}
};

// SYNTHETIC: GAMEMD 0x5FC310
// GLOBAL: GAMEMD 0xAC1528
OverlayStaticShortPair DAT_00AC1528;

// SYNTHETIC: GAMEMD 0x5FC320
// GLOBAL: GAMEMD 0xAC1570
OverlayStaticZero3 DAT_00AC1570;

// SYNTHETIC: GAMEMD 0x5FC340
// GLOBAL: GAMEMD 0xAC15C8
OverlayStaticCoord DAT_00AC15C8;

// SYNTHETIC: GAMEMD 0x5FC360
// GLOBAL: GAMEMD 0xAC1518
OverlayStaticZero4 DAT_00AC1518;

// SYNTHETIC: GAMEMD 0x5FE040
// GLOBAL: GAMEMD 0xAC15F8
OverlayStaticZero4 DAT_00AC15F8;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EF398
extern const double DAT_007EF398 = 0.017453292519943295;
// END defined globals
