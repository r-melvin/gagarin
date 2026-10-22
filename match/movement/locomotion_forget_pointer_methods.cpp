// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra

#include "locomotion_forget_pointer_methods.h"

// FUNCTION: GAMEMD 0x710410
//
// Forget the item wherever this holder still refers to it, then pass it on to
// the shared release helper.
void Holder_00710410::FUN_00710410(void* item)
{
    if (item == this->RefA) {
        this->RefA = 0;
    }
    if (item == this->RefB) {
        this->RefB = 0;
    }
    if (item == this->RefC) {
        this->RefC = 0;
    }
    if (item == this->RefD) {
        this->RefD = 0;
    }
    FUN_005F6DA0(item);
}
