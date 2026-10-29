// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// /Ob2 retains the ordinary destructor body in the scalar deleting wrapper.
// Retail 0x4E12F0..0x4E133E establishes all stores and the conditional flag OR.
// Exact once Next/Previous come from the inline LinkClass constructor: the base
// stores them first, ahead of the member initialisers.
#include "gadget_class_methods.h"

extern GadgetClass* GadgetClass_StuckOn;    // 0x008B3E88
extern GadgetClass* GadgetClass_LastList;   // 0x008B3E8C
extern GadgetClass* GadgetClass_Focused;    // 0x008B3E90

// FUNCTION: GAMEMD 0x4E12F0
GadgetClass::GadgetClass(int x, int y, int width, int height,
                         unsigned int flags, char sticky)
    : X(x), Y(y), Width(width), Height(height), IsToRepaint(0),
      IsSticky(sticky), IsDisabled(0), Flags(flags)
{
    if (sticky != 0) {
        Flags |= 5;
    }
}

// FUNCTION: GAMEMD 0x4E1390
GadgetClass::~GadgetClass()
{
    if (this == GadgetClass_Focused) {
        Flags &= ~0x100u;
        GadgetClass_Focused = 0;
    }
    if (this == GadgetClass_StuckOn) {
        GadgetClass_StuckOn = 0;
    }
    if (this == GadgetClass_LastList) {
        GadgetClass_LastList = 0;
    }
    if (this == GadgetClass_Focused) {
        GadgetClass_Focused = 0;
    }
}

// SYNTHETIC: GAMEMD 0x4E1A60
// GadgetClass scalar deleting destructor, emitted from the ordinary destructor.
