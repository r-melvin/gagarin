// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the three addresses below.

#include "small_misc46_methods.h"
#include "vector_class_operations.h"

// FUNCTION: GAMEMD 0x42DD60   VectorClass<unsigned short>::VectorClass
// SYNTHETIC: GAMEMD 0x42DBB0 -- VectorClass<unsigned short>::`scalar deleting destructor'
// SYNTHETIC: GAMEMD 0x42DC00 -- DynamicVectorClass<unsigned short>::`scalar deleting destructor'
template class VectorClass<unsigned short>;
template class DynamicVectorClass<unsigned short>;

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
