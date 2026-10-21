// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// RTTI at COL0x7FAD18 / TD0x817508 identifies the table 0x7E1B04 as
// GenericList; its slot-zero target is 0x40E3E0, complete span 179 bytes.
// Original native virtual declarations remain unrecovered; explicit vptr view.
#include "../_layout/generic_list.h"
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete.
extern "C" void __cdecl FUN_007C8B3D(void* block);

// FUNCTION: GAMEMD 0x40E3E0
void* GenericList::DeletingDestructor(unsigned int flags)
{
    DestroyList();
    if (flags & 1) {
        FUN_007C8B3D(this);
    }
    return this;
}

// VTABLE: GAMEMD 0x7E1B04 -- GenericList.
GenericListDeletingSlot GG_VTABLE_GENERIC_LIST_SLOTS =
    &GenericList::DeletingDestructor;
GG_STATIC_ASSERT(sizeof(GenericListDeletingSlot) == 4);
