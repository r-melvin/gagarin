// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Retail RTTI at vtable 0x7E8118 (COL 0x800010, type 0x8202D8)
// identifies ToggleClass. Constructor 0x723E60 calls ControlClass and
// initializes +0x2C, +0x2D, +0x30; TurnOn/Off dispatch via inherited slot +0x48.
#ifndef GG_MATCH_UI_TOGGLE_CLASS_METHODS_H
#define GG_MATCH_UI_TOGGLE_CLASS_METHODS_H
#include "control_class.h"

// VTABLE: GAMEMD 0x7E8118
struct ToggleClass : ControlClass
{
    // The inherited virtual destructor is implicit; retail calls Gadget destruction.
    virtual int Action(unsigned flags, unsigned* key, int modifier); // slot 31, 0x723EC0

    ToggleClass(int id, int x, int y, int width, int height);
    void TurnOn();
    void TurnOff();

    unsigned char unknown_2C;
    unsigned char IsOn;
    char unknown_2E[2];
    int unknown_30;
};
GG_STATIC_ASSERT(offsetof(ToggleClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(ToggleClass, IsOn) == 0x2D);
GG_STATIC_ASSERT(offsetof(ToggleClass, unknown_2E) == 0x2E);
GG_STATIC_ASSERT(offsetof(ToggleClass, unknown_30) == 0x30);
GG_STATIC_ASSERT(sizeof(ToggleClass) == 0x34);
#endif
