// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// VectorClass construction, ordered ascending by retail address, written out
// longhand per the family rule.

#include "vector_ctor_methods.h"

// FUNCTION: GAMEMD 0x40BD00
VectorCtor* VectorCtor::FUN_0040BD00(int size, void** array)
{
    Vector = 0;
    Length = size;
    IsValid = 1;
    IsAllocated = 0;

    *(char**)this = VT_007E180C;

    if (size != 0) {
        if (array != 0) {
            Vector = array;
        } else {
            Vector = (void**)FUN_007C8E17(size * 4);
            IsAllocated = 1;
        }
    }

    return this;
}

// FUNCTION: GAMEMD 0x42DC50
VectorCtor* VectorCtor::FUN_0042DC50(int size, void** array)
{
    Vector = 0;
    Length = size;
    IsValid = 1;
    IsAllocated = 0;

    *(char**)this = VT_007E37EC;

    if (size != 0) {
        if (array != 0) {
            Vector = array;
        } else {
            Vector = (void**)FUN_007C8E17(size * 4);
            IsAllocated = 1;
        }
    }

    return this;
}

// FUNCTION: GAMEMD 0x473140
VectorCtor* VectorCtor::FUN_00473140(int size, void** array)
{
    Vector = 0;
    Length = size;
    IsValid = 1;
    IsAllocated = 0;

    *(char**)this = VT_007E4BC4;

    if (size != 0) {
        if (array != 0) {
            Vector = array;
        } else {
            Vector = (void**)FUN_007C8E17(size * 4);
            IsAllocated = 1;
        }
    }

    return this;
}
