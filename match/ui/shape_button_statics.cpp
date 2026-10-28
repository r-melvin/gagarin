// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// Static ShapeButtonClass members in the unit at 0x6CFBA0-0x6CFC79: a 25-element array
// (0x00B0C1C0..0x00B0CB20) and two single buttons. The run-time initialiser of each
// (constructor plus atexit) is followed by an exit stub that tests and sets one bit of the
// shared guard byte 0x00B0C1AC (bits 1, 2, 4) before destroying the member.
#include "shape_button_class.h"

// Not a retail function: it instantiates the vector constructor/destructor helpers first,
// as retail code earlier in the unit does, so the guard bits stay in one byte.
ShapeButtonClass* ShapeButtonArrayStandIn() { return new ShapeButtonClass[3]; }

struct ShapeButtonStatics {
    // GLOBAL: GAMEMD 0x00B0C1C0
    static ShapeButtonClass ButtonArray_00B0C1C0[25];
    // GLOBAL: GAMEMD 0x00B0CCB0
    static ShapeButtonClass Button_00B0CCB0;
    // GLOBAL: GAMEMD 0x00B0CC40
    static ShapeButtonClass Button_00B0CC40;
};

// SYNTHETIC: GAMEMD 0x006CFBA0 -- initialiser of ButtonArray_00B0C1C0
ShapeButtonClass ShapeButtonStatics::ButtonArray_00B0C1C0[25];
// SYNTHETIC: GAMEMD 0x006CFC00 -- initialiser of Button_00B0CCB0
ShapeButtonClass ShapeButtonStatics::Button_00B0CCB0;
// SYNTHETIC: GAMEMD 0x006CFC40 -- initialiser of Button_00B0CC40
ShapeButtonClass ShapeButtonStatics::Button_00B0CC40;
