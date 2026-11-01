// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40EC60
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
//   /Ob2: retail folds the atexit registration into the 0x40F270 initialiser.
#include <math.h>
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E1E18
const double DAT_007E1E18 = 60.0;
// GLOBAL: GAMEMD 0x7E1E20 -- degrees to radians
const double DAT_007E1E20 = 0.017453292519943295;

// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x40EC30
// GLOBAL: GAMEMD 0x8873A8
double DAT_008873A8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);
// SYNTHETIC: GAMEMD 0x40EC60
// GLOBAL: GAMEMD 0x8873F8
double DAT_008873F8 = DAT_008873A8 / DAT_007E1E18;
// SYNTHETIC: GAMEMD 0x40EC80
// GLOBAL: GAMEMD 0x8873E0
double DAT_008873E0 = 1.0 / DAT_008873F8;
// SYNTHETIC: GAMEMD 0x40ECA0
// GLOBAL: GAMEMD 0x8873D8
double DAT_008873D8 = DAT_007E1E20 * 45.0;
// SYNTHETIC: GAMEMD 0x40ECC0
// GLOBAL: GAMEMD 0x8873B0
double DAT_008873B0 = DAT_007E1E20 * 60.0;
// SYNTHETIC: GAMEMD 0x40ECE0
// GLOBAL: GAMEMD 0x887370
double DAT_00887370 = DAT_007E1E20 * 90.0;
// SYNTHETIC: GAMEMD 0x40ED00
// GLOBAL: GAMEMD 0x887400
int DAT_00887400 = (int)(FUN_004CAD50(DAT_00887370 - DAT_008873B0) * DAT_008873A8 * 0.5);
// SYNTHETIC: GAMEMD 0x40ED40
// GLOBAL: GAMEMD 0x8873B8
double DAT_008873B8 = FUN_004CADE0(DAT_00887400 * 0.00390625);
// SYNTHETIC: GAMEMD 0x40ED70
// GLOBAL: GAMEMD 0x8873D0
double DAT_008873D0 = FUN_004CADE0((DAT_00887400 * 2) / DAT_008873A8);
// SYNTHETIC: GAMEMD 0x40EDA0
// GLOBAL: GAMEMD 0x8873F4
int DAT_008873F4 = (int)(DAT_00887400 * 4 + 0.5);
// SYNTHETIC: GAMEMD 0x40EDD0
// GLOBAL: GAMEMD 0x8873A0
HeaderCellInit DAT_008873A0(0, 0);
// SYNTHETIC: GAMEMD 0x40EDE0
// GLOBAL: GAMEMD 0x8873C0
HeaderCoordInit DAT_008873C0(0, 0, 0);
// SYNTHETIC: GAMEMD 0x40EE00
// GLOBAL: GAMEMD 0x8873E8
HeaderCoordInit DAT_008873E8(128, 128, 0);

// A buffer object whose constructor (0x6C89B0, RET 4) records a size and
// allocates that many bytes into +0x04 / +0x08, and whose destructor
// (0x6C89D0) frees +0x04. Placeholder class.
class Obj_006C89B0
{
public:
    // FUNCTION: GAMEMD 0x6C89B0 (declaration)
    Obj_006C89B0(int size);
    // FUNCTION: GAMEMD 0x6C89D0 (declaration)
    ~Obj_006C89B0();

    int   unknown_00;   // +0x00  the size
    void* unknown_04;   // +0x04  the buffer
    void* unknown_08;   // +0x08  a cursor into it
};

// SYNTHETIC: GAMEMD 0x40F270 -- initialiser: constructs DAT_00887460, registers 0x40F290.
// SYNTHETIC: GAMEMD 0x40F290 -- atexit cleanup: destroys DAT_00887460.
// GLOBAL: GAMEMD 0x887460
Obj_006C89B0 DAT_00887460(4000000);
