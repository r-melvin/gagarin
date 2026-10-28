// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// Static members of the Radar unit's guarded group (guard byte 0x00B048A8): bit 1 is a
// GadgetClass-derived object at 0x00B04A10 (initialiser 0x652870, exit stub 0x6528A0) whose
// class is not recovered, so a placeholder holds the bit and its by-product code is not
// claimed. Bits 2 and 4 are the two ShapeButtonClass members below (initialisers 0x6528D0
// and 0x652920, exit stubs 0x6528F0 and 0x652940).
#include "shape_button_class.h"

struct RadarGadgetPlaceholder_00B04A10 {
    RadarGadgetPlaceholder_00B04A10();
    ~RadarGadgetPlaceholder_00B04A10();
    int unknown;
};

struct RadarButtonStatics {
    // GLOBAL: GAMEMD 0x00B04A10
    static RadarGadgetPlaceholder_00B04A10 Gadget_00B04A10;
    // GLOBAL: GAMEMD 0x00B04978
    static ShapeButtonClass RadarButtonF2_00B04978;
    // GLOBAL: GAMEMD 0x00B04910
    static ShapeButtonClass RadarButtonF3_00B04910;
};

RadarGadgetPlaceholder_00B04A10 RadarButtonStatics::Gadget_00B04A10;
// SYNTHETIC: GAMEMD 0x006528D0 -- initialiser of RadarButtonF2_00B04978
// SYNTHETIC: GAMEMD 0x006528F0 -- exit-time destructor stub of RadarButtonF2_00B04978
ShapeButtonClass RadarButtonStatics::RadarButtonF2_00B04978;
// SYNTHETIC: GAMEMD 0x00652920 -- initialiser of RadarButtonF3_00B04910
// SYNTHETIC: GAMEMD 0x00652940 -- exit-time destructor stub of RadarButtonF3_00B04910
ShapeButtonClass RadarButtonStatics::RadarButtonF3_00B04910;
