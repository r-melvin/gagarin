// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The seven vtable-seating base destructors, ordered ascending by address.

#include "seat_vtable_tail_dtor_sweep.h"

// FUNCTION: GAMEMD 0x535A60
// VTABLE: GAMEMD 0x7E1668
void __fastcall FUN_00535A60(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007E1668;
    FUN_00431B80(self);
}

// FUNCTION: GAMEMD 0x7668F0
// VTABLE: GAMEMD 0x7F7024
void __fastcall FUN_007668F0(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007F7024;
    FUN_0065D460(self);
}

// FUNCTION: GAMEMD 0x766900
// VTABLE: GAMEMD 0x7F7014
void __fastcall FUN_00766900(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007F7014;
    FUN_0065D460(self);
}

// FUNCTION: GAMEMD 0x766910
// VTABLE: GAMEMD 0x7F7040
void __fastcall FUN_00766910(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007F7040;
    FUN_0065D460(self);
}

// FUNCTION: GAMEMD 0x767300
// VTABLE: GAMEMD 0x7F7060
void __fastcall FUN_00767300(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007F7060;
    FUN_0065D660(self);
}

// FUNCTION: GAMEMD 0x76F060
// VTABLE: GAMEMD 0x7F71C4
void __fastcall FUN_0076F060(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007F71C4;
    FUN_0065D460(self);
}

// FUNCTION: GAMEMD 0x77D1F0
// VTABLE: GAMEMD 0x7F7624
void __fastcall FUN_0077D1F0(SeatDtorObject* self)
{
    self->Vtbl = VTABLE_007F7624;
    FUN_00624130(self);
}

