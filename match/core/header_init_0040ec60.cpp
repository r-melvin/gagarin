// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The header initialiser group that opens the retail block at 0x40EC60
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy
//   /Ob2: retail folds the atexit registration into the 0x40F270 initialiser.
#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0x8873A8
extern double DAT_008873A8;
// GLOBAL: GAMEMD 0x7E1E18
const double DAT_007E1E18 = 60.0;

// SYNTHETIC: GAMEMD 0x40EC60
// GLOBAL: GAMEMD 0x8873F8
double DAT_008873F8 = DAT_008873A8 / DAT_007E1E18;
// SYNTHETIC: GAMEMD 0x40EC80
// GLOBAL: GAMEMD 0x8873E0
double DAT_008873E0 = 1.0 / DAT_008873F8;
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
