// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x402EF0.

#include "list_teardown_methods.h"

// FUNCTION: GAMEMD 0x4033C0
//
// REGISTER-ROLE DELTA (status partial, 66.7%). The whole of the sweep, the
// registrar work and the second floored decrement are exact; the residual is
// five instructions in the first one, where retail keeps the singleton pointer
// in ECX and the count in EAX and VC6 assigns them the other way round.
// Spelling the global out at each use instead of holding it is much worse
// (7.4%) - it re-reads rather than re-assigning.
//
// The busy counter is raised and floored around the unlink, then the body is
// exactly 0x402EF0's. Written out longhand rather than calling it, per the
// family rule.
void __fastcall FUN_004033C0(Owner_00402EF0* self)
{
    DAT_00815E98->Count++;

    FUN_00407450(self);

    // Decrement written twice so the `TEST` survives - section 4.6.
    Busy_004033C0* busy = DAT_00815E98;

    int count = busy->Count;

    busy->Count = count - 1;

    if (count - 1 < 0) {
        DAT_00815E98->Count = 0;
    }

    ListNode* next = (&self->Items)->FUN_004073C0();
    ListNode* node = next;

    while (next) {
        next = (node)->FUN_004073E0();

        FUN_00402550(node);

        node = next;
    }

    (*(RegistrarSlot_00402EF0*)((char*)self->Registrar->Dispatch + 0x20))(self);

    self->Registrar->Slots[self->SlotIndex] = 0;

    Registrar_00402EF0* registrar = self->Registrar;

    int slots = registrar->Count;

    registrar->Count = slots - 1;

    if (slots - 1 < 0) {
        self->Registrar->Count = 0;
    }

    FUN_007C8B3D(self);
}

// FUNCTION: GAMEMD 0x402EF0
//
// The sweep is driven by the successor with the node copied out at the top,
// the shape established at 0x4036F0: both variables live before the loop so
// all three callee-saved pushes land in the prologue.
//
// The registrar is re-read for each of its three uses rather than held.
void __fastcall FUN_00402EF0(Owner_00402EF0* self)
{
    ListNode* next = (&self->Items)->FUN_004073C0();
    ListNode* node = next;

    while (next) {
        next = (node)->FUN_004073E0();

        FUN_00402550(node);

        node = next;
    }

    (*(RegistrarSlot_00402EF0*)((char*)self->Registrar->Dispatch + 0x20))(self);

    self->Registrar->Slots[self->SlotIndex] = 0;

    // Decrement written twice so the `TEST` survives - section 4.6.
    Registrar_00402EF0* registrar = self->Registrar;

    int count = registrar->Count;

    registrar->Count = count - 1;

    if (count - 1 < 0) {
        self->Registrar->Count = 0;
    }

    FUN_007C8B3D(self);
}
