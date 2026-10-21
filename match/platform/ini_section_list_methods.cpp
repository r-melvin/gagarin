// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// RTTI COL0x7FAC20 / TD0x817480 names List<INIClass::INISection*>;
// its table0x7E1AFC slot0 is 0x40E4C0. Full entry-origin span is 179 bytes.
// Original virtual declarations remain unrecovered; explicit vptr model retained.
#include "../_layout/ini_class.h"
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete.
extern "C" void __cdecl FUN_007C8B3D(void* block);

// FUNCTION: GAMEMD 0x40E4C0
template<> void* List<INIClass::INISection*>::DeletingDestructor(unsigned int flags)
{
    DestroyList();
    if (flags & 1) {
        FUN_007C8B3D(this);
    }
    return this;
}

typedef void* (List<INIClass::INISection*>::*INISectionListDeletingSlot)(unsigned int);
// VTABLE: GAMEMD 0x7E1AFC -- List<INIClass::INISection*>.
INISectionListDeletingSlot GG_VTABLE_LISTOFINISECTION =
    &List<INIClass::INISection*>::DeletingDestructor;
GG_STATIC_ASSERT(sizeof(INISectionListDeletingSlot) == 4);
