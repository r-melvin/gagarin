// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x43A600.

#include "vector_owner_dtor_methods.h"

// FUNCTION: GAMEMD 0x43A600
//
// SCHEDULING DELTA (status partial, 95.5% - 42/44). Two instructions are
// transposed: retail installs the vtable and then loads the element count,
// while VC6 loads the count first. The store depends on nothing, so it floats.
// The count is read straight from the member.
//
// The tenth batch's boundary levers were measured against it and none reaches
// it. The release loop as a free function taking the vector as its first
// pointer parameter is actively wrong here: the container is *embedded* at
// +0x04 and retail addresses it off the owner's own register with a
// displacement, where the free form makes cl hold `LEA ESI,[ECX+4]` and index
// off that (25.0%; the whole teardown as one free function 25.0%, the loop
// with the count passed as a parameter 22.7%, the owner re-bound to a named
// `self` 25.0%). Nor is the order source-selectable: reading the count *before*
// the vtable store still emits the load first (95.5%), and so does declaring
// both locals ahead of the store (95.5%) or letting cl seat the vptr itself
// from a real destructor on a class with virtuals (95.5%, virtual or not).
// Reading the count in the loop condition is 40.9%, guarding the loop on it
// 15.2%, and a volatile-only vtable store 90.9%. cl sinks that store past the
// load unconditionally.
//
// Release every element, hand the vector its own teardown through slot +0x0C,
// then free the buffer - but only when the vector owns it. The IsAllocated byte
// is checked *after* the pointer, and both clears happen whether or not the
// free ran.
void Owner_0043A600::FUN_0043A600()
{
    Vtable = &VT_007E3E74;

    int count = Items.Count;

    for (int i = 0; i < count; i++) {
        Item_0043A600* item = Items.Items[i];

        if (item) {
            item->vt_020(1);
        }

        Items.Items[i] = 0;
    }

    // The embedded vector's own teardown, inlined: retail materialises its
    // address (`LEA ESI,[EDI+0x4]`) and addresses IsAllocated, Items and
    // Capacity off that register (+0xD/+0x4/+0x8), so the vector's `this` is
    // named here. Writing the same teardown through `Items.` member accesses
    // instead scores 52.3%.
    Vector_0043A600* vector = &Items;

    vector->vt_00C();

    Item_0043A600** buffer = vector->Items;

    *(char**)vector = &VT_007E3E54;

    if (buffer && vector->IsAllocated) {
        FUN_007C8B3D(buffer);

        vector->Items = 0;
    }

    vector->IsAllocated = 0;
    vector->Capacity    = 0;
}
