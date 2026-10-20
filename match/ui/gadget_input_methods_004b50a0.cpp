// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; helper behavior confirmed in retail.
#include "gadget_input_methods_004b50a0.h"

// LIBRARY: GAMEMD 0x007CA422 — bounded 16-bit CRT string copy; body out of scope.
extern "C" unsigned short* __cdecl FUN_007CA422(unsigned short* destination,
                                                unsigned short* source,
                                                int count);

// FUNCTION: GAMEMD 0x004B50A0
void GadgetInputView_004B50A0::FUN_004B50A0()
{
    if (this->unknown_48) {
        this->PartB0.Slot9();
        this->unknown_48 = 0;
    }
}

// FUNCTION: GAMEMD 0x004B50C0
void GadgetInputView_004B50A0::FUN_004B50C0(unsigned char flags,
                                           unsigned int* state,
                                           int* target)
{
    if (target == reinterpret_cast<int*>(this->unknown_50) && (flags & 4)) {
        if (this->unknown_48) {
            this->PartB0.Slot9();
            this->unknown_48 = 0;
            *state = (unsigned int)this->unknown_24 | 0x8000;
        } else {
            this->cache_BC = this->X;
            this->cache_C0 = this->Y + 0x12;
            this->cache_C4 = this->Width;
            this->cache_C8 = this->unknown_4C;
            this->PartB0.Slot3(this->HeadOfList());
            this->PartB0.Slot18();
            this->unknown_48 = 1;
        }
    }
    if (target == reinterpret_cast<int*>(&this->PartB0)) {
        FUN_007CA422(this->unknown_34, this->PartB0.Slot39(), this->unknown_38);
        this->MarkRedraw();
        *state = (unsigned int)this->unknown_24 | 0x8000;
    }
}

// FUNCTION: GAMEMD 0x004B5190
void GadgetInputView_004B50A0::FUN_004B5190()
{
    if (!this->unknown_48) {
        this->cache_BC = this->X;
        this->cache_C0 = this->Y + 0x12;
        this->cache_C4 = this->Width;
        this->cache_C8 = this->unknown_4C;
        this->PartB0.Slot3(this->HeadOfList());
        this->PartB0.Slot18();
        this->unknown_48 = 1;
    }
}

// FUNCTION: GAMEMD 0x004B51F0
void GadgetInputView_004B50A0::FUN_004B51F0()
{
    if (this->unknown_48) {
        this->PartB0.Slot9();
        this->unknown_48 = 0;
    }
}
