// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
//
// Static ShapeButtonClass members in the Sidebar unit (0x6A4C10-0x6A4DB9). The run-time
// initialiser of each member (constructor plus atexit) is followed by an exit stub that
// tests and sets one bit of the shared guard byte 0x00B07BB1 before destroying the member.
// The bits in retail order are 1, 2, 4 (a four-element array), 8, 0x10. The object at
// 0x00B07E58 that owns bit 1 of guard byte 0x00B07BB0 is a different class and is not
// defined here.
#include "../shape_button_class.h"

// Not a retail function. The retail unit allocates a ShapeButtonClass array earlier, which
// instantiates the vector constructor/destructor helpers before these members are defined;
// without that first use VC6 starts a second guard byte after the array member (so bits 8
// and 0x10 would land in a new byte). This stand-in reproduces that ordering only.
ShapeButtonClass* SidebarButtonArrayStandIn() { return new ShapeButtonClass[3]; }

struct SidebarButtonStatics {
    // GLOBAL: GAMEMD 0x00B07DF8
    static ShapeButtonClass SellButton_00B07DF8;
    // GLOBAL: GAMEMD 0x00B0B3A0
    static ShapeButtonClass RepairButton_00B0B3A0;
    // GLOBAL: GAMEMD 0x00B07C48
    static ShapeButtonClass ButtonArray_00B07C48[4];
    // GLOBAL: GAMEMD 0x00B0B328
    static ShapeButtonClass Button_00B0B328;
    // GLOBAL: GAMEMD 0x00B0B408
    static ShapeButtonClass Button_00B0B408;
};

// SYNTHETIC: GAMEMD 0x006A4C60 -- initialiser of SellButton_00B07DF8
// SYNTHETIC: GAMEMD 0x006A4C80 -- exit-time destructor stub of SellButton_00B07DF8
ShapeButtonClass SidebarButtonStatics::SellButton_00B07DF8;
// SYNTHETIC: GAMEMD 0x006A4CA0 -- initialiser of RepairButton_00B0B3A0
// SYNTHETIC: GAMEMD 0x006A4CC0 -- exit-time destructor stub of RepairButton_00B0B3A0
ShapeButtonClass SidebarButtonStatics::RepairButton_00B0B3A0;
// SYNTHETIC: GAMEMD 0x006A4CE0 -- initialiser of ButtonArray_00B07C48
// SYNTHETIC: GAMEMD 0x006A4D10 -- exit-time destructor stub of ButtonArray_00B07C48
ShapeButtonClass SidebarButtonStatics::ButtonArray_00B07C48[4];
// SYNTHETIC: GAMEMD 0x006A4D40 -- initialiser of Button_00B0B328
// SYNTHETIC: GAMEMD 0x006A4D60 -- exit-time destructor stub of Button_00B0B328
ShapeButtonClass SidebarButtonStatics::Button_00B0B328;
// SYNTHETIC: GAMEMD 0x006A4D80 -- initialiser of Button_00B0B408
// SYNTHETIC: GAMEMD 0x006A4DA0 -- exit-time destructor stub of Button_00B0B408
ShapeButtonClass SidebarButtonStatics::Button_00B0B408;
