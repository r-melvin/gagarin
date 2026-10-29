// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the three addresses below.

#include "small_misc46_methods.h"

// FUNCTION: GAMEMD 0x42DD60   VectorClass<unsigned short>::VectorClass
VectorClassUnsignedShort::VectorClassUnsignedShort(int capacity, void* array)
{
    Items         = 0;
    Capacity      = capacity;
    IsInitialized = 1;
    IsAllocated   = 0;
    Vtable        = &VT_007E3824;

    if (capacity != 0) {
        if (array != 0) {
            Items = array;

            return;
        }

        Items       = FUN_007C8E17(capacity * 2);
        IsAllocated = 1;
    }

    return;
}

// FUNCTION: GAMEMD 0x473980
int FUN_00473980(const char* name)
{
    if (name == 0) {
        return -1;
    }

    for (int i = 0; i < 11; i++) {
        if (FUN_007C8D20(DAT_0081B7C8[i].Second, name) == 0) {
            return i;
        }

        if (FUN_007C8D20(DAT_0081B7C8[i].First, name) == 0) {
            return i;
        }
    }

    return -1;
}
