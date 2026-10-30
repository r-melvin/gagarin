// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Static initialisers of the TU169 overlay-type math table (retail 0x5fe060-0x5fe230),
//   disassembled from the user's retail gamemd.exe v1.001 via the local Ghidra CLI. Kept beside
//   tu169_overlay_type_class.cpp (which defines 0x5fe090/0x5fe0b0 and reads DAT_00AC1610 as an
//   extern) so that file's _$E numbering is left alone. Same shape as tu168_overlay_statics.cpp.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

#include <math.h>

// GLOBAL: GAMEMD 0x7E1708
extern const double DAT_007E1708;
// GLOBAL: GAMEMD 0x7E1710
extern const double DAT_007E1710;
// GLOBAL: GAMEMD 0x7E1728
extern const double DAT_007E1728;
// GLOBAL: GAMEMD 0x7E1730
extern const double DAT_007E1730;
// GLOBAL: GAMEMD 0x7E1738
extern const double DAT_007E1738;
// GLOBAL: GAMEMD 0x7E1740
extern const double DAT_007E1740;
// GLOBAL: GAMEMD 0x7E1720
extern const double DAT_007E1720;
// GLOBAL: GAMEMD 0x7EF5C8
extern const double DAT_007EF5C8;

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc)
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc)
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc)
double __cdecl FUN_004CADE0(double value);

// SYNTHETIC: GAMEMD 0x5FE060
// GLOBAL: GAMEMD 0xAC1610
double DAT_00AC1610 = FUN_004CAC40(2.0 * pow(DAT_007E1710, DAT_007E1708));

// SYNTHETIC: GAMEMD 0x5FE0D0
// GLOBAL: GAMEMD 0xAC1648
double DAT_00AC1648 = DAT_007E1720 * DAT_007EF5C8;

// SYNTHETIC: GAMEMD 0x5FE0F0
// GLOBAL: GAMEMD 0xAC1618
double DAT_00AC1618 = DAT_007E1728 * DAT_007EF5C8;

// SYNTHETIC: GAMEMD 0x5FE110
// GLOBAL: GAMEMD 0xAC15F0
double DAT_00AC15F0 = DAT_007E1730 * DAT_007EF5C8;

// SYNTHETIC: GAMEMD 0x5FE130
// GLOBAL: GAMEMD 0xAC1670
int DAT_00AC1670 = (int)(DAT_007E1738 * (FUN_004CAD50(DAT_00AC15F0 - DAT_00AC1618) * DAT_00AC1610));

// SYNTHETIC: GAMEMD 0x5FE170
// GLOBAL: GAMEMD 0xAC1620
double DAT_00AC1620 = FUN_004CADE0((double)DAT_00AC1670 * DAT_007E1740);

// SYNTHETIC: GAMEMD 0x5FE1A0
// GLOBAL: GAMEMD 0xAC1638
double DAT_00AC1638 = FUN_004CADE0((double)(DAT_00AC1670 * 2) / DAT_00AC1610);

// SYNTHETIC: GAMEMD 0x5FE1D0
// GLOBAL: GAMEMD 0xAC1664
int DAT_00AC1664 = (int)((double)(DAT_00AC1670 * 4) + DAT_007E1738);

// Small POD members whose constructors the compiler inlined into the static initialisers below.
struct OverlayTypeStaticShortPair
{
    short X;
    short Y;
    OverlayTypeStaticShortPair() : X(0), Y(0) {}
};

struct OverlayTypeStaticZero3
{
    int A;
    int B;
    int C;
    OverlayTypeStaticZero3() : A(0), B(0), C(0) {}
};

struct OverlayTypeStaticCoord
{
    int X;
    int Y;
    int Z;
    OverlayTypeStaticCoord() : X(128), Y(128), Z(0) {}
};

// SYNTHETIC: GAMEMD 0x5FE200
// GLOBAL: GAMEMD 0xAC1608
OverlayTypeStaticShortPair DAT_00AC1608;

// SYNTHETIC: GAMEMD 0x5FE210
// GLOBAL: GAMEMD 0xAC1628
OverlayTypeStaticZero3 DAT_00AC1628;

// SYNTHETIC: GAMEMD 0x5FE230
// GLOBAL: GAMEMD 0xAC1658
OverlayTypeStaticCoord DAT_00AC1658;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7EF5C8
extern const double DAT_007EF5C8 = 0.017453292519943295;
// END defined globals
