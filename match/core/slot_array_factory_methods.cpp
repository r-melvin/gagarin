// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4087F0.

#include <string.h>
#include "slot_array_factory_methods.h"

#pragma intrinsic(memset)

// FUNCTION: GAMEMD 0x4087F0
//
// Allocate an owner, zero it whole, then walk its two slots giving each one a
// back-pointer and its own index.
//
// Use the declared slot fields directly rather than manufacturing a cursor
// through an interior member solely to control register allocation.
Owner_004087F0* __fastcall FUN_004087F0()
{
    Owner_004087F0* self = (Owner_004087F0*)FUN_007C8E17(sizeof(Owner_004087F0));
    memset(self, 0, sizeof(Owner_004087F0));

    FUN_004072C0(self->Embedded);
    self->field_98 = 0;

    for (int i = 0; i < 2; i++) {
        self->Slots[i].Owner = self;
        self->Slots[i].field_1C = 0;
        self->Slots[i].Index = i;
        self->Slots[i].field_24 = 0;
        self->Slots[i].field_18 = 0;
    }

    return self;
}
