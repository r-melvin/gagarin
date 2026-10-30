// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Static members of the Radar unit's guarded group (guard byte 0x00B048A8): bit 1 is a
// GadgetClass-derived object at 0x00B04A10 (initialiser 0x652870, exit stub 0x6528A0) whose
// class is RadarClass::RTacticalClass. Bits 2 and 4 are the two ShapeButtonClass members below (initialisers 0x6528D0
// and 0x652920, exit stubs 0x6528F0 and 0x652940).
#include "shape_button_class.h"

// RTTI: .?AVRTacticalClass@RadarClass@@ (type 0x839298, COL 0x808378, vtable 0x7F02BC). It
// derives GadgetClass and overrides slot 0 (scalar deleting destructor 0x658780) and slot 31
// (Action 0x6539D0).
// VTABLE: GAMEMD 0x7F02BC
class RadarTacticalGadget_00B04A10 : public GadgetClass {
public:
    RadarTacticalGadget_00B04A10() : GadgetClass(0, 0, 0, 0, 0x9F, 1) {}
    // FUNCTION: GAMEMD 0x6539D0 (decl; reloc) -- slot 31 (Action).
    virtual int Action(unsigned flags, unsigned* key, int modifier);
};

// SYNTHETIC: GAMEMD 0x00658780 -- implicit scalar deleting destructor (slot 0) of RadarTacticalGadget_00B04A10
struct RadarButtonStatics {
    // GLOBAL: GAMEMD 0x00B04A10
    static RadarTacticalGadget_00B04A10 Gadget_00B04A10;
    // GLOBAL: GAMEMD 0x00B04978
    static ShapeButtonClass RadarButtonF2_00B04978;
    // GLOBAL: GAMEMD 0x00B04910
    static ShapeButtonClass RadarButtonF3_00B04910;
};

// SYNTHETIC: GAMEMD 0x00652870 -- initialiser of Gadget_00B04A10
// SYNTHETIC: GAMEMD 0x006528A0 -- guarded exit stub of Gadget_00B04A10
RadarTacticalGadget_00B04A10 RadarButtonStatics::Gadget_00B04A10;
// SYNTHETIC: GAMEMD 0x006528D0 -- initialiser of RadarButtonF2_00B04978
// SYNTHETIC: GAMEMD 0x006528F0 -- exit-time destructor stub of RadarButtonF2_00B04978
ShapeButtonClass RadarButtonStatics::RadarButtonF2_00B04978;
// SYNTHETIC: GAMEMD 0x00652920 -- initialiser of RadarButtonF3_00B04910
// SYNTHETIC: GAMEMD 0x00652940 -- exit-time destructor stub of RadarButtonF3_00B04910
ShapeButtonClass RadarButtonStatics::RadarButtonF3_00B04910;
