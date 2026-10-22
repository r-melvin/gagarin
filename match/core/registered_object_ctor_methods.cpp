// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x41D300.

#include "registered_object_ctor_methods.h"

// The append is a free helper taking the registry as a pointer parameter, not
// a member of Registry_0041D300. That is the whole residual: as a member with
// `this` implicit, cl 8804 accumulates the capacity sum into the wrong register
// (`ADD EAX,ECX`) and defers the receiver's vtable load past the argument
// pushes; the identical body with the registry as an ordinary pointer
// parameter gives retail's `ADD ECX,EAX; MOV EAX,[Array]; PUSH 0; PUSH ECX`.
// Mirrors DynamicVectorClass::AddItem. The three failure paths just skip the
// append, so in the constructor they become jumps to its tail.
static inline bool AddItem_0041D300(Registry_0041D300* self, Obj_0041D300* item)
{
    if (self->Count >= self->Capacity) {
        if (!self->IsAllocated && self->Capacity != 0) {
            return false;
        }
        if (self->CapacityIncrement <= 0) {
            return false;
        }
        if (!(self->*self->Vptr->SetCapacity)(self->CapacityIncrement + self->Capacity, 0)) {
            return false;
        }
    }

    int index = self->Count++;
    self->Items[index] = item;
    return true;
}

// FUNCTION: GAMEMD 0x41D300
//
// MATCHED (100.0%, 36/36). The two residuals — retail accumulating the capacity
// sum into the increment's register (`ADD ECX,EAX`) and loading the receiver's
// vtable before the argument pushes — were one lever, and it is the shape of
// the inlined helper rather than anything inside it: written as a member of the
// registry the body scores 88.9%, written as a free inline function taking the
// registry as its first pointer parameter the same body scores 100%. This is
// the mirror of the banked destructor rule (a `__thiscall` shape wants to be a
// real member); an inlined vector append on a *global* container wants the
// container as an ordinary parameter.
//
// Variants measured this pass: the free-function form (100%, kept); the same
// with the registry parameter as `Registry_0041D300* const&` (100%); the grow
// call lifted into its own inline helper taking the registry by const&
// (100%); the vtable bound to a local before the call (66.7%); the slot bound
// to a member-pointer local before the call (24.3%); and the increment read
// into a local and compound-added (61.1%). Earlier passes had tried, on the
// member spelling, naming the sum in a local, naming both call arguments in
// push order and swapping the sum's operands — all 88.9%.
//
// The append itself needed `Count++` rather than a read-then-add: retail copies
// the index out and increments in place (`MOV EAX,ECX; INC ECX`), where
// `index = Count; Count = index + 1;` gives VC6 a single `LEA ECX,[EAX+1]`. That
// took 58.3% to 88.9%.
//
// Construct the object and register it in the global list. The registration's
// result is discarded — if the list cannot grow, the object is simply not in it,
// and the constructor still succeeds.
Obj_0041D300* Obj_0041D300::Ctor()
{
    this->BaseCtor();

    this->Vptr0 = VTBL_007E29A8;
    this->Vptr1 = VTBL_007E298C;
    this->Vptr2 = VTBL_007E2984;
    this->Vptr3 = VTBL_007E297C;

    AddItem_0041D300(&DAT_00889FB8, this);
    return this;
}
