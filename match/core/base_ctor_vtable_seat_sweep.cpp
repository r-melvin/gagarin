// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The five derived constructors, ordered ascending by retail address.

#include "base_ctor_vtable_seat_sweep.h"

// FUNCTION: GAMEMD 0x765C70
// VTABLE: GAMEMD 0x7F6F34
CtorSeatObject* FUN_00765C70(CtorSeatObject* self)
{
    FUN_0065D430(self);
    self->Vtbl = VTABLE_007F6F34;

    return self;
}

// FUNCTION: GAMEMD 0x7670D0
// VTABLE: GAMEMD 0x7F7024
CtorSeatObject* FUN_007670D0(CtorSeatObject* self)
{
    FUN_0065D430(self);
    self->Vtbl = VTABLE_007F7024;

    return self;
}

// FUNCTION: GAMEMD 0x76A7C0
// VTABLE: GAMEMD 0x7F71C4
CtorSeatObject* FUN_0076A7C0(CtorSeatObject* self)
{
    FUN_0065D430(self);
    self->Vtbl = VTABLE_007F71C4;

    return self;
}

// FUNCTION: GAMEMD 0x76BC60
// VTABLE: GAMEMD 0x7EBFA4
CtorSeatObject* FUN_0076BC60(CtorSeatObject* self)
{
    FUN_0065D430(self);
    self->Vtbl = VTABLE_007EBFA4;

    return self;
}

