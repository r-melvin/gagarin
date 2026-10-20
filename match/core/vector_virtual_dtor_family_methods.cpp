// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra

#include "vector_virtual_dtor_family_methods.h"

// FUNCTION: GAMEMD 0x00765960
//
// Release the element block through the element type's own vector-deleting
// destructor, then clear the bookkeeping.
void __fastcall FUN_0000765960(VirtVector_00765960* self)
{
    if (self->Items != 0 && self->IsAllocated != 0) {
        delete [] self->Items;
        self->Items = 0;
    }
    self->IsAllocated = 0;
    self->Capacity = 0;
}

// FUNCTION: GAMEMD 0x00766D30
//
// Release the element block through the element type's own vector-deleting
// destructor, then clear the bookkeeping.
void __fastcall FUN_0000766D30(VirtVector_00765960* self)
{
    if (self->Items != 0 && self->IsAllocated != 0) {
        delete [] self->Items;
        self->Items = 0;
    }
    self->IsAllocated = 0;
    self->Capacity = 0;
}

// FUNCTION: GAMEMD 0x00769F50
//
// Release the element block through the element type's own vector-deleting
// destructor, then clear the bookkeeping.
void __fastcall FUN_0000769F50(VirtVector_00765960* self)
{
    if (self->Items != 0 && self->IsAllocated != 0) {
        delete [] self->Items;
        self->Items = 0;
    }
    self->IsAllocated = 0;
    self->Capacity = 0;
}

// FUNCTION: GAMEMD 0x0076B9E0
//
// Release the element block through the element type's own vector-deleting
// destructor, then clear the bookkeeping.
void __fastcall FUN_000076B9E0(VirtVector_00765960* self)
{
    if (self->Items != 0 && self->IsAllocated != 0) {
        delete [] self->Items;
        self->Items = 0;
    }
    self->IsAllocated = 0;
    self->Capacity = 0;
}
