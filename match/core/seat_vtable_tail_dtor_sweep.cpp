// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The seven vtable-seating base destructors, ordered ascending by address.

#include "seat_vtable_tail_dtor_sweep.h"


// FUNCTION: GAMEMD 0x7668F0
// VTABLE: GAMEMD 0x7F7024
void FUN_007668F0(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007F7024;
    FUN_0065D460(self);
}

// FUNCTION: GAMEMD 0x766900
// VTABLE: GAMEMD 0x7F7014
void FUN_00766900(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007F7014;
    FUN_0065D460(self);
}

// FUNCTION: GAMEMD 0x766910
// VTABLE: GAMEMD 0x7F7040
void FUN_00766910(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007F7040;
    FUN_0065D460(self);
}

