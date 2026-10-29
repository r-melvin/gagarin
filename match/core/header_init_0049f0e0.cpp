// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group (pow-derived cell diagonal, 60-unit ratio, angle table) that opens the retail block at 0x49F0E0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
#include <math.h>
#include "header_init_shapes.h"
#include "../_layout/geometry2d.h"
#include "cell_step_tables.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E5C40
const double DAT_007E5C40 = 60.0;
// GLOBAL: GAMEMD 0x7E5C48 -- degrees to radians
const double DAT_007E5C48 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x49F0E0
// GLOBAL: GAMEMD 0x89F6C0
double DAT_0089F6C0 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x49F110
// GLOBAL: GAMEMD 0x89F750
double DAT_0089F750 = DAT_0089F6C0 / DAT_007E5C40;
// SYNTHETIC: GAMEMD 0x49F130
// GLOBAL: GAMEMD 0x89F738
double DAT_0089F738 = 1.0 / DAT_0089F750;
// SYNTHETIC: GAMEMD 0x49F150
// GLOBAL: GAMEMD 0x89F730
double DAT_0089F730 = DAT_007E5C48 * 45.0;
// SYNTHETIC: GAMEMD 0x49F170
// GLOBAL: GAMEMD 0x89F6C8
double DAT_0089F6C8 = DAT_007E5C48 * 60.0;
// SYNTHETIC: GAMEMD 0x49F190
// GLOBAL: GAMEMD 0x89F680
double DAT_0089F680 = DAT_007E5C48 * 90.0;
// SYNTHETIC: GAMEMD 0x49F1B0
// GLOBAL: GAMEMD 0x89F758
int DAT_0089F758 = (int)(FUN_004CAD50(DAT_0089F680 - DAT_0089F6C8) * DAT_0089F6C0 * 0.5);
// SYNTHETIC: GAMEMD 0x49F1F0
// GLOBAL: GAMEMD 0x89F6D0
double DAT_0089F6D0 = FUN_004CADE0(DAT_0089F758 * 0.00390625);
// SYNTHETIC: GAMEMD 0x49F220
// GLOBAL: GAMEMD 0x89F728
double DAT_0089F728 = FUN_004CADE0((DAT_0089F758 * 2) / DAT_0089F6C0);
// SYNTHETIC: GAMEMD 0x49F250
// GLOBAL: GAMEMD 0x89F74C
int DAT_0089F74C = (int)(DAT_0089F758 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x49F280
// GLOBAL: GAMEMD 0x89F6B8
HeaderCellInit DAT_0089F6B8(0, 0);
// SYNTHETIC: GAMEMD 0x49F290
// GLOBAL: GAMEMD 0x89F718
HeaderCoordInit DAT_0089F718(0, 0, 0);
// SYNTHETIC: GAMEMD 0x49F2B0
// GLOBAL: GAMEMD 0x89F740
HeaderCoordInit DAT_0089F740(128, 128, 0);

// SYNTHETIC: GAMEMD 0x49F2F0
// GLOBAL: GAMEMD 0x89F688 -- the eight one-cell steps indexed by facing, N first, clockwise.
HeaderCellInit DAT_0089F688[8] = {
    HeaderCellInit(0, -1), HeaderCellInit(1, -1), HeaderCellInit(1, 0), HeaderCellInit(1, 1),
    HeaderCellInit(0, 1), HeaderCellInit(-1, 1), HeaderCellInit(-1, 0), HeaderCellInit(-1, -1)
};

// SYNTHETIC: GAMEMD 0x49F3A0
// GLOBAL: GAMEMD 0x89F6D8 -- the eight one-cell steps in leptons, N first, clockwise.
Point2D DAT_0089F6D8[8] = {
    Point2D(0, -256), Point2D(256, -256), Point2D(256, 0), Point2D(256, 256),
    Point2D(0, 256), Point2D(-256, 256), Point2D(-256, 0), Point2D(-256, -256)
};
