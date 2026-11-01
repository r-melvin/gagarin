// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; helper copy behavior confirmed in retail.
#include "gadget_method_004b5030.h"

// LIBRARY: GAMEMD 0x007CA489 — null-terminated 16-bit CRT string copy; body out of scope.
extern "C" unsigned short* __cdecl FUN_007CA489(unsigned short* destination,
                                                unsigned short* source);

// FUNCTION: GAMEMD 0x004B5030
void GadgetMethodView_004B5030::FUN_004B5030(unsigned int value)
{
    GadgetSubobjectView_004B5030* part = &this->PartB0;
    unsigned int count = part->Slot37();
    if (value < count) {
        part->Slot46(value);
        unsigned short* text = part->Slot40(this->Slot41());
        unsigned short* destination = this->unknown_34;
        FUN_007CA489(destination, text);
    } else {
        *this->unknown_34 = 0;
    }
}
