// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the four addresses below.

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

// FUNCTION: GAMEMD 0x433940
void __fastcall FUN_00433940(Obj_00433940* self)
{
    void* block = self->Block;

    self->Vtable = &VT_007E3A78;

    if (block) {
        FUN_007C93E8(block);
    }

    Sub_00433940* sub = self->Sub;

    if (sub) {
        if (sub->BufferA) {
            FUN_007C8B3D(sub->BufferA);
        }

        if (sub->BufferB) {
            FUN_007C8B3D(sub->BufferB);
        }

        FUN_007C8B3D(sub);
    }
}

// FUNCTION: GAMEMD 0x458E00
int BuildingClass_00458E00::FUN_00458E00()
{
    int limit = Settings->FUN_0045ECA0(0);

    if (Settings->FUN_0045EC90() < limit) {
        return Settings->FUN_0045EC90() / 2;
    }

    return Settings->FUN_0045ECA0(0) / 2;
}

// FUNCTION: GAMEMD 0x473980
int __fastcall FUN_00473980(const char* name)
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
