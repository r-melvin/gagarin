// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Two WarheadTypeClass array helpers emitted in the block at 0x40F2D0. The
// class is fixed by the constructor 0x75CEC0 (it installs the WarheadTypeClass
// tables 0x7F6B30 / 0x7F6B14 / 0x7F6B0C / 0x7F6B04), the 0x1D0 allocation and
// the array at 0x8874C0. The ID compared is AbstractTypeClass::ID (+0x24).
#include "type_class_findoralloc_methods.h"

// The array's inline FindItemIndex, written against the layout view.
static inline int WarheadIndexOf(WarheadTypeClass* item)
{
    for (int i = 0; i < WarheadTypeClassArray.Count; i++) {
        if (((WarheadTypeClass**)WarheadTypeClassArray.Items)[i] == item)
            return i;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x40F510
// Returns the index of the warhead named `id`, creating it if absent; -1 for
// the "no type" literals.
int __fastcall WarheadTypeClass::FUN_0040F510(const char* id)
{
    if (_stricmp(id, "<none>") == 0 || _stricmp(id, "none") == 0)
        return -1;

    for (int i = 0; i < WarheadTypeClassArray.Count; i++) {
        if (_stricmp(id, ((WarheadTypeClass**)WarheadTypeClassArray.Items)[i]->ID) == 0)
            return i;
    }

    return WarheadIndexOf(new WarheadTypeClass(id));
}

// FUNCTION: GAMEMD 0x40F5C0
const char* __fastcall WarheadTypeClass::FUN_0040F5C0(int index)
{
    if (index == -1 || (unsigned)index >= (unsigned)WarheadTypeClassArray.Count)
        return 0;
    return ((WarheadTypeClass**)WarheadTypeClassArray.Items)[index]->ID;
}
