// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//   Address index: 0x6C9AE0.

#include "vector_class_operations.h"
#include "trivial_tu224_methods.h"

// Polymorphic object owned by the receiver; only its deleting destructor
// (slot 0) is used.
struct Owned_006C9AE0
{
    virtual ~Owned_006C9AE0();
};

// View of the receiver of 0x6C9AE0 (the 9-dword object initialised by 0x6C9AC0).
struct Owner_006C9AE0
{
    DynamicVectorClass<Obj_006C9930*>* Items;   // +0x00
    int unknown_04;
    int unknown_08;
    int unknown_0C;
    Owned_006C9AE0* Other;                      // +0x10
    // FUNCTION: GAMEMD 0x6C9AE0
    void FUN_006C9AE0();
};

// FUNCTION: GAMEMD 0x6C9AE0
// Releases the owned entries: each item in the vector is torn down and freed,
// then the vector itself and the second owned object are deleted.
void Owner_006C9AE0::FUN_006C9AE0()
{
    if (Items) {
        for (int i = 0; i < Items->Count; i++) {
            Obj_006C9930* item = Items->Items[i];
            if (item) {
                item->FUN_006C9930();
                delete item;
            }
        }
        if (Items)
            delete Items;
    }
    if (Other)
        delete Other;
}
