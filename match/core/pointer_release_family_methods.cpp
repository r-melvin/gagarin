// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra

#include "pointer_release_family_methods.h"

// FUNCTION: GAMEMD 0x007B6760
//
// Release the held block and forget it.
void FUN_00007B6760(Holder_007B46F0* self)
{
    if (self->Block != 0) {
        gg_free(self->Block);
    }
    self->Block = 0;
}

// FUNCTION: GAMEMD 0x007B7040
//
// Release the held block and forget it.
void FUN_00007B7040(Holder_007B46F0* self)
{
    if (self->Block != 0) {
        gg_free(self->Block);
    }
    self->Block = 0;
}
