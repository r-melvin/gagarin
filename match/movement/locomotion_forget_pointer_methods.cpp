// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra

#include "locomotion_forget_pointer_methods.h"

// FUNCTION: GAMEMD 0x710410
//
// Forget the item wherever this holder still refers to it, then pass it on to
// the shared release helper.
void __fastcall FUN_00710410(Holder_00710410* self, int, void* item)
{
    if (item == self->RefA) {
        self->RefA = 0;
    }
    if (item == self->RefB) {
        self->RefB = 0;
    }
    if (item == self->RefC) {
        self->RefC = 0;
    }
    if (item == self->RefD) {
        self->RefD = 0;
    }
    FUN_005F6DA0(item);
}
